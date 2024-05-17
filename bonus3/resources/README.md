First we open the file in [dogbolt](https://dogbolt.org/).

We see that the binary can take one argument.
The argument is cast in a int with an `atoi`
The program put a `\0` at the index given by `atoi` in `ptr`(char [])
and after this compare the `ptr` with `argv[1]`

So if we enter an empty argument, the `atoi` will try to convert the only char in the string which is`\0`
and since the string is empty (just `\0`) `atoi` will return `0`
The program will put a `\0` at the `0` index from ptr.
And this give us two identical strings

```Shell
bonus3@RainFall:~$ ./bonus3 ""
```
