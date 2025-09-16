## FING -- `0x46494e47`

```
X   (sem sem -- )   Swap two semantics
Y   (sem -- )       Pop semantic
Z   (src dst -- )   Push source semantic onto dst

    This fingerprint works by pushing and popping the semantic stacks. an empty stack will pop a reflect
    sem can be 0-25 or 'A through 'Z. Any other value is an error and will reflect
    X will swap a reflect in place of an empty stack
    Y will not reflect popping an empty semantic stack
    Z will push a reflect if the source semantic stack is empty 
```
