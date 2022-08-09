emcc \
    -s LOAD_SOURCE_MAP=1 \
    -s EXPORTED_FUNCTIONS=_main,_malloc,_call_back_wasm \
    --profiling \
    -gsource-map \
    -fwasm-exceptions \
    -sEXPORT_EXCEPTION_HANDLING_HELPERS=1 \
    --std=c++20 main.cpp && node --experimental-wasm-eh a.out.js
