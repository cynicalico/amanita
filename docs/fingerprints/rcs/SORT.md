## SORT -- `0x534f5254`

```
B   (Va Vld Vbd w n -- )    Sort block in funge-space
F   (Va Vd n -- )           Sort funge-space
K   (.. n -- ..)            Sort stack
S   (Va Vld Vsd w n -- )    Sort strings

    Reflect if n<=0
    Reflect if w<=0
    Any delta of all zeros is an error and will reflect
    All arguments are popped from the stack before error checking
    B Sorts only on first cell in each entry 
```
