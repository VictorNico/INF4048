bison --defines=simple.h -v -o exo20-23.c exo20-23.y
flex -o exo20-23.yy.c exo20-23.lex
gcc exo20-23.yy.c exo20-23.c -o exo20-23 -lfl
cat commande.group6 | ./exo20-23
nasm -f elf -o test.o test.asm
ld -s -o test test.o -melf_i386 -I/lib/ld-linux.so.2 -lc

