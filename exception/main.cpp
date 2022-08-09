#include <iostream>
#include <emscripten.h>

EM_JS(void, call_js, (), {
     try {
        Module._call_back_wasm();
     } catch(e) {
         if (e.getArg && Module.getExceptionMessage) {
               const [exType, exMsg] = Module.getExceptionMessage(e);
               console.log(exType, exMsg, e.stack);
         }
     }
});

void in_sub_function() {
   throw std::runtime_error("shit happens");
}

extern "C" {

void call_back_wasm() {
   std::cout << "!!! about to throw" << std::endl;
   in_sub_function();
}

int main() {
	call_js();
}

}
