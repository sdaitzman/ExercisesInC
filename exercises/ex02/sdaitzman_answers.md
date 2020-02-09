# Software Systems Exercise 2
***Sam Daitzman // 2020***

1. The output of aspace, after some slight modifications to give me more info I was curious about, is:

```
 ▷ gcc aspace.c -o aspace; and ./aspace                                                                                                    (base) 
Address of main is 0x109c49d80
Address of var1 is 0x109c4b018
Address of var2 is 0x7ffee5fb6858
       p points to 0x7fb7cfc018d0
       p points to 0x7fb7cfc018d0
   Address of p is 0x7ffee5fb6850
       s points to 0x109c49edc
   Address of s is 0x7ffee5fb6840
       q points to 0x7fb7cfc01950
   Address of q is 0x7ffee5fb6848
```

2. `malloc` allocates the specified `int bytes` of memory and returns a pointer to the allocated memory (or, if it fails, it returns `NULL`).

3. Image to be linked.

4. The heap grows upwards:
```
p points to 0x7feb244018d0
q points to 0x7feb24401950
```

5. Addresses on the stack grow down:
```
Address of local is 0x7ffee9d457f8
 Address of var2 is 0x7ffee9d45858
```

$0x7ffee9d45858 - 0x7ffee9d457f8 = 0x60$