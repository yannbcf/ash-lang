```
xmake
xmake run

nasm -f elf64 out.asm
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o ash -lc out.o
./ash
echo $?
```
