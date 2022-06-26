nasm -f elf -o hello-world.o hello-world.asm
ld -s -o hello-world hello-world.o -melf_i386
strip hello-world
./hello-world
