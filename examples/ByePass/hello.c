#include <stdio.h>

int main() {
	printf("Hello World!\n");
	return 0;
}

// clang -O0 -emit-llvm hello.c -c -o hello.bc