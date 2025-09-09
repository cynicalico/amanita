### TODO: Spell Check, many of these specs have obvious (English) typos

# Fingerprint Specifications

This is a reference for all the Funge-98 specifications that I could find.

The Mycology column indicates whether an extension is tested in Mycology.

| Implemented | Mycology | Name |  Fingerprint  |         Origin         | Description                             |
|:-----------:|:--------:|:----:|:-------------:|:----------------------:|:----------------------------------------|
|      ✅      |    ✅     | HRTI | `0x48525449`  | Cat's Eye Technologies | High-Resolution Timer Interface         |
|      ✅      |    ✅     | MODE | `0x4d4f4445`  | Cat's Eye Technologies | Funge-98 Standard Modes                 |
|      ✅      |    ✅     | MODU | `0x4d4f4455`  | Cat's Eye Technologies | Modulo Arithmetic Extension             |
|      ✅      |    ✅     | NULL | `0x4e554c4c`  | Cat's Eye Technologies | Funge-98 Null Fingerprint               |
|      ✅      |    ✅     | ORTH | `0x4f525448`  | Cat's Eye Technologies | Orthogonal Easement Library             |
|      ✅      |    ✅     | PERL | `0x5045524c`  | Cat's Eye Technologies | Generic Interface to the Perl Language  |
|      ✅      |    ✅     | REFC | `0x52454643`  | Cat's Eye Technologies | Referenced Cells Extension              |
|      ✅      |    ✅     | ROMA | `0x524f4d41`  | Cat's Eye Technologies | Funge-98 Roman Numerals                 |
|      ✅      |    ✅     | TOYS | `0x544f5953`  | Cat's Eye Technologies | Funge-98 Standard Toys                  |
|      ❌      |    ✅     | TURT | `0x54555254`  | Cat's Eye Technologies | Simple Turtle Graphics Library          |
|      ❌      |    ✅     | 3DSP | `0x33445350`  |          RCS           | 3D space manipulation extension         |
|      ❌      |    ❌     | ARRY | `0x41525259`  |          RCS           | Arrays                                  |
|      ❌      |    ✅     | BASE | `0x42415345`  |          RCS           | I/O for numbers in other bases          |
|      ❌      |    ❌     | BOOL | `0x424F4F4C`  |          RCS           | Logic functions                         |
|      ❌      |    ❌     | COPT | `0x434f5054`  |          RCS           | Command line arguments                  |
|      ✅      |    ✅     | CPLI | `0x43504C49`  |          RCS           | Complex Integer extension               |
|      ✅      |    ✅     | DATE | `0x44415445`  |          RCS           | Date Functions                          |
|      ✅      |    ✅     | DIRF | `0x44495246`  |          RCS           | Directory functions extension           |
|      ❌      |    ❌     | EMEM | `0x454d454d`  |          RCS           | Extended memory                         |
|      ✅      |    ✅     | EVAR | `0x45564152`  |          RCS           | Environment variables extension         |
|      ❌      |    ❌     | EXEC | `0x45584543`  |          RCS           | Various types of k-like execs           |
|      ✅      |    ✅     | FILE | `0x46494C45`  |          RCS           | File I/O functions                      |
|      ✅      |    ✅     | FING | `0x46494e47`  |          RCS           | Operate on single fingerprint semantics |
|      ❌      |    ❌     | FNGR | `0x464E4752`  |          RCS           | Fingerprint management extension        |
|      ❌      |    ❌     | FOBJ | `0x464f424a`  |          RCS           | Object Oriented extension               |
|      ❌      |    ❌     | FORK | `0x464F524B`  |          RCS           | Fork Process                            |
|      ✅      |    ✅     | FPDP | `0x46504450`  |          RCS           | Double precision floating point         |
|      ❌      |    ❌     | FPRT | `0x46505254`  |          RCS           | Formatted print                         |
|      ✅      |    ✅     | FPSP | `0x46505350`  |          RCS           | Single precision floating point         |
|      ✅      |    ✅     | FIXP | `0x46495850`  |          RCS           | Some useful fixed point math functions  |
|      ✅      |    ✅     | FRTH | `0x46525448`  |          RCS           | Some common forth commands              |
|      ❌      |    ❌     | ICAL | `0x4943414c`  |          RCS           | Some Intercal-like functions            |
|      ❌      |    ✅     | IIPC | `0x49495043`  |          RCS           | Inter IP communicaiton extension        |
|      ❌      |    ✅     | IMAP | `0x494D4150`  |          RCS           | Instruction remap extension             |
|      ❌      |    ❌     | IMTH | `0x494d5448`  |          RCS           | Some integer math functions             |
|      ✅      |    ✅     | INDV | `0x494E4456`  |          RCS           | Pointer functions                       |
|      ❌      |    ❌     | IPMD | `0x49504d44`  |          RCS           | IP dimension modes                      |
|      ❌      |    ❌     | LONG | `0x4c4f4e47`  |          RCS           | Long Integers                           |
|      ❌      |    ❌     | MACR | `0x4d414352`  |          RCS           | Macro Extension                         |
|      ❌      |    ❌     | MSGQ | `0x44d534751` |          RCS           | SysV IPC Message Queues                 |
|      ❌      |    ❌     | MVRS | `0x4d565253`  |          RCS           | Multiverse extension                    |
|      ❌      |    ❌     | RAND | `0x52414e44`  |          RCS           | Random Numbers                          |
|      ❌      |    ✅     | REXP | `0x52455850`  |          RCS           | Regular Expression Matching             |
|      ❌      |    ❌     | SETS | `0x53455453`  |          RCS           | Set operations                          |
|      ❌      |    ❌     | SGNE | `0x53474e45`  |          RCS           | Extension to SGNL                       |
|      ❌      |    ❌     | SMEM | `0x534d454d`  |          RCS           | SysV IPC Shared Memory                  |
|      ❌      |    ❌     | SMPH | `0x534d5048`  |          RCS           | SysV IPC Semaphores                     |
|      ✅      |    ✅     | SOCK | `0x534F434B`  |          RCS           | tcp/ip socket extension                 |
|      ❌      |    ❌     | SORT | `0x534f5254`  |          RCS           | Sorting Functions                       |
|      ❌      |    ❌     | STCK | `0x5354434b`  |          RCS           | Stack Manipulation                      |
|      ✅      |    ✅     | STRN | `0x5354524E`  |          RCS           | String functions                        |
|      ✅      |    ✅     | SUBR | `0x53554252`  |          RCS           | Subroutine extension                    |
|      ✅      |    ✅     | TIME | `0x54494D45`  |          RCS           | Time and Date functions                 |
|      ❌      |    ✅     | TERM | `0x5445524D`  |          RCS           | Terminal extension                      |
|      ❌      |    ✅     | TRDS | `0x54524453`  |          RCS           | IP travel in time and space             |
|      ❌      |    ❌     | TRGR | `0x54524752`  |          RCS           | Triggers                                |
|      ❌      |    ❌     | UNIX | `0x554e4958`  |          RCS           | Some Unix access functions              |
|      ❌      |    ❌     | WIND | `0x57494E44`  |          RCS           | Windows extensions                      |
|      ❌      |    ✅     | JSTR | `0x4a535452`  |     Jesse Van Herk     | 3d P and G for 0gnirts                  |
|      ❌      |    ❌     | SGNL | `0x53474E4C`  |     Jesse Van Herk     | Signal handling                         |
|      ❌      |    ✅     | NCRS | `0x4e435253`  |     Jesse Van Herk     | Ncurses Routines                        |
|      ❌      |    ✅     | SCKE | `0x53434b45`  |       GLFunge98        | Extensions to SOCK                      |
|      ❌      |    ❌     | CFFI | `0x43464649`  |        oshaboy         | C Foreign Function Interface            |
|      ❌      |    ❌     | IFFI | `0x49464649`  |        catb.org        | C-INTERCAL Foreign Function Interface   |

## HRTI -- `0x48525449`

Taken from https://catseye.tc/modules/Funge-98/library/HRTI.markdown

The HRTI fingerprint allows a Funge program to measure elapsed time much
more finely than the clock values returned by `y`.

After successfully loading HRTI, the instructions `E`, `G`, `M`, `S`,
and `T` take on new semantics.

`G` 'Granularity' pushes the smallest clock tick the underlying system
can reliably handle, measured in microseconds.

`M` 'Mark' designates the timer as having been read by the IP with this
ID at this instance in time.

`T` 'Timer' pushes the number of microseconds elapsed since the last
time an IP with this ID marked the timer. If there is no previous mark,
acts like `r`.

`E` 'Erase mark' erases the last timer mark by this IP (such that `T`
above will act like `r`)

`S` 'Second' pushes the number of microseconds elapsed since the last
whole second.

The timer and mark-list are considered global and static, shared amongst
all IP's, in order to retain tame behaviour.

This timer is not affected by 'time travel' contrivances.

## MODE -- `0x4d4f4445`

Taken from https://catseye.tc/modules/Funge-98/library/MODE.markdown

After successfully loading MODE, the instructions `H`, `I`, `Q`, and `S`
take on new semantics, which alter four new states or 'modes' of the
current IP.

`H` toggles an internal flag called hovermode on and off. In hovermode,
the instructions `>`, `<`, `^`, `v`, `|`, and `_` treat the IP's delta
relatively - instead of setting the dx to 0 and dy to -1, `^` would
instead simply subtract 1 from dy.

The `I` "Toggle Invertmode" instruction toggles an internal flag called
*invertmode*. When invertmode is active, cells are **pushed** on the
stack onto the **bottom** instead of the top.

The `Q` "Toggle Queuemode" instruction toggles an internal flag called
*queuemode*. When queuemode is active, cells are **popped** off the
stack from the **bottom** instead of the top.

`S` toggles switchmode on and off. In switchmode, the pairs of
instructions `[` and `]`, `{` and `}`, and `(` and `)` are treated as
switches. When one is executed, the cell it is located in is immediately
overwritten with the other instruction of the pair, providing a
switching mechanism and a way to seperate coincident IP's.

## MODU -- `0x4d4f4455`

Taken from https://catseye.tc/modules/Funge-98/library/MODU.markdown

The MODU fingerprint implements some of the finer, less-well-agreed-upon
points of modulo arithmetic. With positive arguments, these instructions
work exactly the same as `%` does. However, when negative values are
involved, they all work differently:

