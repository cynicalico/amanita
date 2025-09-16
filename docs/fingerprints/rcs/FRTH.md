## FRTH -- `0x46525448`

```
D   ( .. -- .. n)       Push depth of stack to tos
L   ( .. n -- .. n)     Forth Roll command
O   (a b -- a b a)      Forth Over command
P   (.. n -- .. n)      Forth Pick command
R   (a b c -- b c a)    Forth Rot command

    Stack operations are subject to the modes set by MODE 

Clarification

    P should reflect on a negative argument
    P should push 0 if argument is greater than stack size
    L should act like forth -roll with a negative argument
    L with an argument larger than the stack size is allowed, enough zeroes will be created in order to fulfill the 
        request. Example: n543210a-L will leave a stack of: 2 3 4 5 0 0 0 0 0 0 1   
    L,P the top of stack is position 0 
```
