## SCKE -- `0x53434b45`

```
[ H ] Get address by hostname
-----------------------------

Stack input: 0gnirts
Stack output: [addr]

H gets the string from stack (formatted as a FQDN or dotted-decimal IP
address) and returns the 32 bit address, if possible.

[ P ] Peek for incoming data
----------------------------

Stack input: [s]
Stack output: [val]

P checks if data is available to read from socket (s), output value (val) is
true if there is, and false if there isn't.
```
