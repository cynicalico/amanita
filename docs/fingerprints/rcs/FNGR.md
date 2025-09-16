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
