## STRN -- `0x5354524E`

```
A   (0gnirts 0gnirts -- 0gnirts)    Append bottom string to upper string
C   (0gnirts 0gnirts -- n)          Compare strings
D   (0gnirts --)                    Display a string
F   (0gnirts 0gnirts -- 0gnirts)    Search for bottom string in upper string
G   (Va -- 0gnirts)                 Get string from specified position
I   ( -- 0gnirts)                   Input a string
L   (0gnirts n -- 0gnirts)          Leftmost n characters of string
M   (0gnirts s n -- 0gnirts)        n characters starting at position s
N   (0gnirts -- 0gnirts n)          Get length of string
P   (0gnirts Va -- )                Put string at specified position
R   (0gnirts n -- 0gnirts)          Rightmost n characters of string
S   (n -- 0gnirts)                  String representation of a number
V   (0gnirts -- n)                  Retreive value from string

    functions G and P use deltas of 1,0,0 

Clarification

    For M, requesting zero characters from the string will return an empty string. Other interpreters may have 
    implemented this as reflecting
    
    For M, specifying a length that would go beyond the end of the string is legal and will return from the start til 
    the end of the string. Other interpreters may have implemented this as reflecting.
    
    For M, specifying a negative start or a start beyond the end of the string is an error and will reflect. Other 
    interpreters may have implemented this as returning a null string
    
    For R,L,M Requesting 0 or more characters from an empty string returns an empty string. Other interpreters may have 
    implemented this as reflecting.
    
    Specifiying a negative size for R,L,M is an error and will reflect. Other interpreters may have implemented this as 
    returning a null string
    
    For R,L requesting more characters than the length of the string will return the whole string. Other interpreters 
    may have implemented this as reflecting or returning a null string.
    
    For V, a non-numeric value in the string is not an error and will push a 0. Other interpreters may have implemented 
    this as reflecting. This function is implemented as the c function atoi (or equivalent for cell size), It will not 
    search the string for a numeric value. 
```
