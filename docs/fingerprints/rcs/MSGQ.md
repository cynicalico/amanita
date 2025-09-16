## MSGQ -- `0x44d534751`

```
G   (key flags -- id)           Get message queue identifier
K   (id -- )                    Kill message queue
R   (n mtyp id flags -- .. n t) Receive message to stack
S   (.. n mtyp id flags -- )    Send bytes on stack as message
T   (id -- nmsg maxsize)        Get message system info

    G Flags:
    4096  - IPC_CREAT   - Create if id does not exist
    8192  - IPC_EXCL    - Open in exclusive mode
    16384 - IPC_PRIVATE - Create private
    low 9 bits are Unix standard access permissions
    
    R Flags:
    1 - IPC_NOWAIT  - Do not block if no messages available
    2 - MSG_NOERROR - Truncate too-long message instead of error
    
    S Flags:
    1 - IPC_NOWAIT - Do not block if message queue full
    
    All functions reflect on error with the error code on the stack
    1  - EACCESS - A message queue exists for key, but no permission to access
    2  - EEXIST  - Message queue exist when IPC_CREAT and IPC_EXCL are both specified
    3  - ENOENT  - No mesage queue exists for key and IPC_CREAT was not specified
    4  - ENOMEM  - Not enough memory
    5  - ENOSPC  - Message queue needs to be create but no more message queues allowed
    6  - EFAULT  - Address for IPC_SET or IPC_STAT not accessable
    7  - EINVAL  - Invalid value for cmd or id
    8  - EPERM   - No permissions to perform action
    9  - EAGAIN  - A blocking condition was created and IPC_NOWAIT was specified
    10 - EIDRM   - Message queue was removed
    11 - EINTR   - Sleeping on a full message queue, the process caught a signal
    12 - E2BIG   - Message size greater than specified maximum
    13 - ENOMSG  - IPC_NOWAIT was specifed and no message of the required type was available
    Maximum message size MAY BE limited to a set size. Rc/Funge-98 allows for messages up to 4096 bytes 

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    should use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```
