## ICAL -- `0x4943414c`

```
A   (a -- r)    Unary AND
F   (n -- )     Forget entries from nexting stack
I   (a b -- r)  Interleave a $ b
N   (Va -- )    Jump to new location
O   (a -- r)    Unary OR
R   (n -- )     Resume
S   (a b -- r)  Select a ~ b
X   (a -- r)    Unary XOR

    A,O,X work in 16 bits unless a is greater than 16 bits
    I a and b are 16-bits and will produce a 32 bit result
    N reflects if there are already 79 entries on the Next stack
    Neither N nor R affect the delta!
    0R is not an error and will just continue without resuming
    Negative argument to R is an error and will reflect
    R on an empty nexting stack will continue without resuming
    R if n is greater than the number of nexting stack entries, the nexting stack will be cleared and no resume will take place 
```
