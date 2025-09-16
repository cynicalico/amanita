## JSTR -- `0x4a535452`

```
P   (Vd Va n -- )           pop n cells off of the stack and write at Va with delta Vd.
G   (Vd Va n -- 0gnirts)    read n cells from position Va and delta Vd, push on stack as a string.

This extension is the Right Way to handle string writing/reading in fungespace. multidimensionality, people!
```
