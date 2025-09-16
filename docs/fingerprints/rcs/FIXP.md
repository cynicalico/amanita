## FIXP -- `0x46495850`

```
A   (a b -- a and b)    And
B   (n -- arccos(b))    Find arccosin of tos
C   (n -- cos(b))       Find cosin of tos
D   (n -- rnd(n))       RanDom number
I   (n -- sin(b))       Find sin of tos
J   (n -- arcsin(b))    Find arcsin of tos
N   (a -- 0-a)          Negate
O   (a b -- a or b)     Or
P   (a -- a*pi)         Multiply by pi
Q   (a -- sqrt(a))      Square root
R   (a b -- a**b)       Raise a to the power of b
S   (n -- n)            Replace tos with sign of tos
T   (n -- tan(b))       Find tangent of tos
U   (n -- arctan(b)     Find arctangent of tos
V   (n -- n)            Absolute value of tos
X   (a b -- a xor b)    Xor

    The functions C,I,T,B,J,U expect their arguments times 10000, for example: 45 should be passed as 450000. The 
        results will also be multiplied by 10000, thereby giving 4 digits of decimal precision.
    Trigonometric functions work in degrees. not radians. 
```
