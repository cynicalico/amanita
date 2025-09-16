## EXEC -- `0x45584543`

```
A   (V n -- )   Execute command at vector n times from current location, IP will be pointed at the A
B   (V n -- )   Like A but IP will be reset each iteration
G   (V --)      Set position of IP to vector
K   (n -- )     what k should have been, will skip following instruction if it is the iterated one
R   (n --)      Like K but IP is reset after each iteration
X   (cmd n --)  execute command on stack n times

    An IP reset as used in B and R reset the IP position only, nothing else
    On X, cmd is removed from the stack before it is iterated 
```
