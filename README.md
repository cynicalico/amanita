# amanita

amanita is a [Mycology](https://github.com/Deewiant/Mycology) [compliant](mycology_result.txt) Funge-98 interpreter.

Currently, only Befunge (2D) is supported. I have never seen a program written for Unefunge or Trefunge before (nor do I
know what a source file for Trefunge would even look like), so these may or may not ever exist.

This interpreter's handprint is `0x4e495441` ("NITA")

## Usage

See output of `amanita --help`

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

## Available Fingerprints (names link to documentation)

### Cat's Eye

| Name                                                                                                        | ID           | Description                            |
|-------------------------------------------------------------------------------------------------------------|--------------|----------------------------------------|
| [`HRTI`](https://web.archive.org/web/20250124201720/https://catseye.tc/view/Funge-98/library/HRTI.markdown) | `0x48525449` | High-Resolution Timer Interface        |
| [`MODE`](https://web.archive.org/web/20250525000331/https://catseye.tc/view/funge-98/library/MODE.markdown) | `0x4d4f4445` | Funge-98 Standard Modes                |
| [`MODU`](https://web.archive.org/web/20250523022748/https://catseye.tc/view/funge-98/library/MODU.markdown) | `0x4d4f4455` | Modulo Arithmetic Extension            |
| [`NULL`](https://web.archive.org/web/20250124201817/https://catseye.tc/view/Funge-98/library/NULL.markdown) | `0x4e554c4c` | Funge-98 Null Fingerprint              |
| [`ORTH`](https://web.archive.org/web/20250124201940/https://catseye.tc/view/funge-98/library/ORTH.markdown) | `0x4f525448` | Orthogonal Easement Library            |
| [`PERL`](https://web.archive.org/web/20250124201940/https://catseye.tc/view/funge-98/library/PERL.markdown) | `0x5045524c` | Generic Interface to the Perl Language |
| [`REFC`](https://web.archive.org/web/20250124201827/https://catseye.tc/view/Funge-98/library/REFC.markdown) | `0x52454643` | Referenced Cells Extension             |
| [`ROMA`](https://web.archive.org/web/20250523145159/https://catseye.tc/view/funge-98/library/ROMA.markdown) | `0x524f4d41` | Funge-98 Roman Numerals                |
| [`TOYS`](https://web.archive.org/web/20211201092300/https://catseye.tc/view/funge-98/library/TOYS.markdown) | `0x544f5953` | Funge-98 Standard Toys                 |

### RCS

| Name                                                                                            | ID           | Description                     |
|-------------------------------------------------------------------------------------------------|--------------|---------------------------------|
| [`DIRF`](https://web.archive.org/web/20230617132045/https://rcfunge98.com/rcsfingers.html#DIRF) | `0x44495246` | Directory functions extension   |
| [`EVAR`](https://web.archive.org/web/20230617132045/https://rcfunge98.com/rcsfingers.html#EVAR) | `0x45564152` | Environment variables extension |
| [`FILE`](https://web.archive.org/web/20230617132045/https://rcfunge98.com/rcsfingers.html#FILE) | `0x46494c45` | File I/O functions              |
| [`FPDP`](https://web.archive.org/web/20230617132045/https://rcfunge98.com/rcsfingers.html#FPDP) | `0x46504450` | Double precision floating point |
| [`FPSP`](https://web.archive.org/web/20230617132045/https://rcfunge98.com/rcsfingers.html#FPSP) | `0x46505350` | Single precision floating point |
| [`SUBR`](https://web.archive.org/web/20230617132045/https://rcfunge98.com/rcsfingers.html#SUBR) | `0x53554252` | Subroutine extension            |

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
