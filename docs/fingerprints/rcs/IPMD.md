## IPMD -- `0x49504d44`

```
B   ( -- )  Run in BeFunge mode
D   ( -- )  Run in default mode for VM
Q   ( -- d) Query for mode IP is running in
T   ( -- )  Run in TreFunge mode
U   ( -- )  Run in UneFunge mode

    These commands only affect the IP executing them. Other IPs running in the same VM are not affected.
    
    These functions affect how the IP interprets instructions, they will be limited or expanded based upon the mode the 
    IP is running in.
    
    These modes are NOT affected by the mode the VM is running in. It is allowed to set an IP into TreFunge mode in a 
    BeFunge funge-space. The TreFunge instructions must however work.
    
    Vectors will be affected by the mode the IP is running in. Example: If a VM is running in BeFunge mode and an IP is 
    running in TreFunge mode and wants to pop a vector, it will pop a 3 coordinate vector, likewise if the IP were 
    running in UneFunge mode, then it will pop a single value vector.
    
    When running in a mode less than Funge-Space, coordinates above the mode of the IP will be set for the coordinate of 
    the ip. For example if the IP is at 20,30 then exectues U and then a g command is exectued, g will retrieve a value 
    from row 30, not 0
    
    When running in a mode less than Funge-Space, x will set unpopped delta values to 0.
    
    Funge-space supports up to TreFunge when using this extension 
```
