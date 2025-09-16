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
