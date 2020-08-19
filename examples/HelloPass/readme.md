#### usage
```bash
clang -O0 -emit-llvm hello.c -c -o hello.bc

cmake . -B./dest && cmake --build ./dest

opt -load ./dest/LLVMHello.so -hello -time-passes < ../hello.bc > /dev/null
```

#### reference
i referred manythings from [here](https://llvm.org/docs/WritingAnLLVMPass.html#quick-start-writing-hello-world)

i hope it's helpful for you.