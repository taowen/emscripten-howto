emcc \
    -s EXPORTED_FUNCTIONS=_main,_malloc,_call_back_wasm \
    --profiling-funcs \
    -gseparate-dwarf \
    -gsource-map \
    -fwasm-exceptions \
    -sEXPORT_EXCEPTION_HANDLING_HELPERS=1 \
    --std=c++20 main.cpp
node --experimental-wasm-eh a.out.js > run.log
node processLog.js
