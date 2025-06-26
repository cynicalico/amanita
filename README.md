# amanita

amanita is a [Mycology](https://github.com/Deewiant/Mycology) [compliant](mycology_result.txt) (be)Funge-98 interpreter.

### Usage

`amanita <file>`

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

UNDEF: # across left edge skips easternmost cell in file <br>
UNDEF: # across left edge hits easternmost cell on line <br>

UNDEF: o doesn't remove spaces prior to newline-valued cells <br>
UNDEF: o didn't write EOL to EOF <br>

UNDEF: k with a negative argument executes 0 times or less often than the absolute value of the argument <br>
UNDEF: the empty string wrapped around the edge of space contains 1 character(s) (hopefully spaces) <br>
UNDEF: ( with a negative count reflects and pops 0 times or less than the absolute value of the count <br>
UNDEF: ) with a negative count reflects and pops 0 times or less than the absolute value of the count <br>
