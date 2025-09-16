## ARRY -- `0x41525259`

```
A   (Va n x -- Va)      Store to single dimension array
B   (Va x -- Va n)      Retrieve from single dimension array
C   (Va n x y -- Va)    Store to two dimension array
D   (Va x y -- Va n)    Retrieve from two dimension array
E   (Va n x y z -- Va)  Store to three dimension array
F   (Va x y z -- Va n)  Retrieve from three dimension array
G   ( -- n)             Get maximum dimensions allowed

    Array data is stored in funge-space
    Negative array indexes are allowed
    Dimensionality of arrays is NOT tied to the dimensionality of the funge-space, however it is NOT required for an 
        interpreter to support arrays greater than funge-space dimensions. G can be used to determine what array 
        dimensionality can be used. Rc/Funge-98 supports three- dimensional arrays in all funge-spaces.
    Va is a vector in the form of the current funge-space, regardless of the array dimensionality
    Addresses used by this extension are absolute, the storage offset does NOT apply to these functions. 
```
