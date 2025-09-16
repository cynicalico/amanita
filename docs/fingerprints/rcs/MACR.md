## MACR -- `0x4d414352`

```
A-Y ( -- )  Execute specified macro
Z   (V -- ) Specify where macro block is located

    Macros are simple mini-funge like Befunge-like subroutines that execute in a single tick
    
    The Macro block may be located anywhere in Funge-Space. Each macro runs with a delta of 1,0,0 (Befunge like macros) 
    macro A is located at the macro block vector, Macro B is one line below at the same starting X, C below that, etc
    
    Macros execute with the IP where it is! not in the macro space
    
    Instructions affect the IP that called the Macro
    
    A macro teminates when either a @ is found or an invalid instruction is found
    
    Most standard Funge-98 instructions can be used within macro blocks, but keep in mind they affect the IP where it is 
    and not inside the macro block
    
    A-Z generally are not allowed within macros, however some A-Z commands perform special functions when executed 
        inside of a macro:
    A - like _ but affects the macro pointer instead of the IP
    B - Move IP backwards
    E - Change macro delta to 1,0,0
    F - Move IP forwards
    G - Get next macro cell onto stack
    I - like | but affects the macro pointer instead of the IP
    J - like j but affects the macro pointer instead of the IP
    L - like [ but affects the macro pointer instead of the IP
    N - Change macro delta to 0,-1,0
    R - like ] but affects the macro pointer instead of the IP
    S - Change macro delta to 0,1,0
    T - like # but affects the macro pointer instead of the IP
    W - Change macro delta to -1,0,0
```
