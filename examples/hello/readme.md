#### usage
```bash
cmake . -B./dest
cd dest
cmake --build .
./Hello
lli ./hello.bc
llvm-dis ./hello.bc -o hello.ll
cat hello.ll
```

#### reference
i referred manythings from [here](https://www.slideshare.net/WeiRenChen/mclinker2013chenwj)

i hope it's helpful for you.