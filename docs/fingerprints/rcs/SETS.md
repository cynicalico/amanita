## SETS -- `0x53455453`

```
A   (set v -- set)                  Add value to set
C   (set -- set n)                  Get count of items in set
D   (set -- set set)                Duplicate set on stack
G   (Vdlt Vsrc -- set)              Get set from Funge-space
I   (seta setb -- seta setb setr)   Instersection of sets
M   (set v -- set r)                r=0 if v is not member of set, else r=1
P   (set -- set)                    Print a set
R   (set v -- set)                  Remove value from set
S   (seta setb -- seta setb setr)   Subtract setb from seta
U   (seta setb -- seta setb setr)   Union of sets
W   (set Vdlt Vdst -- set)          Write set to Funge-space
X   (seta setb -- setb seta)        Swap two sets
Z   (set -- )                       Drop set from stack

    All reflect if stack does not appear to have a proper set
    Sets are in the form (v1 v2 v3 .. vn ) n, n being closes to top of stack denotes how many items are in the set
    Nearly all instructions leave the work sets on the stack at the completion of the instruction
    Order within the sets need not be maintained. These are sets and not arrays 
```