`M`: signed-result modulo:

`U`: Sam Holden's unsigned-result modulo

`R`: C-language integer remainder

## NULL -- `0x4e554c4c`

Taken from https://catseye.tc/modules/Funge-98/library/NULL.markdown

After successfully loading fingerprint 0x4e554c4c, all 26 instructions
`A` to `Z` take on the semantics of `r`.

This can be loaded before loading a regular transparent fingerprint to
make it act opaquely.

## ORTH -- `0x4f525448`

Taken from https://catseye.tc/modules/Funge-98/library/ORTH.markdown

The ORTH fingerprint is designed to ease transition between the
Orthogonal programming language and Befunge-98 (or higher dimension
Funges.) Even if transition from Orthogonal is not an issue, the ORTH
library contains some potentially interesting instructions not in
standard Funge-98.

After successfully loading ORTH, the instructions `A`, `E`, `G`, `O`,
`P`, `S`, `V`, `W`, `X`, `Y`, and `Z` take on new semantics. The
following table, which can be used to translate Orthogonal to Funge-98
and back, includes which Orthogonal instructions they emulate:

        Funge   Orthogonal  Semantic

        +       +           add
        *       *           multiply
        -       -           subtract
        /       /           divide
        %       %           modulo (positive values only)
    >>> A       &           bitwise AND
    >>> O       |           bitwise OR
    >>> E       ^           bitwise EXOR
        !       !           logical negate
        \       ~           swap
        :       @           duplicate
        $       $           pop
        <       L           go west
        >       H           go east
        ^       K           go north
        v       J           go south
        ]       cw          rotate right
        [       ccw         rotate left
        r       rev         reverse
    >>> X       x           change x
    >>> Y       y           change y
    >>> V       dx          change dx
    >>> W       dy          change dy
    >>> G       =           ortho get
    >>> P       #           ortho put
    >>> Z       ?           ramp if zero
        ,       c           output character
    >>> S       s           output string
        .       d           output decimal
        z       nop         no operation
        q       ret         quit

## PERL -- `0x5045524c`

Taken from https://catseye.tc/modules/Funge-98/library/PERL.markdown

The PERL fingerprint is designed to provide a basic, no-frills interface
to the Perl language.

After successfully loading PERL, the instructions `E`, `I`, and `S` take
on new semantics.

`S` ('Shelled') pushes a 0 on the stack if the Perl language is already
loaded (e.g. the interpreter is written in Perl). It pushes a 1 on the
stack otherwise, indicating that the Perl language will be shelled when
needed.

`E` ('Eval') pops a 0gnirts string and performs a Perl `eval()` on it,
possibly (or not) shelling Perl as indicated by S above. The result of
the call is pushed as a 0gnirts string back onto the stack.

`I` ('Int Eval') acts the same as `E`, except that the result of the
call is converted to an integer and pushed as a single cell onto the
stack.

## REFC -- `0x52454643`

Taken from https://catseye.tc/modules/Funge-98/library/REFC.markdown

The REFC fingerprint allows vectors to be encoded into and decoded from
single scalar cell values.

After successfully loading REFC, the instructions `D` and `R` take on
new semantics.

`R` 'Reference' pops a vector off the stack, and pushes a scalar value
back onto the stack, unique within an internal list of references, which
refers to that vector.

`D` 'Dereference' pops a scalar value off the stack, and pushes the
vector back onto the stack which corresponds to that unique reference
value.

The internal list of references is considered shared among all IP's, so
a global static can be used to store this list, so that this extension
remains tame.

## ROMA -- `0x524f4d41`

Taken from https://catseye.tc/modules/Funge-98/library/ROMA.markdown

After successfully loading ROMA, the instructions `C`, `D`, `I`, `L`,
`M`, `V`, and `X` take on new semantics.

- `C` pushes 100 onto the stack.
- `D` pushes 500 onto the stack.
- `I` pushes 1 onto the stack.
- `L` pushes 50 onto the stack.
- `M` pushes 1000 onto the stack.
- `V` pushes 5 onto the stack.
- `X` pushes 10 onto the stack.

Note that these are just digits, you still have to do the arithmetic
yourself. Executing `MCMLXXXIV` will not leave 1984 on the stack. But
executing `MCM\-+LXXX+++IV\-++` should.

## TOYS -- `0x544f5953`

Taken from https://catseye.tc/modules/Funge-98/library/TOYS.markdown

After successfully loading TOYS, the instructions `A`, `B`, `C`, `D`,
`E`, `F`, `G`, `H`, `I`, `J`, `K`, `L`, `M`, `N`, `O`, `P`, `Q`, `R`,
`S`, `T`, `U`, `V`, `W`, `X`, `Y`, and `Z` take on new semantics (and
INTERCAL-esque names).

`C` ('bracelet') pops three vectors off the stack and performs a
low-order copy of Funge-Space.

`K` ('scissors') pops three vectors off the stack and performs a
high-order copy of Funge-Space.

`M` ('kittycat') pops three vectors off the stack and performs a
low-order move (copy & erase original) of Funge-Space.

`V` ('dixiecup') pops three vectors off the stack and performs a
high-order move of Funge-Space.

`S` ('chicane') pops two vectors off the stack, then a cell, then fills
that area of Funge-Space homogenously with that cell's value.

Which order a copy or move takes is important if you copy or move to an
overlapping area. Ensure when implementing these that the order is
preserved in all dimensions.

The first two vectors are like the arguments to `o`. In all except `S`,
the third is the destination, relative to the origin.

`J` ('fishhook') pops a value off the stack, and causes the current
column (y coordinate) of Funge-space to be translated north (if value is
negative) or south (if positive) that many rows.

`O` ('boulder') pops a value off the stack, and causes the current row
(x coordinate) of Funge-space to be translated west (if value is
negative) or east (if positive) that many columns.

`L` ('corner') works like `'` except it picks up the cell to the "left"
of the IP's line and does not skip over anything. (Historians may note
that this works like "Get Left Hand" did in Befunge-97.) The cell to the
"left" of the IP is the IP's position, plus its delta rotated -90
degrees about the Z axis (a la `[`)

