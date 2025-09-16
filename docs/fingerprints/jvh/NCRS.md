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
