## IMAP -- `0x494D4150`

```
C   ( -- )          Clear all instruction remaps
M   (new old -- )   Remap an instruction
O   (n -- )         Return instruction n to its old function

Clarification

    This extension is intended to map instructions in the 0-255 range. Other interpreters may have a more limited or 
    more expanded range
    
    Attempting to map instructions outside of the 0-255 range reflect. Some interpreters may ignore an out of range map
    without reflecting
    
    Chained remaps are not supported by this extension. Only a single level of mapping is supported. Other interpreters
    may have implemented chained remaps 
```
