# amanita

amanita is a [Mycology](https://github.com/Deewiant/Mycology) [compliant](mycology_result.txt) (be)Funge-98 interpreter.

### Usage

See output of `amanita --help`

### TODO

- [ ] CLI arguments and ENV variables (`y`)
- [ ] User input (`&` and `~`)
- [ ] Execute (`=`)
- [ ] Fingerprints
- [ ] Visual editor/debugger
    - Built on top of [mizu](https://github.com/cynicalico/mizu), my graphics engine (dogfooding!)

### Fingerprints

TODO

### Mycology UNDEFs

```
UNDEF: # across left edge skips easternmost cell in file
UNDEF: # across left edge hits easternmost cell on line

UNDEF: o doesn't remove spaces prior to newline-valued cells
UNDEF: o didn't write EOL to EOF

UNDEF: k with a negative argument executes 0 times or less often than the absolute value of the argument
UNDEF: the empty string wrapped around the edge of space contains 1 character(s) (hopefully spaces)
UNDEF: ( with a negative count reflects and pops 0 times or less than the absolute value of the count
UNDEF: ) with a negative count reflects and pops 0 times or less than the absolute value of the count
```

### Dependencies

- [argparse](https://github.com/p-ranav/argparse)
- [mizu](https://github.com/cynicalico/mizu)
