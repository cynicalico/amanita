## TRGR -- `0x54524752`

```
A-Y ( -- )  Activate a trigger
Z   (V -- ) Specify where trigger table is located

    When an IP executes a trigger a new IP is created that will then run concurrently with the rest of the IPs. The new 
        IP will be generated in the same from as t, but will contain the position associated with the relevent entry in 
        the trigger table
    The original IP is unaffected and continues to run normally after having executed the trigger
    The trigger table contains executable code for the new IP, the code for A begins at the trigger table vector, B 
        starts at the same X one line lower, C below that, etc
    Both the original IP and the new IP will have the uid of the other pushed onto its stack 

Clarification

    Like in command 't', the newly created IP should execute first before the triggering IP.
    
    Initial direction of the trigger IP is 1,0,0. 
```
