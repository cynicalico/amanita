## SGNL -- `0x53474E4C`

```
H   ( Va n -- ) sets code at position Va to be handler for signal n.
K   ( p n -- )  send signal n to PID p
R   ( n -- )    restore default handler for signal n.  Not a stack!
M   ( h n -- )  adjust signal mask by n with method h. 
X   ( c -- )    set current cell to character c. esp. useful with 'Y'.
Y   ( -- )      stall; ip will not advance, delta is maintained.

All signals start with their default handlers.

When a signal is received, pid of sender and signal number are pushed onto stack, in that order. A new thread is created 
to handle each signal; to exit the signal handler, kill the thread with @.

For the 'M' command, h can be one of 0(SIG_BLOCK), 1(SIG_UNBLOCK), or 2(SIG_SETMASK).

Whatever X becomes has no effect on the ip that triggered it. 
```
