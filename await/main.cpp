#include <iostream>
#include <emscripten.h>
#include "coro.h"

EM_JS(void, js_sleep, (), {
   console.log('js sleep');
   setTimeout(() => {
     Module._wasm_wakeup();
   }, 3000);
});

std::optional<std::coroutine_handle<>> pending;

struct sleep_awaiter {
   bool await_ready() const {
      return false;
   }
   int await_resume() {
      std::cout << "resume" << std::endl;
      return 42;
   }
   void await_suspend(std::coroutine_handle<> h) {
      pending = h;
      std::cout << "suspended" << std::endl;
   }
};

sleep_awaiter sleep() {
   js_sleep();
   return sleep_awaiter{};
}

task<int> do_sleep() {
   int ret = co_await sleep();
   co_return ret;
}

task<void> async_process() {
   std::cout << "begin async process" << std::endl;
   int i = co_await do_sleep();
   std::cout << "end async process: " << i << std::endl;
}

async_scope global_scope;

extern "C" {

void wasm_wakeup() {
   std::cout << "wake up: " << pending.has_value()  << std::endl;
   pending->resume();
}

int main() {
   std::cout << "enter main()" << std::endl;
   global_scope.spawn_detached(lazy_task{[] { return async_process(); }});
}

}
