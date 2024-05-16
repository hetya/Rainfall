After opening the binary in [dogbolt](https://dogbolt.org/).

We can see that the binary take 2 argument:
- The first is use to defined the length of the memcpy : `4 * argv[1]` + launch a shell if it equal to 1464814662
- The second is use to fill an array

To launch the shell we have to defined `v5` to 1464814662 but `v5` can't be greater than 9.

Here we can see that `v5` is defined just after the char array filled by the second argument.
Let's try to overflow in `v5` to overflow in `v5`. We can use the first argument to change the size of the length that the `memcpy` will copy but `v5` can only be `<=9` so have to find a way to bypass the check.

Here we know that `v5` is a signed int and that `memcpy` take a unsigned int as parameter so let's exploit this.

We know that an negative signed int is a lot bigger in unsigned int, like signed int -1 is unsigned int max.
We also know that when we input a signed int in an unsigned int parameter it will read it like an unsigned int.

We know that we have to set `v5` to 44:
[40 length of dest] + [4 bytes size of an int]
Lets convert 44 in signed int using a [converter](https://www.simonv.fr/TypesConvert/?integers):
We want to input an negative number to overflow the unsigned int, we input `-44`.
This give us `4294967252` in unsigned int
So the signed int `-44` == the unsigned int `4294967252`
And signed int `-4294967252` == the unsigned int `44`
We 4294967252 / 4 to counter the `* 4` of the `memcpy` : 1073741813
So we get `-1073741813`



To overflow `v5` and set the variable to 1464814662 we know that our second argument will look like :
[40 char to fill `dest`][the number 1464814662]
ok we will transform 1464814662 in hexadecimal so we can fill the int with the correct number:
`1464814662` in hex : `574f4c46`
in little endian : `\x46\x4c\x4f\x57`
Second argument : `$(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')`

Put together we have :
``` Shell
./bonus1 -1073741813  $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
```