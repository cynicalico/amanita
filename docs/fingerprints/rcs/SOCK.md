## SOCK -- `0x534F434B`

```
A   (s -- prt addr s)   Accept a connection
B   (s ct prt addr -- ) Bind a socket
C   (s ct prt addr -- ) Open a connection
I   (0gnirts -- addr)   Convert an ascii ip address to a 32 bit address
K   (s -- )             Kill a connection
L   (n s -- )           Set a socket to listening mode (n=backlog size)
O   (n o s -- )         Set socket option
R   (V l s -- bytes)    Receive from a socket,
S   (pf typ pro -- s)   Create a socket
W   (V l s -- retcode)  Write to a socket

note: All functions act as r on failure

addr:   32 bit destination address

ct:     1=AF_UNIX
        2=AF_INET

o:      1=SO_DEBUG
        2=SO_REUSEADDR
        3=SO_KEEPALIVE
        4=SO_DONTROUTE
        5=SO_BROADCAST
        6=OOBINLINE

pf:     1=PF_UNIX
        2=PF_INET

prt:    Port to connect to

s:      Socket identifier

typ:    1=SOCK_DGRAM
        2=SOCK_STREAM

pro:    1=tcp
        2=udp

V:      Vector to io buffer

Clarification

    The socket descriptor s used in these functions could be either an index into a table of open sockets or else use 
    the id returned by the OS. In either case the socket identifier needs to be usable by other IPs, therefore a socket 
    table that is global to all IPs or else use the OS descriptors.
    
    ct=1 and pf=1 are a broken spec and should not be implemented. Usage of either of these should reflect. 
```
