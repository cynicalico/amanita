## SMEM -- `0x534d454d`

```
G   (key size flags -- id)      Get shared memory segment
K   (id -- )                    Remove shared memory segment
R   (n addr id flags -- ..)     Read bytes from shared memory
T   (id -- size)                Get shared memory info
W   (.. n addr id flags -- )    Write bytes to shared memory

    G Flags:
    4096  - IPC_CREATE  - Create segment if it does not exist
    8192  - IPC_EXCL    - Open for exclusive use
    16384 - IPC_PRIVATE - Create private

    Low 9 bits are Unix pattern permisssions

    R Flags:
    1 - SHM_RDONLY - Attach segment readonly

    W Flags:
    1 - SHM_RDONLY - Attach segment readonly

    All commands reflect on error with the error code on the stack:
    1  - EACCES    - User does not have permission to access
    2  - EEXIST    - IPC_CREAT|IPC_EXCL was specified and sement exists
    3  - EFAULT    - Address is not accessable
    4  - EIDRM     - Shared memory segment was removed
    5  - EINVAL    - id is not a valid id
    6  - ENFILE    - System limit on open files has been reached
    7  - EOVERFLOW -
    8  - ENOENT    - No segment exists for key and IPC_CREAT was not specified
    9  - ENOMEM    - No memory could be allocated
    10 - ENOSPC    - All possible shared memory IDs have been taken
    11 - EPERM     - No permissions

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    hould use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```
