## TRDS -- `0x54524453`

```
C   ( -- )  Continue normal time
D   (V -- ) Set absolute destination space coordinates
E   (V -- ) Set relative destination space corrdinates
G   ( -- n) Get current time point
I   ( -- )  Set inverse settings
J   ( -- )  Initiate a jump
P   ( -- n) Maximum distance in the past ip can jump to
R   ( -- )  Reset all tardis controls to default
S   ( -- )  Stop time
T   (n -- ) Set absolute destination time
U   (n -- ) Set relative destination time
V   (V -- ) Set destination vector

Notes to time travelling ips:

    Usage of time travel can be very punishing on the performance of the funge interpreter. If travel is performed to 
the past, the interpreter must be capable of reproducing all conditions that existed at the destination time, which 
includes all ips, stacks, and funge space cells. Some interpreters may only store time snapshots from only so far back 
(The furthest point in the past that can be jumped to can be determined with the P command). The RCS interpreter 
essentially reruns from point 0 and therefore all points in time can be jumped to (note: this can be quite time 
consuminmg if the destination time point is tens or hundreds of thousands of instructions from time point 0).

    Time travel into the future is not quite so punishing. The ip that time travels will merely be frozen until time 
catches up with it, at which point it will continue to execute.

Time travel into the past has the following consequences:

    1.  It is not possible to travel further back than time point 0. Attempts to travel beyond the beginning will leave 
        the ip at time point 0.
    2.  The original ip will still be born as per normal. example. If ip #2 is born at time 100 and then performs a jump 
        at time 200 to time 50, ip #2 will be born again at time 100, and there will now be 2 of them (the newly born ip 
        #2 in addition to the one that jumped) When the newly born ip #2 reaches the time it jumped (time point 200) it 
        will cease to exist, it will not perform another jump into the past, the original ip #2 however can still jump. 
        If the new ip #2 performs a time jump earlier than when the original jumped, the original will cease to exist.
    3.  An ip travelling in the past can kill its parent prior to its own birth, and will still exist.
    4.  A time travelling ip will retain its memory, in other words, its stack will be the same after the jump as before. 
        Also, unless the jump also included a space jump, the location will be the same physical space coodinates as when 
        it jumped.
    5.  An ip that perfroms a time jump without a space jump will execute the next instruction as if it had never jumped.
    6.  An ip that performs a space jump (with or without a time jump) will first execute the instruction it jumped to. 

When Multiple IPs Time Travel:

    In order to decrease the work on the interpreter, it is not necessary for the interpreter to remember future events. 
In other words when an ip travels back in time, everything occuring after the time point of destination need not recur 
if it does not occur in the further course of the program. When IPs time travel, only those ips that are currently in 
funge space at the time of arrival (either normally or from time travelling) will exist. Any ips that time travelled to 
a point later in time will not recur, unless the original time travel for these ips recur. Here are two examples to 
illustrate this point:

Example 1: Ip#1 travels back in time and arrives to time point 100, Ip#2 travels back to point 150. At point 150 the 
    time travelled copies of both ips will exist.

Example 2: Ip#1 travels back in time and arrives to time point 150, Ip#2 travels back to point 100. At the point where 
    ip#2 arrives, ip#1 has not yet arrived and therefore does not exist, it will also not exist when time point 150 
    arrives, only when the original jump for Ip#1 occurs, will history again be rewritten.

Tardis Operators Manual:

    1.  Before attempting any jumps, the ip's tardis should be reset to clear out any unwanted coordinates.
    2.  There are three coordinate settings: Space coordinates, vector after jump, and destination time. Any coordinate 
        that is not set will remain at the last setting, or at default if the tardis is reset.
    3.  Default coordinates are the current time, space, and vector.
    4.  Absolute coordinates are based from time point 0, and space 0,0,0.
    5.  Relative coordinates are based from the point the jump is actually made.
    6.  All tardis coordinates are retained following a jump.
    7.  The I command will set the tardis for the last source jump point. 
    
Stopping Time:

    An ip that issues a <S>top time command freezes the time counter. All other ips will be frozen until a <C>ontinue 
time command is executed. During the time that time is stopped, only the ip that executed the S command will continue to
run. For the purposes of time travel, the time used while time is stopped does not actually exist, and therefore cannot 
be jumped to. In other words everything the ip does is considered to have taken no time. If an ip that stops time is 
terminated, time will be continued
```