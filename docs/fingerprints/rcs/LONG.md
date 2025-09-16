## LONG -- `0x4c4f4e47`

```
A   (ah al bh bl -- rh rl)  Addition
B   (ah al -- rh rl)        Absolute value
D   (ah al bh bl -- rh rl)  Division
E   (n -- rh rl)            Sign extend single to long
L   (ah al n -- rh rl)      Shift left n times
M   (ah al bh bl -- rh rl)  Multiplication
N   (ah al -- rh rl)        Negate
O   (ah al bh bl -- rh rl)  Modulo
P   (ah al -- )             Print
R   (ah al n -- rh rl)      Shift right n times
S   (ah al bh bl -- rh rl)  Subraction
Z   (0gnirts -- rh rl)      Ascii to long

    Long integers are 2 cell integers, if the interpreter's cell size is 32, then long integers are 64-bits.
    Division by zero results in zero, not error 
```
