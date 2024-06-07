After opening the binary in [dogbolt](https://dogbolt.org/).

We can see that the binary take 2 argument:
- The first is use to defined the length of the memcpy : `4 * argv[1]` + launch a shell if it equal to 1464814662
- The second is use to fill an array


To launch the shell we have to defined `v5` to `1464814662` but `v5` can't be greater than 9.
We can see that `v5` is defined just after the buffer filled by the second given argument.
We know that `v5` is used to defined the length that `memcpy` will copy and since `v5` is defined just after the buffer if we succeed to make `v5` * 4 > 40(len of the buffer) we can use use the buffer to overwrite `v5`.

We also know that `v5` is a signed int and that `memcpy` take a unsigned int as parameter so let's exploit this.

We know that we have to set `v5` to 44:
- [40 (length of dest)] + [4 bytes (size of an int)] == 44
- Since we can't input a number > 9, we will have to input a negative number let's find it with this [converter](https://www.simonv.fr/TypesConvert/?integers):
Signed and Unsigned integer representation:
- In 32 bits representation, the signed integer `-44` has the same bit representation as the unsigned integer `4294967252` because of two's complement representation.
- `-44` (signed) == `4294967252`(unsigned)
And signed int `-4294967252` == the unsigned int `44`
To compensate for the Multiplication:
- We divide 4294967252 by 4 to counter the `* 4` in the `memcpy` : `4294967252 / 4 = 1073741813`
After overflow `-1073741813` will result in `44`


Transforming `1464814662` in hexadecimal to fill the int with the correct number:
`1464814662` in hex : `574f4c46`
in little endian : `\x46\x4c\x4f\x57`


To overwrite `v5` and set the variable to `1464814662` we know that our second argument will look like :
[40 char to fill `dest`][1464814662(in hex)]
Second argument : `$(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')`

Put together we have :
``` Shell
./bonus1 -1073741813  $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
```
