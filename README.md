# amanita

amanita is a [Mycology](https://github.com/Deewiant/Mycology) [compliant](mycology_result.txt) (be)Funge-98 interpreter.

### Usage

See output of `amanita --help`

### TODO

- [ ] CLI arguments and ENV variables (`y`)
- [x] User input (`&` and `~`)
- [ ] Execute (`=`)
- [ ] Fingerprints
- [ ] Visual editor/debugger
    - Built on top of [mizu](https://github.com/cynicalico/mizu), my graphics engine (dogfooding!)

### Fingerprints

TODO

### Notable Implementation Details

#### Decimal input (`&`)

The Funge-98 specification reads:

> Decimal input reads and discards characters until it encounters decimal digit characters
> at which point it reads a decimal number from those digits, up until (but not including)
> the point at which input characters stop being digits, or the point where the next digit
> would cause a cell overflow, whichever comes first

This leads to an interesting dilemma with line-buffered input for integers. Consider the following
input: <br>

`abc1234\n`

"up until (but not including)" would imply leaving the newline in the input stream, but this gives
very unintuitive behavior if followed by a `~` (Input Character) command, which will happily eat the newline but is
probably not what was desired.

For comparison, consider the following similar input: <br>

`abc1234abc\n`

Following the same logic, it would be expected that the `abc\n` is left in the input stream, and in this case,
it very well could be desired.

As an attempt to perform the most "intuitive" action, amanita will discard the newline only if it immediately follows
an integer, and otherwise will un-get the final non-digit character.

Checking what other interpreters do may be desirable in the future.

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
