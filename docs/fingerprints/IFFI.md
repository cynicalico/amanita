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