`R` ('can opener') is a corresponding instruction that mirrors `L` and
works to the right, rotated 90 degrees about the Z axis ("Get Right
Hand" from Befunge-97)

`I` ('doric column') pops a value off the stack, increments it, and
pushes it back onto the stack.

`D` ('toilet seat') pops a value off the stack, decrements it, and
pushes it back onto the stack.

`N` ('lightning bolt') pops a value off the stack, negates it, and
pushes it back onto the stack.

`H` ('pair of stilts') pops a value *b* off the stack, then a value *a*,
then binary-shifts *a* *b* places left if *b* is positive, or |*b*|
places right if *b* is negative.

`A` ('gable') pops a cell *n* off the stack, then another cell, then
pushes *n* copies of that cell onto the stack.

`B` ('pair of shoes') pops two cells off the stack and pushes the result
of a "butterfly" bit operation.

`E` ('pitchfork head') pops all values off the stack and pushes their
sum back onto it.

`P` ('mailbox') pops all values off the stack and pushes their product
back onto it.

`F` ('calipers') pops a vector, then a value *i*. Treating the rest of
the stack as *j* groups of *i* cells each, it writes this 2D matrix into
Funge-space in row-major order, with it's least point as the given
vector.

`G` ('counterclockwise') pops a vector, then a value *i*. It then pushes
onto the stack *j* groups of *i* cells each which it retrieves as a 2D
matrix in Funge-space in row-major order, the least point of which being
the vector supplied to it.

`Q` ('necklace') pops a value off the stack and places it into the cell
directly behind the IP (kind of like `s`, except behind, and no cell is
skipped over.)

`T` ('barstool') pops a dimension number off the stack; if it's a 0,
acts like `_`; if it's 1, acts like `|`; if it's 2, acts like `m`; etc.
depending on the number of available dimensions as appropriate of
course.

`U` ('tumbler') is like `?` but one-shot. When executed, it randomly
transmutes into one of `<`, `>`, `^`, `v`, `h`, or `l`, depending on the
number of available dimensions as appropriate of course.

`W` ('television antenna') pops a vector off the stack, then a value. If
the cell at that vector (plus the storage offset) in Funge-Space (a la
`g`) is equal to that value, nothing happens. If the cell in space is
less than the value, it pushes the value and the vector (inverted) back
onto the stack, and backs up the IP (subtracts the IP's delta from it's
position, sort of a 'wait to try again' condition, useful mainly in
Concurrent Funge.) If the cell in space is greater than that value, acts
like `r`.

`X` ('buried treasure') increments the IP's x coordinate.

`Y` ('slingshot') increments the IP's y coordinate.

`Z` ('barn door') increments the IP's z coordinate.

These three instructions are useful at the end of a line, to indicate
"proceed to next line then wrap". Note the IP's delta motion is still
fully in effect.

## TURT -- `0x54555254`

Taken from https://catseye.tc/modules/Funge-98/library/TURT.markdown

The TURT fingerprint provides a simple interface to a simple "drawing
turtle-robot simulator".

After successfully loading TURT, several instructions take on new
semantics.

These instructions pop one value off the stack:

- `L` 'Turn Left' (angle in degrees)
- `R` 'Turn Right' (angle in degrees)
- `H` 'Set Heading' (angle in degrees, relative to 0deg, east)
- `F` 'Forward' (distance in pixels)
- `B` 'Back' (distance in pixels)
- `P` 'Pen Position' (0 = up, 1 = down)
- `C` 'Pen Colour' (24-bit RGB)
- `N` 'Clear Paper with Colour' (24-bit RGB)
- `D` 'Show Display' (0 = no, 1 = yes)

These pop two values each:

- `T` 'Teleport' (x, y coords relative to origin; 00T = home)

These push one value each:

- `E` 'Query Pen' (0 = up, 1 = down)
- `A` 'Query Heading' (positive angle relative to east)

These push two values each:

- `Q` 'Query Position' (x, y coordinates)

These push four values each:

- `U` 'Query Bounds' (two pairs of x, y coordinates)

And these don't even use the stack:

- `I` 'Print current Drawing' (if possible)

To keep this fingerprint tame, a single Turtle and display is defined to
be shared amongst all IP's. The turtle is not defined to wrap if it goes
out of bounds (after all this interface might just as well be used to
drive a **real** turtle robot.)

## 3DSP -- `0x33445350`

```
A   (V3a V3b -- V3)     Add two 3d vectors
B   (V3a V3b -- V3)     Subtract two 3d vectors
C   (V3a V3b -- V3)     Cross porduct of two vectors
D   (V3a V3b -- n)      Dot product of two vector
L   (V3 -- n)           Length of vector
M   (V3a V3b -- V3)     Multiply two 3d vectors
N   (V3 -- V3)          Normalize vector (sets length to 1)
P   (Vdm Vsm -- )       Copy a matrix
R   (Va axis ang -- )   Generate a rotation matrix
S   (Va V3 -- )         Generate a scale matrix
T   (Va V3 -- )         Generate a translation matrix
U   (V3 -- V3 V3)       Duplicate vector on top of stack
V   (V3 -- x y)         Map 3d point to 2d view
X   (V3 Vam -- V3)      Transform a vector using transformation matrix
Y   (Vdm Vam Vam -- )   Multiply two matrices
Z   (n V3 -- V3)        Scale a vector

    All numbers used by these functions are single precision floating point like in extension "FPSP"
    In R, ang is in degrees, axis is an integer (1=x,2=y,3=z)
    Matrices are stored in funge-space as 2-dimenstion 4x4 arrays. the address vector will point to the x1y1 cell. 
```

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

## BASE -- `0x42415345`

```
B   (n -- )     Ouptut top of stack in binary
H   (n -- )     Ouptut top of stack in hex
I   (b -- n)    Read input in specified base
N   (n b -- )   Output n in base b
O   (n -- )     Ouptut top of stack in octal
```

## BOOL -- `0x424F4F4C`

```
A   (a b -- r)  And
N   (a -- r)    Not
O   (a b -- r)  Or
X   (a b -- r)  Xor
```

## COPT -- `0x434f5054`

```
A   ( -- 0gnirts ... )      Push all command line arguments on stack
C   ( -- n)                 Get count of command line arguments
G   (n -- 0gnirts)          Get specified command line argument on stack
S   (0gnirts -- 0gnirts)    Get argument with specified switch

    A First string on stack will be source file, second will be first argument.
    C returns the number of arguments, including the source file, so if no arguments were given besides the source file
        then C will return 1, 2 if one argument was given after source file, and so on.   
    G Will reflect on negative or if argument n does not exist.
    Argument 0 is the name of the funge file loaded by the interpreter.
    S gets second argument from things like: switch arg, switcharg, switch=arg.
    S will reflect if a matching argument is not found. 
```

## CPLI -- `0x43504C49`

```
A   (ar ai br bi -- r i)    Add two complex integers
D   (ar ai br bi -- r i)    Divide two complex integers
M   (ar ai br bi -- r i)    Multiply two complex integers
O   (r i -- )               Output a complex number
S   (ar ai br bi -- r i)    Subtract two complex integers
V   (r i -- n)              Absolute value of a complex integer
```

## DATE -- `0x44415445`

```
A   (y m d days -- y m d)       Add days to date
C   (jd -- y m d)               Convert julian day to calendar date
D   (y1 m1 d1 y2 m2 d2 -- days) Days between dates
J   (y m d -- jd)               Calendar date to julian day
T   (y d -- y m d)              Year/day-of-year to full date
W   (y m d -- d)                Day of week (0=monday)
Y   (y m d -- d)                Day of year (0=Jan 1)

    A may be negative
    Since all these functions work with integer values, julian day calculations assume 12:00 noon as the time.
    Gregorian calendar is assumed for calendar dates 
```

## DIRF -- `0x44495246`

```
C   (0gnirts -- )   Change directory
M   (0gnirts -- )   Make a directory
R   (0gnirts -- )   Remove a directory

    All functions act as r on failure 
```

## EMEM -- `0x454d454d`

```
A   (size -- hnd)       Allocate memory
F   (hnd -- )           Free memory
G   (hnd n addr --)     Get bytes from memory
P   (.. hnd n addr --)  Put bytes into memory
R   (hnd size -- )      Reallocate memory

    Errors on any instructions will reflect
    
    This is essentially an interface into malloc.
    
    As far as implementing this, hnd can be the direct pointer if it fits within the cell size of the interprter, or 
    else a seperate list can be maintained and this would be the handle into the list.
    
    Stack entries written to memory using P truncate to bytes. 
```

## EVAR -- `0x45564152`

```
G   (0gnirts -- 0gnirts)    Get value of an environment variable
N   ( -- n )                Get number of environment variables
P   (0gnirts --)            Put a value into the environemnt (form: name=value)
V   (n -- 0gnirts)          Get n'th environmnt variable (form: name=value)
```

## EXEC -- `0x45584543`

```
A   (V n -- )   Execute command at vector n times from current location, IP will be pointed at the A
B   (V n -- )   Like A but IP will be reset each iteration
G   (V --)      Set position of IP to vector
K   (n -- )     what k should have been, will skip following instruction if it is the iterated one
R   (n --)      Like K but IP is reset after each iteration
X   (cmd n --)  execute command on stack n times

    An IP reset as used in B and R reset the IP position only, nothing else
    On X, cmd is removed from the stack before it is iterated 
```

## FILE -- `0x46494C45`

```
C   (h --)              Close a file
D   (0gnirts -- )       Delete specified file
G   (h -- h 0gnirts b)  Read string from file (like c fgets)
L   (h -- h n)          Get location of file pointer
O   (Va m 0gnirts -- h) Open a file (Va=i/o buffer)
                        m   function
                        0   read
                        1   write
                        2   append
                        3   read/write
                        4   truncate read/write
                        5   append read/write
P   (h 0gnirts -- h)    Write string to file (like c fputs)
R   (h n -- h)          Read n bytes from file to buffer
S   (h m n -- h)        Seek to position n in file
                        m   function
                        0   from beginning
                        1   from current location
                        2   from end
W   (h n -- h)          Write n bytes from buffer to file

    All file functions on failure act as r.
    Functions W and R write cells as bytes, any cells containing values greater than 255 will have the top bits 
        stripped. 

Clarification

    D was not in the original spec and may not be supported in all interpreters 
```

## FING -- `0x46494e47`

```
X   (sem sem -- )   Swap two semantics
Y   (sem -- )       Pop semantic
Z   (src dst -- )   Push source semantic onto dst

    This fingerprint works by pushing and popping the semantic stacks. an empty stack will pop a reflect
    sem can be 0-25 or 'A through 'Z. Any other value is an error and will reflect
    X will swap a reflect in place of an empty stack
    Y will not reflect popping an empty semantic stack
    Z will push a reflect if the source semantic stack is empty 
```

## FNGR -- `0x464E4752`

```
A   ( -- )              Set ( and ) to work in absolute mode
B   ( -- fp 1)          Create a Blank extension on top of stack
                        (all entries are set to transparent). The standard
                        fingerprint id for this copy will be 0xFFFFFFFF.
                        This is useful to create a customized
                        extension containing pieces from many others.
C   (new n old o -- )   Copy instruction 'old' in fingerprint 'o' to
                        instruction 'new' in fingerprint 'n'
D   (inst n-- )         Delete an instruction from fingerprint with id n
F   (fp -- n)           Get current id for specified fingerprint
                        fp is a 1 cell version, like from the ) command
K   (n -- )             Kill extension at selected position in fingerprint stack
N   ( -- n)             Get number of fingerprints loaded
O   ( -- )              Return ( and ) to the official functions
R   ( -- )              Set ( and ) to work in roll mode
S   ( -- )              Set ( and ) to work in swap mode
T   (fp n -- )          Tag stack entry n with new fingerprint fp
X   (n n -- )           Exchange the positions of two fingerprints in the stack

All instructions on failure act like r.

    The fingerprint stack and fingerprint ids as used by this extension: The fingerprint stack consists of all loaded 
fingerprints. When a fingerprint is loaded it is pushed onto this stack. When an A-Z instruction is executed the tos of
this stack is the first searched for the command, and then on downwards through the stack, if the bottom is hit, then an
r command will be executed. For most all commands in this extension, the fingerprint id is actually the position on the
fingerprint stack. The top has id 0, the second id 1, and so on. So, if you were to execute "'A1D" This would delete the
'A' command from the extension sitting on the second position on the fingerprint stack.

Absolute Mode: In absolute mode, the ( and ) instructions take on new meanings:

(   A number is popped of off the stack, this numbers is the fingerprint id (stack position) of what should be 
    considered the top of stack. It does not actually move anything, it only changes where the instruction search 
    starts. Extensions on the stack above the selected one will not be searched whereas the selected and donward will 
    still be searched. Executing "0(" will return the search to the top of the fingerprint stack.
    
)   A number is popped of off the stack, this number specifies which fingerprint is to be copied over the top of the 
    current top of stack. The extenstion that is currently on the top of the fingerprint stack will be deleted amd the 
    selected one takes its place. The selected entry also remains in its original stack position, only a copy is made. 
    The search point is then reset to the top of the fingerprint stack. Unlike the ( command, this will allow all other 
    stack entries to be searched.
    
Roll Mode: In roll mode, the ( and ) instructions take on new meanings:

(   A number is popped off the data stack and is used to roll the fingerprint stack. The item at the selected entry is 
    removed and moved to the top of stack, while all other entries are moved down. This operates like the forth "roll" 
    command.

)  	This works like (, but the roll is reversed. The top of stack is moved to the selected position while all other 
    entries are moved up. This operates like the forth "-roll" command.

Swap Mode: In swap mode, the ( and ) instructions take on new meanings:

(   A number is popped from the data stack. This specifies which entry in the fingerprint stack is to be swapped with 
    the top of the fingerprint stack.

)   This command uses no arguments from the data stack. It merely swaps the top two entries on the fingerprint stack

Note:

    In all modes, on failure ( and ) will act like r.
    
    When FNGR is loaded the fingerprint stack does NOT act like the spec, Instead there is a single fingerprint stack 
    and unloading a fingerprint will remove the semantics for that fingerprint and not the semantics assigned to the 
    various commands of the unloaded fingerprint. When FNGR is unloaded then the ( and ) commands will work like the 
    official specs. 
```

## FOBJ -- `0x464f424a`

```
D   (ref -- )               Destruct an object
I   (0gnirts -- ref)        Instantiate an object
M   (nargs ref meth -- ret) Call an object method
N   (ref -- 0gnirts)        Get object name

    All functions reflect upon error
    
    ref referes to an index into a global object table
    
    In Funge/Multiverse each universe has its own global object table
    
    I 0gnirts referes to the funge file containing the code for the object
    
    M nargs specifies how many stack entries to transfer to the IP created in the object funge-space. Stack order is 
    preserved. The count is NOT placed on the destination IPs stack.
    
    Funge files are in trefunge format. Each z level is a message handler, therefore message handlers start at 0 and go 
    up.
    
    Funge-space for objects is in Trefunge mode.
    
    Starting point for any message handler is always [0][0][m] with a delta of [1][0][0]
    
    if cell[0][0][m] is a space then cause M to reflect
    
    Object method calls execute in a single tick
    
    The full capabilites of the funge engine should be available to object message handlers, this includes i,o,=,t, 
    fingerprints, etc.
    
    Funge multiverse is not required for this extension, but each object must be its own funge-space.
    
    In Rc/Funge-98, each object is a stand-alone VM that is NOT part of the funge multiverse.
    
    Funge-space of a loaded object must remain consistant across method calls. In other words, if the method modifies 
    its own funge-space, that change must remain for further method calls.
    
    When the last IP terminates a value is popped off its stack, that many stack entries are transferred back to the 
    calling IP. Order is preserved.
    
    Global object table should be initialized at interpreter startup, and not by loading this fingerprint
    
    Object reference numbers may be reused 
```

## FORK -- `0x464F524B`

```
T   ( -- pid flg)   Fork new process

    T - flg=0 for parent, 1 for child.
    T - child gets parent's pid, parent gets child's pid
    T - child has its IP delta reflected
    T - flg=-1 error in fork, does not reflect
    Other IPs in the forked process are unaffected 

Clarification

    The function forks the actual interpreter, creating an additional interpreter process. 
```

## FPDP -- `0x46504450`

```
A   (a b -- n)      Add two double precision fp numbers
B   (n -- n)        Sin of double precision fp number
C   (n -- n)        Cosin of double precision fp number
D   (a b -- n)      Divide two double precision fp numbers
E   (n -- n)        Arcsin of double precision fp number
F   (n -- n)        Convert integer to floating point
G   (n -- n)        Arctangent of double precision fp number
H   (n -- n)        Arccosin of double precision fp number
I   (n -- n)        Convert floating point to integer
K   (n -- n)        Natural logarithm of double precision fp number
L   (n -- n)        Base 10 logarithm of double precision fp number
M   (a b -- n)      Multiply two double precision fp numbers
N   (n -- n)        Negate double precision fp number
P   (n -- )         Print a floating point number
Q   (n -- n)        Double precision square root
R   (0gnirts -- n)  Convert ascii number to floating point
S   (a b -- n)      Subtract two double precision fp numbers
T   (n -- n)        Tangent of double precision fp number
V   (n -- n)        Absolute value of double precision fp number
X   (n -- n)        Exponential of double precision fp number (e**n)
Y   (x y -- n)      Raise x to the power of y
```

## FPRT -- `0x46505254`

```
D   (fmt fh fl -- 0gnirts)      Format FPDP type number
F   (fmt f -- 0gnirts)          Format FPSP type number
I   (fmt i -- 0gnirts)          Format an integer
L   (fmt h l -- 0gnirts)        Format a long integer
S   (fmt 0gnirts -- 0gnirts)    Format a string

    Formats are printf style
    Error in any function reflects 
```

## FPSP -- `0x46505350`

```
A   (a b -- n)      Add two single precision fp numbers
B   (n -- n)        Sin of single precision fp number
C   (n -- n)        Cosin of single precision fp number
D   (a b -- n)      Divide two single precision fp numbers
E   (n -- n)        Arcsin of single precision fp number
F   (n -- n)        Convert integer to floating point
G   (n -- n)        Arctangent of single precision fp number
H   (n -- n)        Arccosin of single precision fp number
I   (n -- n)        Convert floating point to integer
K   (n -- n)        Natural logarithm of single precision fp number
L   (n -- n)        Base 10 logarithm of single precision fp number
M   (a b -- n)      Multiply two single precision fp numbers
N   (n -- n)        Negate single precision fp number
P   (n -- )         Print a floating point number
Q   (n -- n)        Single precision square root
R   (0gnirts -- n)  Convert ascii number to floating point
S   (a b -- n)      Subtract two single precision fp numbers
T   (n -- n)        Tangent of single precision fp number
V   (n -- n)        Absolute value of single precision fp number
X   (n -- n)        Exponential of single precision fp number (e**n)
Y   (x y -- n)      Raise x to the power of y

    Trig functions work in radians 
```

## FIXP -- `0x46495850`

```
A   (a b -- a and b)    And
B   (n -- arccos(b))    Find arccosin of tos
C   (n -- cos(b))       Find cosin of tos
D   (n -- rnd(n))       RanDom number
I   (n -- sin(b))       Find sin of tos
J   (n -- arcsin(b))    Find arcsin of tos
N   (a -- 0-a)          Negate
O   (a b -- a or b)     Or
P   (a -- a*pi)         Multiply by pi
Q   (a -- sqrt(a))      Square root
R   (a b -- a**b)       Raise a to the power of b
S   (n -- n)            Replace tos with sign of tos
T   (n -- tan(b))       Find tangent of tos
U   (n -- arctan(b)     Find arctangent of tos
V   (n -- n)            Absolute value of tos
X   (a b -- a xor b)    Xor

    The functions C,I,T,B,J,U expect their arguments times 10000, for example: 45 should be passed as 450000. The 
        results will also be multiplied by 10000, thereby giving 4 digits of decimal precision.
    Trigonometric functions work in degrees. not radians. 
```

## FRTH -- `0x46525448`

```
D   ( .. -- .. n)       Push depth of stack to tos
L   ( .. n -- .. n)     Forth Roll command
O   (a b -- a b a)      Forth Over command
P   (.. n -- .. n)      Forth Pick command
R   (a b c -- b c a)    Forth Rot command

    Stack operations are subject to the modes set by MODE 

Clarification

    P should reflect on a negative argument
    P should push 0 if argument is greater than stack size
    L should act like forth -roll with a negative argument
    L with an argument larger than the stack size is allowed, enough zeroes will be created in order to fulfill the 
        request. Example: n543210a-L will leave a stack of: 2 3 4 5 0 0 0 0 0 0 1   
    L,P the top of stack is position 0 
```

## ICAL -- `0x4943414c`

```
A   (a -- r)    Unary AND
F   (n -- )     Forget entries from nexting stack
I   (a b -- r)  Interleave a $ b
N   (Va -- )    Jump to new location
O   (a -- r)    Unary OR
R   (n -- )     Resume
S   (a b -- r)  Select a ~ b
X   (a -- r)    Unary XOR

    A,O,X work in 16 bits unless a is greater than 16 bits
    I a and b are 16-bits and will produce a 32 bit result
    N reflects if there are already 79 entries on the Next stack
    Neither N nor R affect the delta!
    0R is not an error and will just continue without resuming
    Negative argument to R is an error and will reflect
    R on an empty nexting stack will continue without resuming
    R if n is greater than the number of nexting stack entries, the nexting stack will be cleared and no resume will take place 
```

## IIPC -- `0x49495043`

```
A   ( -- n)     Get ancestors unique id
D   ( -- )      Go Dormant until stack is manipulated by another ip
G   (i -- n)    Get the top value of another ip's stack (pop)
I   ( -- n)     Get ip's own unique id
L   (i -- n)    Look at top stack value of another ip
P   (n i -- )   Put a value onto another ip's stack
```

## IMAP -- `0x494D4150`

```
C   ( -- )          Clear all instruction remaps
M   (new old -- )   Remap an instruction
O   (n -- )         Return instruction n to its old function

Clarification

    This extension is intended to map instructions in the 0-255 range. Other interpreters may have a more limited or 
    more expanded range
    
    Attempting to map instructions outside of the 0-255 range reflect. Some interpreters may ignore an out of range map
    without reflecting
    
    Chained remaps are not supported by this extension. Only a single level of mapping is supported. Other interpreters
    may have implemented chained remaps 
```

## IMTH -- `0x494d5448`

```
A   (.. n -- r) Average
B   (n -- r)    Absolute value
C   (n -- r)    Multiply by 100
D   (n -- r)    Decrease towards zero
E   (n -- r)    Multiply by 10,000
F   (n -- r)    Factorial
G   (n -- r)    Sign
H   (n -- r)    Multiply by 1,000
I   (n -- r)    Increase away from zero
L   (n c -- r)  Shift n left c times
N   (.. n -- r) Minimum value
R   (n c -- r)  Shift n right c times
S   (.. n -- r) Sum
T   (n -- r)    Multiply by 10
U   (n -- )     Unsigned print
X   (.. n -- r) Maximum value
Z   (n -- r)    Negate

    A n=0 is not an error and will return 0
    A n<0 is an error and will reflect
    A n>stacksize is not an error
    F will reflect on negative
    L c can be negative and will shift right
    R c can be negative and will shift left
    L,R count of zero will return the argument unmodified
    N,X will reflect if count <= 0
    N,X count greater than stack size is not an error
    S n=0 is not an error and will return 0
    S n<0 is an error and will reflect
    S n>stacksize is not an error
    D input of zero is not an error and will produce zero
    I input of zero is not an error and will produce zero 
```

## INDV -- `0x494E4456`

```
G   (Vp - n)    Pointer get number
P   (n Vp -- )  Pointer put number
V   (Va -- V)   Pointer get vector
W   (V Va --)   Pointer put vector

    Pointer functions pop a vector off the stack which points to another vector in memory which is the pointer to the 
    target cell. 

Clarification

    This fingerprint was originally called PNTR. Early on it was renamed. to INDV. Some interpreters may implement this 
    fingerprint as PNTR. Any use of PNTR should be changed to use INDV. Otherwise consider PNTR to be a synonum of INDV
    
    Vectors are stored in memory with a delta of 1,0,0 with Z being first in trefunge, and Y first in befunge. 
    Originally Rc/Funge-98 stored this vector in reverse and became known as Rc/Funge-98 illogical order. Other 
    interpreters may have copied the original way that Rc/Funge-98 stored the vectors. 
```

## IPMD -- `0x49504d44`

```
B   ( -- )  Run in BeFunge mode
D   ( -- )  Run in default mode for VM
Q   ( -- d) Query for mode IP is running in
T   ( -- )  Run in TreFunge mode
U   ( -- )  Run in UneFunge mode

    These commands only affect the IP executing them. Other IPs running in the same VM are not affected.
    
    These functions affect how the IP interprets instructions, they will be limited or expanded based upon the mode the 
    IP is running in.
    
    These modes are NOT affected by the mode the VM is running in. It is allowed to set an IP into TreFunge mode in a 
    BeFunge funge-space. The TreFunge instructions must however work.
    
    Vectors will be affected by the mode the IP is running in. Example: If a VM is running in BeFunge mode and an IP is 
    running in TreFunge mode and wants to pop a vector, it will pop a 3 coordinate vector, likewise if the IP were 
    running in UneFunge mode, then it will pop a single value vector.
    
    When running in a mode less than Funge-Space, coordinates above the mode of the IP will be set for the coordinate of 
    the ip. For example if the IP is at 20,30 then exectues U and then a g command is exectued, g will retrieve a value 
    from row 30, not 0
    
    When running in a mode less than Funge-Space, x will set unpopped delta values to 0.
    
    Funge-space supports up to TreFunge when using this extension 
```

## LONG -- `0x4c4f4e47`

```
A   (ah al bh bl -- rh rl)  Addition
B   (ah al -- rh rl)        Absolute value
D   (ah al bh bl -- rh rl)  Division
E   (n -- rh rl)            Sign extend single to long
L   (ah al n -- rh rl)      Shift left n times
M   (ah al bh bl -- rh rl)  Multiplication
N   (ah al -- rh rl)        Negate
O   (ah al bh bl -- rh rl)  Modulo
P   (ah al -- )             Print
R   (ah al n -- rh rl)      Shift right n times
S   (ah al bh bl -- rh rl)  Subraction
Z   (0gnirts -- rh rl)      Ascii to long

    Long integers are 2 cell integers, if the interpreter's cell size is 32, then long integers are 64-bits.
    Division by zero results in zero, not error 
```

## MACR -- `0x4d414352`

```
A-Y ( -- )  Execute specified macro
Z   (V -- ) Specify where macro block is located

    Macros are simple mini-funge like Befunge-like subroutines that execute in a single tick
    
    The Macro block may be located anywhere in Funge-Space. Each macro runs with a delta of 1,0,0 (Befunge like macros) 
    macro A is located at the macro block vector, Macro B is one line below at the same starting X, C below that, etc
    
    Macros execute with the IP where it is! not in the macro space
    
    Instructions affect the IP that called the Macro
    
    A macro teminates when either a @ is found or an invalid instruction is found
    
    Most standard Funge-98 instructions can be used within macro blocks, but keep in mind they affect the IP where it is 
    and not inside the macro block
    
    A-Z generally are not allowed within macros, however some A-Z commands perform special functions when executed 
        inside of a macro:
    A - like _ but affects the macro pointer instead of the IP
    B - Move IP backwards
    E - Change macro delta to 1,0,0
    F - Move IP forwards
    G - Get next macro cell onto stack
    I - like | but affects the macro pointer instead of the IP
    J - like j but affects the macro pointer instead of the IP
    L - like [ but affects the macro pointer instead of the IP
    N - Change macro delta to 0,-1,0
    R - like ] but affects the macro pointer instead of the IP
    S - Change macro delta to 0,1,0
    T - like # but affects the macro pointer instead of the IP
    W - Change macro delta to -1,0,0
```

## MSGQ -- `0x44d534751`

```
G   (key flags -- id)           Get message queue identifier
K   (id -- )                    Kill message queue
R   (n mtyp id flags -- .. n t) Receive message to stack
S   (.. n mtyp id flags -- )    Send bytes on stack as message
T   (id -- nmsg maxsize)        Get message system info

    G Flags:
    4096  - IPC_CREAT   - Create if id does not exist
    8192  - IPC_EXCL    - Open in exclusive mode
    16384 - IPC_PRIVATE - Create private
    low 9 bits are Unix standard access permissions
    
    R Flags:
    1 - IPC_NOWAIT  - Do not block if no messages available
    2 - MSG_NOERROR - Truncate too-long message instead of error
    
    S Flags:
    1 - IPC_NOWAIT - Do not block if message queue full
    
    All functions reflect on error with the error code on the stack
    1  - EACCESS - A message queue exists for key, but no permission to access
    2  - EEXIST  - Message queue exist when IPC_CREAT and IPC_EXCL are both specified
    3  - ENOENT  - No mesage queue exists for key and IPC_CREAT was not specified
    4  - ENOMEM  - Not enough memory
    5  - ENOSPC  - Message queue needs to be create but no more message queues allowed
    6  - EFAULT  - Address for IPC_SET or IPC_STAT not accessable
    7  - EINVAL  - Invalid value for cmd or id
    8  - EPERM   - No permissions to perform action
    9  - EAGAIN  - A blocking condition was created and IPC_NOWAIT was specified
    10 - EIDRM   - Message queue was removed
    11 - EINTR   - Sleeping on a full message queue, the process caught a signal
    12 - E2BIG   - Message size greater than specified maximum
    13 - ENOMSG  - IPC_NOWAIT was specifed and no message of the required type was available
    Maximum message size MAY BE limited to a set size. Rc/Funge-98 allows for messages up to 4096 bytes 

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    should use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```

## MVRS -- `0x4d565253`

```
B   (0gnirts flgs lng dim -- )  Big-Bang, create another universe
C   ( -- n)                     Number of existing universes
F   (0gnirts Vd Vs Vsz -- )     Copy funge-space from another universe
G   (0gnirts Vpos Vdlt -- )     Go to another universe
J   (0gnirts -- )               Jump to another universe
N   ( -- 0gnirts)               Get name of current universe
P   (0gnirts Vd Vs Vsz -- )     Copy funge-space to another universe

    F source vector must be x,y,z even if source universe is unefunge or befunge
    F size vector is based upon current universe
    J keeps position and delta
    Any command specifying a universe will reflect if the universe does not exist 

B Flags:
    0 - Default
    Flags from 512 upwards are implementation dependent and may vary from interpreter to interpreter. Flags 256 and 
        below are reserved and may change in the future.
    Interpreters are not required to support any flags
    If an unsupported flag below 512 is used, B should reflect
    If an unsupported flag 512 and up is used, B should ignore it 

dim:
    0 - Default
    1 - Unefunge
    2 - Befunge
    3 - Trefunge
    n - Other funges

lng:
    0 - Default
    1 - Funge/93
    2 - Funge/98
    3 - Funge/108

    All others reserved and may change in the future
    If an unsupported language is specified, B should reflect 

Defaults:
    Defaults are the creating universe's flags, dimensions, and language 
```

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

## REXP -- `0x52455850`

```
C   (0gnirts flags -- )         Compile a regular expression
E   (0gnirts flags -- results)  Execute regular expression on string
F   ( -- )                      Free compiled regex buffer

    Flags for C command:
    1 - REG_EXTENDED - use posix extended regular expressions
    2 - REG_ICASE    - ignore case
    4 - REG_NOSUB    - Do not retrieve submatches
    8 - REG_NEWLINE  - match any characters do not match newlines
    
    Flags for E command:
    1 - REG_NOTBOL - beginning of line always fails
    2 - REG_NOTEOL - end of line always fails
    
    C Reflects on error with error number on stack:
    1  - REG_BADBR    - Invalid use of back reference
    2  - REG_BADPAT   - Invalid use of pattern operators
    3  - REG_BADRPT   - Invalid use of repitition operators
    4  - REG_EBRACE   - Unmatched brace
    5  - REG_EBRACK   - Unmatched bracket
    6  - REG_ECOLLATE - Invalid collating element
    7  - REG_ECTYPE   - Invalid character class name
    8  - REG_EEND     - Non-specific error
    9  - REG_EESCAPE  - Trailing backslash
    10 - REG_EPAREN   - Unmatched parenthesis
    11 - REG_ERANGE   - Invalid use of range operator
    12 - REG_ESIZE    - Compiled pattern too large
    13 - REG_ESPACE   - Regex routines ran out of memory
    14 - REG_ESUBREG  - Invalid backreference to subexpression
    
    E leaves the results of the match as a series of 0gnirts strings. Each string representing the matched portion of a 
    substring. Top of stack will have the count of these 0gnirts strings.
    
    E Reflects if no match
    
    If REG_EXTENDED is not specified, then the base level of regular expressions is what is supported, similar to grep 
    or sed. The commands . * [ ] ^ $ \( \) should all be supported 

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    should use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```

## SETS -- `0x53455453`

```
A   (set v -- set)                  Add value to set
C   (set -- set n)                  Get count of items in set
D   (set -- set set)                Duplicate set on stack
G   (Vdlt Vsrc -- set)              Get set from Funge-space
I   (seta setb -- seta setb setr)   Instersection of sets
M   (set v -- set r)                r=0 if v is not member of set, else r=1
P   (set -- set)                    Print a set
R   (set v -- set)                  Remove value from set
S   (seta setb -- seta setb setr)   Subtract setb from seta
U   (seta setb -- seta setb setr)   Union of sets
W   (set Vdlt Vdst -- set)          Write set to Funge-space
X   (seta setb -- setb seta)        Swap two sets
Z   (set -- )                       Drop set from stack

    All reflect if stack does not appear to have a proper set
    Sets are in the form (v1 v2 v3 .. vn ) n, n being closes to top of stack denotes how many items are in the set
    Nearly all instructions leave the work sets on the stack at the completion of the instruction
    Order within the sets need not be maintained. These are sets and not arrays 
```

## SGNE -- `0x53474e45`

```
A   (sec -- old)    Set alarm
I   ( -- pid)       Get PID of current process
L   (sec -- )       Sleep
P   ( -- )          Pause until signal
S   (s -- )         Send signal to self
T   ( -- )          Abort

    These instructions affect the interpreter and therefore all IPs will be subject to the effects of these functions.
    L - If process is worken up because of a signal, then the IP is reflected and the stack will contain the number of 
        unslept seconds. If the Process wakes up normally after the sleep period is over then the IP continues along its 
        delta and nothing will be pushed onto the stack
    S - Reflects on error 
```

## SMEM -- `0x534d454d`

```
G   (key size flags -- id)      Get shared memory segment
K   (id -- )                    Remove shared memory segment
R   (n addr id flags -- ..)     Read bytes from shared memory
T   (id -- size)                Get shared memory info
W   (.. n addr id flags -- )    Write bytes to shared memory

    G Flags:
    4096  - IPC_CREATE  - Create segment if it does not exist
    8192  - IPC_EXCL    - Open for exclusive use
    16384 - IPC_PRIVATE - Create private

    Low 9 bits are Unix pattern permisssions

    R Flags:
    1 - SHM_RDONLY - Attach segment readonly

    W Flags:
    1 - SHM_RDONLY - Attach segment readonly

    All commands reflect on error with the error code on the stack:
    1  - EACCES    - User does not have permission to access
    2  - EEXIST    - IPC_CREAT|IPC_EXCL was specified and sement exists
    3  - EFAULT    - Address is not accessable
    4  - EIDRM     - Shared memory segment was removed
    5  - EINVAL    - id is not a valid id
    6  - ENFILE    - System limit on open files has been reached
    7  - EOVERFLOW -
    8  - ENOENT    - No segment exists for key and IPC_CREAT was not specified
    9  - ENOMEM    - No memory could be allocated
    10 - ENOSPC    - All possible shared memory IDs have been taken
    11 - EPERM     - No permissions

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    hould use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```

## SMPH -- `0x534d5048`

```
A   (sem id flags -- id)    Allocate semaphore
D   (sem id flags -- id)    De-allocate semaphore
G   (key nsems flags -- id) Get a semaphore set
K   (id -- )                Remove a semaphore set
M   (op sem id n -- )       Multiple semaphore operations
N   (sem id -- z n)         Get number of processes waiting on semaphore
R   (sem id -- n)           Read semaphore value
W   (v sem id -- )          Write semaphore value
Z   (sem id -- )            Wait for zero semaphore

    A,D,Z Flags:
    1 - IPC_NOWAIT - Do not block
    2 - SEM_UNDO   - Undo operation on program exit
    
    G Flags:
    4096  - IPC_CREATE  - Create if it does not exist
    8192  - IPC_EXCL    - Open for exclusive use
    16384 - IPC_PRIVATE - Create a private semaphore set
    
    Low 9 bits are Unix pattern permisssions
    
    M (op sem id) is repeated on the stack n times, one set for each semaphore to be changed.
    
    N result z is the number of processes waiting for semaphore to be zero, n is the number of processes waiting for a 
    positive value
    
    All commands reflect on error with the error code on the stack:
    1  - E2BIG   - Value was too large
    2  - EACCESS - Semaphore exists but no access allowed
    3  - EAGAIN  - Operation could not go through with IPC_NOWAIT specified
    4  - EEXIST  - IPC_CREAT|IPC_EXCL were specified and semaphore exists
    5  - EFAULT  - Address isn't accessible
    6  - EFBIG   - Invalid semaphore number
    7  - EIDRM   - Semaphore set was removed
    8  - EINTR   - Sleeping on a wait queue and process receives a signal
    9  - EINVAL  - Semaphore set does not exist
    10 - ENOENT  - No semaphore set exists and IPC_CREAT was not specified
    11 - ENOMEM  - Not enough memory to create new semaphore set
    12 - ENOSPC  - Maximum semaphore limit has been reached
    13 - EPERM   - Insuficient privileges to execute command
    14 - ERANGE  - Semaphore value exceeded allowed count

Clarification

    Not all implementations will support all possible error types. If an implementation supports the error then it 
    should use the number above.
    
    Implementations may define additional errors as such portable code should be careful how it handles errors 
```

## SOCK -- `0x534F434B`

```
A   (s -- prt addr s)   Accept a connection
B   (s ct prt addr -- ) Bind a socket
C   (s ct prt addr -- ) Open a connection
I   (0gnirts -- addr)   Convert an ascii ip address to a 32 bit address
K   (s -- )             Kill a connection
L   (n s -- )           Set a socket to listening mode (n=backlog size)
O   (n o s -- )         Set socket option
R   (V l s -- bytes)    Receive from a socket,
S   (pf typ pro -- s)   Create a socket
W   (V l s -- retcode)  Write to a socket

note: All functions act as r on failure

addr:   32 bit destination address

ct:     1=AF_UNIX
        2=AF_INET

o:      1=SO_DEBUG
        2=SO_REUSEADDR
        3=SO_KEEPALIVE
        4=SO_DONTROUTE
        5=SO_BROADCAST
        6=OOBINLINE

pf:     1=PF_UNIX
        2=PF_INET

prt:    Port to connect to

s:      Socket identifier

typ:    1=SOCK_DGRAM
        2=SOCK_STREAM

pro:    1=tcp
        2=udp

V:      Vector to io buffer

Clarification

    The socket descriptor s used in these functions could be either an index into a table of open sockets or else use 
    the id returned by the OS. In either case the socket identifier needs to be usable by other IPs, therefore a socket 
    table that is global to all IPs or else use the OS descriptors.
    
    ct=1 and pf=1 are a broken spec and should not be implemented. Usage of either of these should reflect. 
```

## SORT -- `0x534f5254`

```
B   (Va Vld Vbd w n -- )    Sort block in funge-space
F   (Va Vd n -- )           Sort funge-space
K   (.. n -- ..)            Sort stack
S   (Va Vld Vsd w n -- )    Sort strings

    Reflect if n<=0
    Reflect if w<=0
    Any delta of all zeros is an error and will reflect
    All arguments are popped from the stack before error checking
    B Sorts only on first cell in each entry 
```

## STCK -- `0x5354434b`

```
B   (v n -- v ..)           Bury v value n deep into the stack
C   (.. -- cnt)             Get count of items on stack
D   (.. n -- ..)            Duplicate top n stack items
G   (n Vdlt Vsrc -- ..)     Read n stack entires from Funge-Space
K   (st en -- ..)           Push block of stack cells on top
N   (.. n -- ..)            Reverse n items on stack
P   (.. -- ..)              Print contents of stack, non-destructive
R   (.. -- ..)              Reverse all items on stack
S   (a b -- a a b)          Duplicate second on stack
T   (a b c -- b a c)        Swap second and third items on stack
U   (n -- n r)              Drop items from stack until n is found
W   (n Vdlt Vsrc -- )       Write n stack entires to Funge-Space
Z   (0string -- 0gnirts)    Reverse 0 terminated string on stack

    B if stack is not as deep as specified will reflect
    B if n is negative, push n zeroes above v
    K moves the block
    K if end is deeper than start, reflect
    K if end or start is negative, reflect
    K with start or end deeper than stack is NOT an error
    D works like ( a b c 3 -- a a b b c c )
    U reflects if the item is not found. r is the number of dropped items, next on stack will be the found value
    S with stack size <= 1 is NOT an error
    T with stack size <3 is NOT an error
    Both W and G will reflect on a negative count
    G must reproduce the stack written by W 
```

## STRN -- `0x5354524E`

```
A   (0gnirts 0gnirts -- 0gnirts)    Append bottom string to upper string
C   (0gnirts 0gnirts -- n)          Compare strings
D   (0gnirts --)                    Display a string
F   (0gnirts 0gnirts -- 0gnirts)    Search for bottom string in upper string
G   (Va -- 0gnirts)                 Get string from specified position
I   ( -- 0gnirts)                   Input a string
L   (0gnirts n -- 0gnirts)          Leftmost n characters of string
M   (0gnirts s n -- 0gnirts)        n characters starting at position s
N   (0gnirts -- 0gnirts n)          Get length of string
P   (0gnirts Va -- )                Put string at specified position
R   (0gnirts n -- 0gnirts)          Rightmost n characters of string
S   (n -- 0gnirts)                  String representation of a number
V   (0gnirts -- n)                  Retreive value from string

    functions G and P use deltas of 1,0,0 

Clarification

    For M, requesting zero characters from the string will return an empty string. Other interpreters may have 
    implemented this as reflecting
    
    For M, specifying a length that would go beyond the end of the string is legal and will return from the start til 
    the end of the string. Other interpreters may have implemented this as reflecting.
    
    For M, specifying a negative start or a start beyond the end of the string is an error and will reflect. Other 
    interpreters may have implemented this as returning a null string
    
    For R,L,M Requesting 0 or more characters from an empty string returns an empty string. Other interpreters may have 
    implemented this as reflecting.
    
    Specifiying a negative size for R,L,M is an error and will reflect. Other interpreters may have implemented this as 
    returning a null string
    
    For R,L requesting more characters than the length of the string will return the whole string. Other interpreters 
    may have implemented this as reflecting or returning a null string.
    
    For V, a non-numeric value in the string is not an error and will push a 0. Other interpreters may have implemented 
    this as reflecting. This function is implemented as the c function atoi (or equivalent for cell size), It will not 
    search the string for a numeric value. 
```

## SUBR -- `0x53554252`

```
A   ( -- )              Set absolute mode
C   (Va n -- Va Vd .. ) Call a subroutine
J   (Va -- )            Jump to another location
O   ( -- )              Set Relative mode
R   (Va Vd .. n -- ..)  Return from subroutine

    Default mode when SUBR is loaded is absolute mode.
    Mode setting is individual per IP
    Relative mode only affects the vectors from J and C. R should always return to the point of the original Call
    J and C each set delta to 1,0,0 at target, R restores the delta before the call.
    When C is executed, the tos specifies how many stack entries to retrieive from the stack and then place back onto 
        the stack after the retrurn address and delta vectors are pushed on the stack.
    When R is executed, the tos specifies how many stack entries to retrieve from the stack before retrieving the delta 
        and address vectors. The popped entries will be restored to the stack after the vectors are popped.
    Vectors in this function work directly on the IP and not through funge-space, therefore the IP storage offset does 
        not apply to these vectors. 

Clarification

    A and O were not part of the original spec and therefore there may be interpreters that will not handle these.
    
    If A and O are not supported then absolute mode should be the mode that C and J will operate in. Some interpreters 
    may have however implemented these in relative mode 
```

## TIME -- `0x54494D45`

```
D   ( -- n) Day of Month
F   ( -- n) Day since First of year
G   ( -- )  Set time functions to GMT
H   ( -- n) Hours
L   ( -- )  Set time functions to local time (default)
M   ( -- n) Minutes
O   ( -- n) Month (1=January)
S   ( -- n) Seconds
W   ( -- n) Day of Week (1=Sunday)
Y   ( -- n) Year
```

## TERM -- `0x5445524D`

```
C   ( -- )      Clear the screen
D   ( n -- )    Move cursor down n lines
G   (x y -- )   Put cursor at position x,y (home is 0,0)
H   ( -- )      Move cursor to home
L   ( -- )      Clear to end of line
S   ( -- )      Clear to end of screen
U   ( n -- )    Move cursor up n lines
```

## TRDS -- `0x54524453`

```
C   ( -- )  Continue normal time
D   (V -- ) Set absolute destination space coordinates
E   (V -- ) Set relative destination space corrdinates
G   ( -- n) Get current time point
I   ( -- )  Set inverse settings
J   ( -- )  Initiate a jump
P   ( -- n) Maximum distance in the past ip can jump to
R   ( -- )  Reset all tardis controls to default
S   ( -- )  Stop time
T   (n -- ) Set absolute destination time
U   (n -- ) Set relative destination time
V   (V -- ) Set destination vector

Notes to time travelling ips:

    Usage of time travel can be very punishing on the performance of the funge interpreter. If travel is performed to 
the past, the interpreter must be capable of reproducing all conditions that existed at the destination time, which 
includes all ips, stacks, and funge space cells. Some interpreters may only store time snapshots from only so far back 
(The furthest point in the past that can be jumped to can be determined with the P command). The RCS interpreter 
essentially reruns from point 0 and therefore all points in time can be jumped to (note: this can be quite time 
consuminmg if the destination time point is tens or hundreds of thousands of instructions from time point 0).

    Time travel into the future is not quite so punishing. The ip that time travels will merely be frozen until time 
catches up with it, at which point it will continue to execute.

Time travel into the past has the following consequences:

    1.  It is not possible to travel further back than time point 0. Attempts to travel beyond the beginning will leave 
        the ip at time point 0.
    2.  The original ip will still be born as per normal. example. If ip #2 is born at time 100 and then performs a jump 
        at time 200 to time 50, ip #2 will be born again at time 100, and there will now be 2 of them (the newly born ip 
        #2 in addition to the one that jumped) When the newly born ip #2 reaches the time it jumped (time point 200) it 
        will cease to exist, it will not perform another jump into the past, the original ip #2 however can still jump. 
        If the new ip #2 performs a time jump earlier than when the original jumped, the original will cease to exist.
    3.  An ip travelling in the past can kill its parent prior to its own birth, and will still exist.
    4.  A time travelling ip will retain its memory, in other words, its stack will be the same after the jump as before. 
        Also, unless the jump also included a space jump, the location will be the same physical space coodinates as when 
        it jumped.
    5.  An ip that perfroms a time jump without a space jump will execute the next instruction as if it had never jumped.
    6.  An ip that performs a space jump (with or without a time jump) will first execute the instruction it jumped to. 

When Multiple IPs Time Travel:

    In order to decrease the work on the interpreter, it is not necessary for the interpreter to remember future events. 
In other words when an ip travels back in time, everything occuring after the time point of destination need not recur 
if it does not occur in the further course of the program. When IPs time travel, only those ips that are currently in 
funge space at the time of arrival (either normally or from time travelling) will exist. Any ips that time travelled to 
a point later in time will not recur, unless the original time travel for these ips recur. Here are two examples to 
illustrate this point:

Example 1: Ip#1 travels back in time and arrives to time point 100, Ip#2 travels back to point 150. At point 150 the 
    time travelled copies of both ips will exist.

Example 2: Ip#1 travels back in time and arrives to time point 150, Ip#2 travels back to point 100. At the point where 
    ip#2 arrives, ip#1 has not yet arrived and therefore does not exist, it will also not exist when time point 150 
    arrives, only when the original jump for Ip#1 occurs, will history again be rewritten.

Tardis Operators Manual:

    1.  Before attempting any jumps, the ip's tardis should be reset to clear out any unwanted coordinates.
    2.  There are three coordinate settings: Space coordinates, vector after jump, and destination time. Any coordinate 
        that is not set will remain at the last setting, or at default if the tardis is reset.
    3.  Default coordinates are the current time, space, and vector.
    4.  Absolute coordinates are based from time point 0, and space 0,0,0.
    5.  Relative coordinates are based from the point the jump is actually made.
    6.  All tardis coordinates are retained following a jump.
    7.  The I command will set the tardis for the last source jump point. 
    
Stopping Time:

    An ip that issues a <S>top time command freezes the time counter. All other ips will be frozen until a <C>ontinue 
time command is executed. During the time that time is stopped, only the ip that executed the S command will continue to
run. For the purposes of time travel, the time used while time is stopped does not actually exist, and therefore cannot 
be jumped to. In other words everything the ip does is considered to have taken no time. If an ip that stops time is 
terminated, time will be continued
```

## TRGR -- `0x54524752`

```
A-Y ( -- )  Activate a trigger
Z   (V -- ) Specify where trigger table is located

    When an IP executes a trigger a new IP is created that will then run concurrently with the rest of the IPs. The new 
        IP will be generated in the same from as t, but will contain the position associated with the relevent entry in 
        the trigger table
    The original IP is unaffected and continues to run normally after having executed the trigger
    The trigger table contains executable code for the new IP, the code for A begins at the trigger table vector, B 
        starts at the same X one line lower, C below that, etc
    Both the original IP and the new IP will have the uid of the other pushed onto its stack 

Clarification

    Like in command 't', the newly created IP should execute first before the triggering IP.
    
    Initial direction of the trigger IP is 1,0,0. 
```

## UNIX -- `0x554e4958`

```
A   (id -- )                Set effective uid
B   (id -- )                Set effective gid
C   (0gnirts uid gid -- )   Change owner of a file
D   ( -- 0gnirts)           Get domain name of host
E   ( -- id)                Get effective uid
G   ( -- id)                Get real gid
H   ( -- id)                Get host id
K   (mask -- old)           Set umask
M   (0gnirts mode -- )      Change file access
N   ( -- 0gnirts)           Get host name
P   ( -- id)                Get process id
R   ( -- id)                Get effective gid
S   (id -- )                Set uid
T   (id -- )                Set gid
U   ( -- id)                Get real uid

    All functions reflect on error
    C: if uid or gid is -1 that component will not be set 
```

## WIND -- `0x57494E44`

```
B   (x1 y1 width height h -- )  Draw a box
C   (h -- )                     Close GC
D   (h -- )                     Drop (lower) Window
E   (h -- )                     Call event checker
I   (Va e h -- )                Install event handler
                                e   function
                                1   - Mouse Down
                                2   - Mouse Up
                                3   - Mouse Motion
                                4   - Key Pressed
                                5   - Expose
                                6   - Configuration
F   (r g b h -- )               Change foreground color
K   (h -- )                     Kill a window
L   (x1 y1 x2 y2 h -- )         Draw a line
M   (x y h -- )                 Move a window
O   (h -- )                     Open GC
P   (x y h -- )                 Draw a point
R   (h -- )                     Raise Window
S   (x y h -- )                 resize a window
T   (0gnirts x y h --)          Draw text in a window
W   (x y w h -- h)              Open a window
Y   (h -- )                     Copy back-buffer to screen

    Drawing commands: B, L, P, and T require an open GC 
```

## JSTR -- `0x4a535452`

```
P   (Vd Va n -- )           pop n cells off of the stack and write at Va with delta Vd.
G   (Vd Va n -- 0gnirts)    read n cells from position Va and delta Vd, push on stack as a string.

This extension is the Right Way to handle string writing/reading in fungespace. multidimensionality, people!
```

## SGNL -- `0x53474E4C`

```
H   ( Va n -- ) sets code at position Va to be handler for signal n.
K   ( p n -- )  send signal n to PID p
R   ( n -- )    restore default handler for signal n.  Not a stack!
M   ( h n -- )  adjust signal mask by n with method h. 
X   ( c -- )    set current cell to character c. esp. useful with 'Y'.
Y   ( -- )      stall; ip will not advance, delta is maintained.

All signals start with their default handlers.

When a signal is received, pid of sender and signal number are pushed onto stack, in that order. A new thread is created 
to handle each signal; to exit the signal handler, kill the thread with @.

For the 'M' command, h can be one of 0(SIG_BLOCK), 1(SIG_UNBLOCK), or 2(SIG_SETMASK).

Whatever X becomes has no effect on the ip that triggered it. 
```

## NCRS -- `0x4e435253`

```
B   ( -- )          Beep or visible beep.
E   (m -- )         Set echo mode to m (1 == echo, 0 == noecho). 
G   ( -- c)         get character c, modified by various flags
I   (m -- )         initialize curses mode if m == 1, else end curses mode.
K   (m -- )         set keypad mode to m (1 == keypad, 0 == nokeypad)
M   (x y -- )       move cursor to x,y
N   (m -- )         toggle input mode to m (1 == wait for newline, 0 == cbreak)
R   ( -- )          refresh(update) window. 
U   (c -- )         unget character c. only guaranteed to work once.
P   (c -- )         put the character c at the current cursor location.
S   (0gnirts -- )   write given string at current cursor location.
C   (m --           clear all or part of the screen. 
                    m can be one of 0(wholescreen), 1(end of line), or 2(bottom of screen).

All functions act as r on error.  K is useful for getting KEY_foo codes, i.e. arrow keys, other special keys.

R must be called for the results of other operations to be displayed. You *must* call 'I' at the beginning  *and* end 
of each program that uses NCRS.
```

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

## CFFI -- `0x43464649`

Taken from https://github.com/oshaboy/rcfunge-with-ffi

CFFI uses an extra pointer stack to push pointers to due to many architectures requiring 64-bit pointers while the funge
stack is only 32 bits.

(f) - funge stack  
(p) - pointer stack

B - pop(f) index, pop(p) C char * pointer then push(f) the char at that location.

C -
pop(f) return type (0 for integer, 1 for pointer, 2 for void)  
pop(f) len  
pop(f) argument type bitmask (LSB to MSB, 0 for integer, 1 for pointer).    
pop len arguments from the appropriate stack.   
pop(p) C function pointer.  
call the C function with the arguments.  
Push the return value to the appropriate stack.

D - duplicate pointer on pointer stack.   
F - pop(p) C pointer and free it.   
G - pop(p) then push(f) its 2 words. (32 bit architectures will push 0 then the pointer)  
I - pop(p).   
L - pop(p) as char * then load a dynamic library with that filename and push(p) its pointer, reflect on error. (
dlopen)  
M - pop(f) len then create an array and then push(p) its C pointer. (malloc)  
O - Display the contents of the pointer stack (without popping)  
P - pop(f) twice then push(p) a pointer generated from the two words. (32 bit architectures should push 0 first)  
S - pop(f) a null terminated string and create a C String out of it then push(p) its pointer. (like M but different)  
T - pop(p) char * , then pop(p) dynamic library pointer, then push(p) a symbol from the library, reflect on error. (
dlsym)  
U - pop(p) dynamic library pointer and close it, reflect on error. (dlclose)  
W - pop(f) index, then pop(p) C array pointer then push(f) the word in the array at that index.   
X - pop(f) index, then data then pop(p) C array pointer and insert the data into the array.   
Y - swap two pointers on pointer stack.

## IFFI -- `0x49464649`

Unless you're going to embed an entire C-INTERCAL compiler in your implementation I don't think this one is actually
implementable, but for the sake of a complete archive I put it here anyway.

Taken from http://catb.org/~esr/intercal/ick.htm#The-IFFI-Fingerprint <br>
You may need the rest of that page for it to make any sense.

```
    To a Funge program, the external calls interface is accessed via a Funge-98 ’fingerprint’ defined by the interpreter. 
The name of the fingerprint is 0x49464649, or as text, ‘IFFI’.

    When a program formed by linking INTERCAL and Befunge-98 is run, the first thing that happens is some internal 
INTERCAL initialisation which is not visible to either program, and then initialisation routines specified in the 
Befunge-98 program run (if an initialisation routine is also specified in a linked C program using ick_startup, it is 
unspecified whether the C or Befunge-98 initialisation happens first.) In the Befunge program, the initialisation 
routine consists of everything that happens until the ‘Y’ command in the ‘IFFI’ fingerprint is run; the author of the 
Funge-98 must load the ‘IFFI’ fingerprint themselves during this initialisation to access that command. (This is so that 
the Befunge program ends up complying with the Funge-98 standard; commands not defined in that standard cannot be used 
until a fingerprint is loaded.) During initialisation, no commands from the ‘IFFI’ fingerprint may be used except ‘Y’ 
and ‘A’. (If a different command is used, ‘C’, ‘M’, and ‘X’ remove the arguments they would use from the stack (if any) 
but otherwise do nothing, and the other commands in the ‘IFFI’ fingerprint reflect.)

    After the ‘Y’ command is called, the INTERCAL program starts running; in order for the Befunge program to regain 
control, it has to be NEXTed to from the INTERCAL program, or COME or NEXT FROM the INTERCAL program, or contain the 
line label to which syntax in the INTERCAL program was CREATEd. (In other words, the normal INTERCAL ways of 
transferring information between parts of a program.) In order to do this, therefore, line labels and INTERCAL control 
flow statements must be placed into the Befunge program.

    Code like COME FROM (100) is a single statement in INTERCAL, but several statements in Funge-98; therefore, some 
method of telling the interpreter where to start executing to look for COME FROMs, NEXT FROMs, and line labels is 
needed. The method used by C-INTERCAL is that of the ’marker’; a marker is represented by character 0xB7 (a mid-dot in 
Latin-1) in the input Funge-98 program, but is transformed to a capital ‘M’ by ick. (The reason for using a special 
character for a marker and transforming it rather than just using ‘M’ is to prevent occurences of ‘M’ in comments and 
string literals, etc., having an effect on the control flow of the program.) Whenever a NEXT or line label is 
encountered (in the INTERCAL program, the Funge program or elsewhere), the Funge program is executed starting from each 
marker in each cardinal direction to look for line labels or COME/NEXT FROMs respectively. Therefore, COME FROM (100) 
is written in Funge-98 as Maa*C (where the M is a marker in the source code), and likewise the line label (100) would 
be written as Maa*L. (This code can be written in any cardinal direction, that is left to right, top to bottom, right 
to left, or bottom to top, but not diagonally or flying.) There are likely to be unused directions from markers, which 
will be evaluated too; you can (and must) close these off by reflecting code execution back into that marker, another 
marker, or a non-marker M. Note also that a marker remains in Funge-space even if the M on the same square is deleted 
(the marker itself is not visible to the g command, though).

Here are the commands in the ‘IFFI’ fingerprint:

A
    This command pops a line number and then an 0"gnirts"-format string from the stack; they are used as the line 
    number and signature to CREATE syntax in the INTERCAL program; for details of the format of the signature, see 
    ick_create. Although using this command during speculative execution works, doing so is not recommended; if the 
    target line number for CREATEd syntax is changed during speculative execution to find the line that that syntax 
    corresponds to, its effect is delayed until after the original line is found and execution continues from that 
    point. (Side effects during speculative execution are never recommended, because they might or might not be 
    optimised away.)

C
    During speculative execution to find COME FROMs and NEXT FROMs, pops a line label off the top of the stack and does 
    a COME FROM that location. During speculative excution to find line labels, pops the top of the stack and ends that 
    particular speculative execution as a failure. When not doing speculative execution, pops and discards the top 
    element of the stack.

D
    This command must only be used when the Funge program is executing a CREATEd command, and allows access to the 
    arguments that command has. It pops an integer off the top of the stack, and treats it as an argument position 
    (0-based, so 0 refers to the first argument, 1 refers to the second, and so on). Note that providing an invalid 
    argument number, or running this command when not implementing a CREATEd command, leads to undefined behaviour 
    (possibly a reflection, possibly a segfault, possibly worse).

    The command pushes information about the argument chosen onto the stack; the following information is pushed from 
    bottom to top:

        The data type of the argument, in bits (16 if the argument was a onespot variable or expression of onespot type, 
        and 32 if the argument was a twospot variable or expression of twospot type). Note that this is under the 
        C-INTERCAL typing rules, rather than the INTERCAL-72 typing rules (that is, select’s type is always that of its 
        right argument no matter how many bits are actually selected).
        
        1 if the argument is an array variable, 0 if it is a scalar value.
        
        0 if the argument is not a variable, or the variable’s number if it is (e.g. .123 would push 123 here, but .1~.2 
        would push 0).
        
        The argument’s value at the time that the CREATEd instruction was called.
        
        The argument’s value now, or alternatively a repeat of the previous stack element if -a (see -a) was not used. 
        (Without -a, the information needed to re-evaluate the expression is not available.)

F
    During speculative execution, this command reflects; otherwise, this command pops an integer from the top of stack, 
    and FORGETs that many NEXT stack entries (or all of them if the argument given is negative).

G
    This command pops an integer from the top of stack. If it is positive, the value of the onespot variable whose name 
    is the popped integer is pushed onto the stack; if it is negative, the value of the twospot variable whose name is 
    minus the popped integer is pushed onto the stack; and if it is zero, the command reflects. If the referenced 
    variable is not in the INTERCAL program at all, this causes an INTERCAL error due to referencing a nonexistent 
    variable.

L
    During speculative execution to find COME FROMs and NEXT FROMs, this command pops and discards the top stack 
    element, then ends that speculative execution. During speculative execution to find a line label, this command pops 
    an integer from the top of stack and succeeds with that integer as the line label (that is, it is possible to NEXT 
    to an L in the Funge program if a marker, followed by code to push the correct line number onto the stack, precedes 
    that L). When not doing speculative execution, the integer on the top of the stack is used as a line label (assuming 
    it is in the range 1–65535, otherwise it is popped and discarded), and a search is made for COME FROMs and NEXT 
    FROMs aiming for that line label (including in the INTERCAL program and the Befunge program itself, as well as 
    programs in any other language which may be linked in). Note that just as in INTERCAL, it is possible to NEXT to a 
    line label which has a COME FROM aiming for it, in which case the COME FROM will come from that line label as soon 
    as the NEXT transfers control to it.
    
M
    Does nothing if not in speculative execution, or ends the current speculative execution with failure. (This is so 
    that code like

     v
    >M5C
     ^

    does exactly the same thing as COME FROM (5), even when, for instance, it is entered from the left in the Funge 
    program, rather than gaining control from the line label (5).)
    
N
    During speculative execution, reflects. Otherwise, pops the top stack element, interprets it as a line label, and 
    NEXTs to that line label (this may start speculative execution to look for line labels, but might not if it isn’t 
    needed, for instance if the line label in question is in the INTERCAL program or in a C program linked to the 
    Befunge program).
    
R
    During speculative execution, reflects. Otherwise, pops the top stack element, removes that many items from the 
    NEXT stack, and RESUMEs at the last item removed. (If the top stack element was zero, negative, or too large, this 
    will cause a fatal error in the INTERCAL program.)
    
S
    Pops a variable number (interpreted as onespot if positive, or minus the number of a twospot variable if negative) 
    and an integer from the stack, and sets the referenced variable to the integer. This reflects if an attempt is made 
    to set the nonexistent variable 0, causes a fatal error in the INTERCAL program if an attempt is made to set a 
    variable that doesn’t exist there, and does not set read-only variables (but pops the stack anyway). If the integer 
    is too high for the variable it is being stored in, only the least significant 16 or 32 bits from it will be used; 
    and likewise, if it is negative, it will be treated as the two’s complement of the number given.
    
V
    Pops a CREATEd argument index and an integer from the top of stack. (This is undefined behaviour if not in the 
    implementation of a CREATEd statement, or if the referenced argument does not exist; as with the D instruction, 0 
    refers to the first argument, 1 to the second, and so on.) If the -a option is not used, this command does nothing; 
    otherwise, the value of the argument will be set to the integer. (This involves doing a reverse assignment if the 
    argument is a non-variable expression, as usual, and causes a fatal error in the INTERCAL program if the reverse 
    assignment is impossible or an attempt is made to assign a scalar to an array.)
    
X
    This is identical to C, except that it does a NEXT FROM rather than a COME FROM.

    As with external calls to C, terminating any program involved (whether the INTERCAL program with GIVE UP, the 
Befunge program with @ or q, or a C program with exit()) causes all programs involved to terminate, and likewise a fatal 
error will end all programs with an error.

    One final point which is probably worth mentioning is that flow control instructions only record the IP’s position 
and direction, nothing else; so for instance, if the stack is modified in one part of the code, those modifications will 
remain even after a RESUME, for instance. 
```
