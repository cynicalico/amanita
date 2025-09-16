## SGNE -- `0x53474e45`

```
A   (sec -- old)    Set alarm
I   ( -- pid)       Get PID of current process
L   (sec -- )       Sleep
P   ( -- )          Pause until signal
S   (s -- )         Send signal to self
T   ( -- )          Abort

    These instructions affect the interpreter and therefore all IPs will be subject to the effects of these functions.
    L - If process is worken up because of a signal, then the IP is reflected and the stack will contain the number of 
        unslept seconds. If the Process wakes up normally after the sleep period is over then the IP continues along its 
        delta and nothing will be pushed onto the stack
    S - Reflects on error 
```
