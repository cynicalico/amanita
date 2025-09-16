## SUBR -- `0x53554252`

```
A   ( -- )              Set absolute mode
C   (Va n -- Va Vd .. ) Call a subroutine
J   (Va -- )            Jump to another location
O   ( -- )              Set Relative mode
R   (Va Vd .. n -- ..)  Return from subroutine

    Default mode when SUBR is loaded is absolute mode.
    Mode setting is individual per IP
    Relative mode only affects the vectors from J and C. R should always return to the point of the original Call
    J and C each set delta to 1,0,0 at target, R restores the delta before the call.
    When C is executed, the tos specifies how many stack entries to retrieive from the stack and then place back onto 
        the stack after the retrurn address and delta vectors are pushed on the stack.
    When R is executed, the tos specifies how many stack entries to retrieve from the stack before retrieving the delta 
        and address vectors. The popped entries will be restored to the stack after the vectors are popped.
    Vectors in this function work directly on the IP and not through funge-space, therefore the IP storage offset does 
        not apply to these vectors. 

Clarification

    A and O were not part of the original spec and therefore there may be interpreters that will not handle these.
    
    If A and O are not supported then absolute mode should be the mode that C and J will operate in. Some interpreters 
    may have however implemented these in relative mode 
```
