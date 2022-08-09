emcc -s EXPORTED_FUNCTIONS=_main,_malloc,_wasm_wakeup --std=c++20 main.cpp && node a.out.js
