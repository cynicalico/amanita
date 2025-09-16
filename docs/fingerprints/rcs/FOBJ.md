## FOBJ -- `0x464f424a`

```
D   (ref -- )               Destruct an object
I   (0gnirts -- ref)        Instantiate an object
M   (nargs ref meth -- ret) Call an object method
N   (ref -- 0gnirts)        Get object name

    All functions reflect upon error
    
    ref referes to an index into a global object table
    
    In Funge/Multiverse each universe has its own global object table
    
    I 0gnirts referes to the funge file containing the code for the object
    
    M nargs specifies how many stack entries to transfer to the IP created in the object funge-space. Stack order is 
    preserved. The count is NOT placed on the destination IPs stack.
    
    Funge files are in trefunge format. Each z level is a message handler, therefore message handlers start at 0 and go 
    up.
    
    Funge-space for objects is in Trefunge mode.
    
    Starting point for any message handler is always [0][0][m] with a delta of [1][0][0]
    
    if cell[0][0][m] is a space then cause M to reflect
    
    Object method calls execute in a single tick
    
    The full capabilites of the funge engine should be available to object message handlers, this includes i,o,=,t, 
    fingerprints, etc.
    
    Funge multiverse is not required for this extension, but each object must be its own funge-space.
    
    In Rc/Funge-98, each object is a stand-alone VM that is NOT part of the funge multiverse.
    
    Funge-space of a loaded object must remain consistant across method calls. In other words, if the method modifies 
    its own funge-space, that change must remain for further method calls.
    
    When the last IP terminates a value is popped off its stack, that many stack entries are transferred back to the 
    calling IP. Order is preserved.
    
    Global object table should be initialized at interpreter startup, and not by loading this fingerprint
    
    Object reference numbers may be reused 
```
