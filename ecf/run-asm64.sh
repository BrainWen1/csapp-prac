#! /bin/bash

# 汇编
as --64 -o hello-asm64.o hello-asm64.s

# 链接
ld -o ../bin/hello-asm64 hello-asm64.o
