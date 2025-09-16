## UNIX -- `0x554e4958`

```
A   (id -- )                Set effective uid
B   (id -- )                Set effective gid
C   (0gnirts uid gid -- )   Change owner of a file
D   ( -- 0gnirts)           Get domain name of host
E   ( -- id)                Get effective uid
G   ( -- id)                Get real gid
H   ( -- id)                Get host id
K   (mask -- old)           Set umask
M   (0gnirts mode -- )      Change file access
N   ( -- 0gnirts)           Get host name
P   ( -- id)                Get process id
R   ( -- id)                Get effective gid
S   (id -- )                Set uid
T   (id -- )                Set gid
U   ( -- id)                Get real uid

    All functions reflect on error
    C: if uid or gid is -1 that component will not be set 
```
