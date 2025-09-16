## RAND -- `0x52414e44`

```
I   (n -- r)    Integer random number 0 <= r < n
M   ( -- max)   Maximum allowed integer range
R   ( -- r)     FPSP random number 0 <= r < 1
S   (n -- )     Reseed rng with n
T   ( -- )      Reseed rng with system timer or other source

    I n will be considered to be unsigned
    
    I n=0 is an error and will reflect 
```
