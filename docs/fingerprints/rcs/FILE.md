## FILE -- `0x46494C45`

```
C   (h --)              Close a file
D   (0gnirts -- )       Delete specified file
G   (h -- h 0gnirts b)  Read string from file (like c fgets)
L   (h -- h n)          Get location of file pointer
O   (Va m 0gnirts -- h) Open a file (Va=i/o buffer)
                        m   function
                        0   read
                        1   write
                        2   append
                        3   read/write
                        4   truncate read/write
                        5   append read/write
P   (h 0gnirts -- h)    Write string to file (like c fputs)
R   (h n -- h)          Read n bytes from file to buffer
S   (h m n -- h)        Seek to position n in file
                        m   function
                        0   from beginning
                        1   from current location
                        2   from end
W   (h n -- h)          Write n bytes from buffer to file

    All file functions on failure act as r.
    Functions W and R write cells as bytes, any cells containing values greater than 255 will have the top bits 
        stripped. 

Clarification

    D was not in the original spec and may not be supported in all interpreters 
```
