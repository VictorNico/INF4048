nasm -f elf -o hello-world.o hello-world.asm
ld -s -o hello-world hello-world.o -melf_i386 -I/lib/ld-linux.so.2 -lc

