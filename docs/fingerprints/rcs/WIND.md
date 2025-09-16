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
