## STCK -- `0x5354434b`

```
B   (v n -- v ..)           Bury v value n deep into the stack
C   (.. -- cnt)             Get count of items on stack
D   (.. n -- ..)            Duplicate top n stack items
G   (n Vdlt Vsrc -- ..)     Read n stack entires from Funge-Space
K   (st en -- ..)           Push block of stack cells on top
N   (.. n -- ..)            Reverse n items on stack
P   (.. -- ..)              Print contents of stack, non-destructive
R   (.. -- ..)              Reverse all items on stack
S   (a b -- a a b)          Duplicate second on stack
T   (a b c -- b a c)        Swap second and third items on stack
U   (n -- n r)              Drop items from stack until n is found
W   (n Vdlt Vsrc -- )       Write n stack entires to Funge-Space
Z   (0string -- 0gnirts)    Reverse 0 terminated string on stack

    B if stack is not as deep as specified will reflect
    B if n is negative, push n zeroes above v
    K moves the block
    K if end is deeper than start, reflect
    K if end or start is negative, reflect
    K with start or end deeper than stack is NOT an error
    D works like ( a b c 3 -- a a b b c c )
    U reflects if the item is not found. r is the number of dropped items, next on stack will be the found value
    S with stack size <= 1 is NOT an error
    T with stack size <3 is NOT an error
    Both W and G will reflect on a negative count
    G must reproduce the stack written by W 
```
