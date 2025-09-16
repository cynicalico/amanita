## MODU -- `0x4d4f4455`

Taken from https://catseye.tc/modules/Funge-98/library/MODU.markdown

The MODU fingerprint implements some of the finer, less-well-agreed-upon
points of modulo arithmetic. With positive arguments, these instructions
work exactly the same as `%` does. However, when negative values are
involved, they all work differently:

`M`: signed-result modulo

`U`: Sam Holden's unsigned-result modulo

`R`: C-language integer remainder