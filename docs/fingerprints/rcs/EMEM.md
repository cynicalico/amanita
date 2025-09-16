## EMEM -- `0x454d454d`

```
A   (size -- hnd)       Allocate memory
F   (hnd -- )           Free memory
G   (hnd n addr --)     Get bytes from memory
P   (.. hnd n addr --)  Put bytes into memory
R   (hnd size -- )      Reallocate memory

    Errors on any instructions will reflect
    
    This is essentially an interface into malloc.
    
    As far as implementing this, hnd can be the direct pointer if it fits within the cell size of the interprter, or 
    else a seperate list can be maintained and this would be the handle into the list.
    
    Stack entries written to memory using P truncate to bytes. 
```
