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
