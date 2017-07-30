# Memory

## Bits and Bytes

### Bits

The smallest unit of memory is the *bit*. A bit can be in one of two states
-- **on** vs. **off**, or alternately, **1** vs. **0**.

Most computers don't work with bits individually, but instead group eight 
bits together to form a **byte**. Eash byte maintains one eight-bit pattern.
A group of N bits can be arranged in 2^N different patterns.

Strictly speaking, a program can interpret a bit pattern any way it chooses.

### Bytes

The byte is sometimes defined as the **smallest addressable unit** of memory.
Most computers also support reading and writting larger units of memory-- 2bytes **half-words** (sometimes known as a **short** word) and 4 byte **word**.

Most computers restrict half-word and word accesses to be **aligned**-- 
a half-word must start at an even address and a word must start at an 
address that is a multiple of 4.


### Basic Types

* Character: The ASCII code defines 128 characters and a mapping of those
characters onto the numbers 0..127. The letter 'A' is assigned 65 in the 
ASCII table. Expressed in binary, that's 2^6 + 2^0 (64 + 1). 
All standard ASCII characters have zero in the uppermost 
bit (the *most significant* bit) since they only span the range 0..127.

* Short Integer: 2 bytes or 16 bits. 16 bits provide 2^16 = 65536 patterns. 
This number is known as **64k**, where **1k** of something is 2^10 = 1024. 
For non-negative numbers these patterns map to the numbers 0..65535. Systems
that are _big-endian_ store the most-significant byte at the lower address. 
A _litter-endian_ (Intel x86) system arranges the bytes in the opposite 
order. This means when exchanging data through files or over a network 
between different endian machines, there is often a substantial amount of
**byte-swapping** required to rearrange the data.

* Long Integer: 4 bytes or 32 bits. 32 bits provide 2^32 = 4294967296 
patterns. 4 bytes is the contemporary default size for an integer. Also 
known as a **word**.

* Floating Point: 4,8, or 16 bytes. Almost all computers use the standard 
IEEE representation for floating point numbers that is a system much more
complex than the scheme for integers. The important thing to note is that
the bit pattern for the floating point number 1.0 is not the same as the 
pattern for integer 1. IEEE floats are in a form of scientific notation.
A 4-byte float uses 23 bits for the mantissa, 8 bits for the exponent, and
1 bit for the sign. Some processors have a special hardware Floating Point
Unit, FPU, that substantially speeds up floating point operations.
With separate integer and floating point processing units, it is often 
possible that an integer and a floating point computation can proceed in
parallel to an extent. The exponent field contains 127 plus the true 
exponent for sigle-precision, or 1023 plus the true exponent for double
precision. The first bit of the mantissa is typically assumed to be 1._f_,
where _f_ is the field of fraction bits.

|                   |   sign   |   exponent (base 2)` |   mantissa   |
|:-----------------:|---------:|---------------------:|-------------:|
| signle precision  | 1 \[31\] | 8 \[30-23\]          | 23 \[22-00\] |
| double precision  | 1 \[63\] | 8 \[62-52\]          | 52 \[51-00\] |

* Records: The size of a record is equal to at least the sum of the size
of its component fields. The record is laid out by allocating the components 
sequentially in a contiguous block, working from low memory to high. 
Sometimes a compiler will add invisible pad fields in a record to comply
with processor alignment rectrictions.

* Arrays: The size of an array is at least equal to the size of each element 
multiplied by the number of components. The elements in the array are laid
out consecutively starting with the first element and working from low
memory to high. Given the base address of the array, the compiler can generate
constant-time code to figure the address of any element. As with records,
there may be pad bytes added to the size of each element to comply with
alignment retrictions.

* Pointer: A pointer is an address. The size of the pointer depends on the 
range of addresses on the machine. Currently almost all machines use 4 bytes
to store an address, creating a 4GB addressable range. There is actually
very little distinction between a pointer and a 4 byte unsigned integer.
They both just store integers-- the difference is in whether the number is 
_interpreted_ as a number or as an address.

* Instruction: Machine instructions themselves are also encoded using bit
patterns, most often using the same 4-byte native word size. The different
bits in the instruction encoding indicate things such as what type of 
instruction it is (load, store, multiply, etc) and registers involved.

## Allocation


### malloc
> don't cast the result of malloc
> It is unneccessary, as ```void *``` is automatically and safely prompted to any
other pointer type in this case.
> It adds clutter to the code, casts are not very easy to read (especially if the
pointer type is long).
> It makes you repeat yourself, which is generally bad.
> It can hide an error, if you forgot to include ```<stdlib.h>```. This can crashes 
(or, worse, not cause a crash until way later in some totally different part of the
code). Consider what happens if pointers and integers are differently sized; then
you're hiding a warning by casting and might lose bits of your returned address. 
Note: as of C11 implicit functions are gone from C, and this point is no longer 
relevant since there's no automatic assumption that undeclared functions return 
```int```

> To add further, your code needlessly repeats the type information (```int```) which
can cause errors. It's better to dereference the pointer being used to store the 
return value, to __lock__ the two together:
> ```int *x = malloc(length * sizeof *x);```
> This also moves the ```lengh``` to the front for increased visibility, and drops
the redundant parentheses with ```sizeof()```; they are only needed when the argument 
is a type name. Many people seem to not know or ignore this, which makes their code
move verbose. Remember: ```sizeof``` is not a function!

> While moving length to the front may increase visibility in some
rare cases, one should also pay attention that in the general case, 
it should be better to write the expression as:
```int *x = malloc(sizeof *x * length);```

> Compare with ```malloc(sizeof *x * length * width)``` vs. 
```malloc(length * width * sizeof *x)``` the second may overflow the 
```length * width``` when ```length``` and ```width``` are smaller types than 
```size_t```.

### free

## References
* [Programming Paradigms](https://see.stanford.edu/Course/CS107)
* [IEEE Standard 754 Floating Point Numbers](http://steve.hollasch.net/cgindex/coding/ieeefloat.html)
* [Do I cast the result of malloc](https://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc)