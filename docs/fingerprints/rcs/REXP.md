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
