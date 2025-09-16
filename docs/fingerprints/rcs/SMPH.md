## SMPH -- `0x534d5048`

```
A   (sem id flags -- id)    Allocate semaphore
D   (sem id flags -- id)    De-allocate semaphore
G   (key nsems flags -- id) Get a semaphore set
K   (id -- )                Remove a semaphore set
M   (op sem id n -- )       Multiple semaphore operations
N   (sem id -- z n)         Get number of processes waiting on semaphore
R   (sem id -- n)           Read semaphore value
W   (v sem id -- )          Write semaphore value
Z   (sem id -- )            Wait for zero semaphore

    A,D,Z Flags:
    1 - IPC_NOWAIT - Do not block
    2 - SEM_UNDO   - Undo operation on program exit
    
    G Flags:
    4096  - IPC_CREATE  - Create if it does not exist
    8192  - IPC_EXCL    - Open for exclusive use
    16384 - IPC_PRIVATE - Create a private semaphore set
    
    Low 9 bits are Unix pattern permisssions
    
    M (op sem id) is repeated on the stack n times, one set for each semaphore to be changed.
    
    N result z is the number of processes waiting for semaphore to be zero, n is the number of processes waiting for a 
    positive value
    
    All commands reflect on error with the error code on the stack:
    1  - E2BIG   - Value was too large
    2  - EACCESS - Semaphore exists but no access allowed
    3  - EAGAIN  - Operation could not go through with IPC_NOWAIT specified
    4  - EEXIST  - IPC_CREAT|IPC_EXCL were specified and semaphore exists
    5  - EFAULT  - Address isn't accessible
    6  - EFBIG   - Invalid semaphore number
    7  - EIDRM   - Semaphore set was removed
    8  - EINTR   - Sleeping on a wait queue and process receives a signal
    9  - EINVAL  - Semaphore set does not exist
    10 - ENOENT  - No semaphore set exists and IPC_CREAT was not specified
    11 - ENOMEM  - Not enough memory to create new semaphore set
    12 - ENOSPC  - Maximum semaphore limit has been reached
    13 - EPERM   - Insuficient privileges to execute command
    14 - ERANGE  - Semaphore value exceeded allowed count

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    should use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```
