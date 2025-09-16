## IMTH -- `0x494d5448`

```
A   (.. n -- r) Average
B   (n -- r)    Absolute value
C   (n -- r)    Multiply by 100
D   (n -- r)    Decrease towards zero
E   (n -- r)    Multiply by 10,000
F   (n -- r)    Factorial
G   (n -- r)    Sign
H   (n -- r)    Multiply by 1,000
I   (n -- r)    Increase away from zero
L   (n c -- r)  Shift n left c times
N   (.. n -- r) Minimum value
R   (n c -- r)  Shift n right c times
S   (.. n -- r) Sum
T   (n -- r)    Multiply by 10
U   (n -- )     Unsigned print
X   (.. n -- r) Maximum value
Z   (n -- r)    Negate

    A n=0 is not an error and will return 0
    A n<0 is an error and will reflect
    A n>stacksize is not an error
    F will reflect on negative
    L c can be negative and will shift right
    R c can be negative and will shift left
    L,R count of zero will return the argument unmodified
    N,X will reflect if count <= 0
    N,X count greater than stack size is not an error
    S n=0 is not an error and will return 0
    S n<0 is an error and will reflect
    S n>stacksize is not an error
    D input of zero is not an error and will produce zero
    I input of zero is not an error and will produce zero 
```
