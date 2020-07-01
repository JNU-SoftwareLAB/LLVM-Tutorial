## Print unreachable basic blocks in LLVM programs. 
#### [Excerpted from a lecture, Principles and Practices of Software Development, at SNU](https://github.com/snu-sf-class/swpp202001/tree/master/practice/3.assn)

### Assignment 3

To submit your code:

```
./package.sh
# Now, upload submit.tar.gz to ETL
```


#### 2. unreachable.cpp

Update `unreachable.cpp` so it enumerates unreachable blocks from the given IR.
For example,

```
define void @f(i1 %cond) {
entry:
  br i1 %cond, label %bb1, label %bb2
bb1:
  br label %bb2
bb2:
  ret void
bb_unreachable:
  ret void
}
```

The block `bb_unreachable` cannot be executed whatever `%cond` is.
Your pass should print the name of the blocks that are unreachable, per one line.
If there are more than one unreachable blocks, please print them in
lexicographical order (사전순).
It is assumed that names of basic blocks are unique, and all branch conditions
are given from a function argument (such as `%cond` in the above example).

NOTE: you should report blocks that are syntactically unreachable only.
For example,

```
entry:
if (flag) {
  if (!flag) {
  BB1: // logically unreachable, but syntactically reachable
  }
}
```

In this case, you should not report BB1, because there exists branch instructions from the entry to BB1 syntactically.


##### How to check

```
./unreachable.sh all <clang directory(e.g: ~/my-llvm-release/bin)>
# If you want to compile only..
./unreachable.sh build <clang directory(e.g: ~/my-llvm-release/bin)>
# If you want to run only..
./unreachable.sh run <clang directory(e.g: ~/my-llvm-release/bin)>
```

##### Hints

Read slides and codes in practice/3.materials.

Refer to the LLVM API document for BasicBlock, Function, StringRef, and so on.

Refer to CPP references for templates. [LINK](https://en.cppreference.com/)

##### Setting VSCode

Setting VSCode to successfully find header files will greatly help doing your
assignment.

In order to do this, you will need to update your includePath
( https://stackoverflow.com/a/48015407 ).

If you're using master branch built with llvmscript, please add these two paths
to the includePath:

```
..(your path)../my-llvm-project/llvm/include
..(your path)../my-llvm-release/include
```

If you're using the prebuilt binary, please add this:

```
..(your path)../clang+llvm-9.0.0-x86_64-<...>/include
```

#### Video References about this problem
- [Basic Block](https://www.youtube.com/watch?v=m8G_S5LwlTo&feature=youtu.be&t=818)
- [Remove Dead Blocks](https://youtu.be/3QQuhL-dSys?t=738)
