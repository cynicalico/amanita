# amanita

amanita is a [Mycology](https://github.com/Deewiant/Mycology) [compliant](mycology_result.txt) Funge-98 interpreter.

Currently, only Befunge (2D) is supported. I have never seen a program written for Unefunge or Trefunge before (nor do I
know what a source file for Trefunge would even look like), so these may or may not ever exist.

This interpreter's handprint is `0x4e495441` ("NITA")

## Usage

See output of `amanita --help`

## Archival

There is not much of a community for this language out there anymore. As a result there is a *lot* of link rot.

The major implementation where the majority of fingerprints come from, Rc/Funge, has been abandoned and no longer has a
functional website (GitHub user kronosta has created an archive of the source
code [here](https://github.com/kronosta/rcfunge/tree/main)).

To help with this, I have included the complete [Funge-98 specification](docs/funge98.md) and [ERRATA](docs/errata.md)
document. The original documents are still available [here](https://catseye.tc/view/funge-98/doc/funge98.markdown) if
desired, though there's no telling for how many more years this will be true.

Additionally, all fingerprint specifications I could find are located [here](docs/fingerprints.md). Where the links are
still active, I have included them. For all RCS fingerprints, I have not included a link, though one could be added to
the internet archive similar to what [esolangs.org](https://esolangs.org/wiki/Funge-98#Fingerprints) has done.

## TODO

- [x] CLI arguments and ENV variables (`y`)
- [x] User input (`&` and `~`)
- [ ] Execute (`=`)
    - Currently reflects, possibly add multiple interpreter options (Python?)
- [x] Fingerprints
- [ ] Visual editor/debugger
    - Built on top of [mizu](https://github.com/cynicalico/mizu), my graphics engine (dogfooding!)
    - TODO
        - [ ] Don't close debugger on q instruction
        - [ ] Reset and re-run
        - [ ] Follow IPs other than first
        - [ ] Show stacks beyond SOSS
        - [ ] GUI controls (currently all keyboard)
        - [ ] Controllable tick speed
        - [x] Display loaded fingerprint(s)
        - [ ] Colorize instructions
        - [ ] Editing

## Fingerprints

See [docs/fingerprints.md](docs/fingerprints.md).

## Notable Implementation Details

### Input Decimal (`&`)

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

#### Base instruction set

```
UNDEF: # across left edge skips easternmost cell in file
UNDEF: # across left edge hits easternmost cell on line

UNDEF: o doesn't remove spaces prior to newline-valued cells
UNDEF: o didn't write EOL to EOF

UNDEF: k with a negative argument executes 0 times or less often than the absolute value of the argument
UNDEF: the empty string wrapped around the edge of space contains 1 character(s) (hopefully spaces)
UNDEF: ( with a negative count reflects and pops 0 times or less than the absolute value of the count
UNDEF: ) with a negative count reflects and pops 0 times or less than the absolute value of the count

UNDEF: IVXLCDM didn't reflect: child IP has ROMA loaded
```

#### CPLI

```
UNDEF: abO outputs 10+11i 
UNDEF: 0a-bO outputs -10+11i 
UNDEF: a0b-O outputs 10-11i 
UNDEF: 0a-0b-O outputs -10-11i 
```

#### FIXP

```
UNDEF: 2aaaa****J pushes -9223372036854775808
UNDEF: 002-R pushes -9223372036854775808
UNDEF: 00R pushes 1
```

#### FPSP

```
UNDEF: cFP outputs 12.000000 
UNDEF: 0"1234.567890"R results in 1234.567871
UNDEF: aFeFA results in 24.000000 (24)
UNDEF: cF7FS results in 5.000000 (5)
UNDEF: 6FaFM results in 60.000000 (60)
UNDEF: ASMDF say 355/113 is 3.141593 (3.141593)
UNDEF: D says 1/0 is inf (NaN or +infinity)
UNDEF: D says -1/0 is -inf (NaN or -infinity)
UNDEF: B says sin(4.2) is -0.871576 (-0.871576)
UNDEF: C says cos(42) is -0.399985 (-0.399985)
UNDEF: T says tan(-.42) is -0.446573 (-0.446573)
UNDEF: E says asin(2) is -nan (actually complex: NaN)
UNDEF: H says acos(0) is 1.570796 (1.570796)
UNDEF: G says atan(100) is 1.560797 (1.560797)
UNDEF: K says ln(0) is -inf (-infinity)
UNDEF: K says ln(1) is 0.000000 (0)
UNDEF: K says ln(2) is 0.693147 (0.693147)
UNDEF: L says log10(20) is 1.301030 (1.301030)
UNDEF: X says exp(3) is 20.085537 (20.085537)
UNDEF: N says -0 is -0.000000 (-0)
UNDEF: V says abs(-15) is 15.000000 (15)
UNDEF: Q says sqrt(8) is 2.828427 (2.828427)
UNDEF: Y says pow(-8, 9) is -134217728.000000 (-134217728)
UNDEF: Y says pow(2, -7) is 0.007812 (0.007813)
```

#### FPDP

```
UNDEF: cFP outputs 12.000000 
UNDEF: 0"1234.567890"R results in 1234.567890
UNDEF: aFeFA results in 24.000000 (24)
UNDEF: cF7FS results in 5.000000 (5)
UNDEF: 6FaFM results in 60.000000 (60)
UNDEF: ASMDF say 355/113 is 3.141593 (3.141593)
UNDEF: D says 1/0 is inf (NaN or +infinity)
UNDEF: D says -1/0 is -inf (NaN or -infinity)
UNDEF: B says sin(4.2) is -0.871576 (-0.871576)
UNDEF: C says cos(42) is -0.399985 (-0.399985)
UNDEF: T says tan(-.42) is -0.446573 (-0.446573)
UNDEF: E says asin(2) is -nan (actually complex: NaN)
UNDEF: H says acos(0) is 1.570796 (1.570796)
UNDEF: G says atan(100) is 1.560797 (1.560797)
UNDEF: K says ln(0) is -inf (-infinity)
UNDEF: K says ln(1) is 0.000000 (0)
UNDEF: K says ln(2) is 0.693147 (0.693147)
UNDEF: L says log10(20) is 1.301030 (1.301030)
UNDEF: X says exp(3) is 20.085537 (20.085537)
UNDEF: N says -0 is -0.000000 (-0)
UNDEF: V says abs(-15) is 15.000000 (15)
UNDEF: Q says sqrt(8) is 2.828427 (2.828427)
UNDEF: Y says pow(-8, 9) is -134217728.000000 (-134217728)
UNDEF: Y says pow(2, -7) is 0.007812 (0.007813)
```

#### MODE

```
UNDEF: IQ{ moves cells from SOSS to TOSS by popping and pushing according to the modes
UNDEF: stack stack seems unaffected by invertmode
UNDEF: stack stack seems unaffected by queuemode
```

#### HRTI

```
UNDEF: E without M did not reflect
```

#### STRN

```
UNDEF: 00L leaves 0 on stack
UNDEF: "ooF"01-L reflects
UNDEF: 00R leaves 0 on stack
UNDEF: "ooF"01-R reflects
UNDEF: 000M reflects
UNDEF: "ooF"101-M reflects
UNDEF: "ooF"01-1M reflects
UNDEF: "ooF"42M reflects
UNDEF: "ooF"24M leaves "o" on stack
```

#### TOYS

```
UNDEF: 12B leaves stack as [ -1 3 ] (from top to bottom)
UNDEF: 0f-03-H is -2, meaning H did a signed right shift
UNDEF: F pops j after i
UNDEF: 02T goes through
UNDEF: Z in Befunge reflects
```

## Dependencies

- [argparse](https://github.com/p-ranav/argparse)
- [utf8-cpp](https://github.com/nemtrif/utfcpp)
- [mizu](https://github.com/cynicalico/mizu)
