#### usage
```bash
clang -O0 -emit-llvm hello.c -c -o hello.bc

cmake . -B./dest && cmake --build ./dest

opt -load ./dest/libLLVMBye.so -goodbye -time-passes < ./hello.bc > /dev/null
opt -load-pass-plugin ./dest/libLLVMBye.so -passes "bye-pass" < ./hello.bc > /dev/null
```

#### reference
i referred manythings from [here](https://medium.com/@mshockwave/writing-llvm-pass-in-2018-part-i-531c700e85eb) and [here](https://github.com/llvm/llvm-project/blob/master/llvm/examples/Bye/Bye.cpp)

i hope it's helpful for you.