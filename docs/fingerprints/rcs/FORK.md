## FORK -- `0x464F524B`

```
T   ( -- pid flg)   Fork new process

    T - flg=0 for parent, 1 for child.
    T - child gets parent's pid, parent gets child's pid
    T - child has its IP delta reflected
    T - flg=-1 error in fork, does not reflect
    Other IPs in the forked process are unaffected 

Clarification

    The function forks the actual interpreter, creating an additional interpreter process. 
```
