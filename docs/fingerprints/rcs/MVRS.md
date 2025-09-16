## MVRS -- `0x4d565253`

```
B   (0gnirts flgs lng dim -- )  Big-Bang, create another universe
C   ( -- n)                     Number of existing universes
F   (0gnirts Vd Vs Vsz -- )     Copy funge-space from another universe
G   (0gnirts Vpos Vdlt -- )     Go to another universe
J   (0gnirts -- )               Jump to another universe
N   ( -- 0gnirts)               Get name of current universe
P   (0gnirts Vd Vs Vsz -- )     Copy funge-space to another universe

    F source vector must be x,y,z even if source universe is unefunge or befunge
    F size vector is based upon current universe
    J keeps position and delta
    Any command specifying a universe will reflect if the universe does not exist 

B Flags:
    0 - Default
    Flags from 512 upwards are implementation dependent and may vary from interpreter to interpreter. Flags 256 and 
        below are reserved and may change in the future.
    Interpreters are not required to support any flags
    If an unsupported flag below 512 is used, B should reflect
    If an unsupported flag 512 and up is used, B should ignore it 

dim:
    0 - Default
    1 - Unefunge
    2 - Befunge
    3 - Trefunge
    n - Other funges

lng:
    0 - Default
    1 - Funge/93
    2 - Funge/98
    3 - Funge/108

    All others reserved and may change in the future
    If an unsupported language is specified, B should reflect 

Defaults:
    Defaults are the creating universe's flags, dimensions, and language 
```
