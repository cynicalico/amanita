#ifndef AMANITA_DATE_HPP
#define AMANITA_DATE_HPP

/* A   (y m d days -- y m d)       Add days to date
 * C   (jd -- y m d)               Convert julian day to calendar date
 * D   (y1 m1 d1 y2 m2 d2 -- days) Days between dates
 * J   (y m d -- jd)               Calendar date to julian day
 * T   (y d -- y m d)              Year/day-of-year to full date
 * W   (y m d -- d)                Day of week (0=monday)
 * Y   (y m d -- d)                Day of year (0=Jan 1)
 *
 *     A may be negative
 *     Since all these functions work with integer values, julian day calculations assume 12:00 noon as the time.
 *     Gregorian calendar is assumed for calendar dates
 */

#include "common.hpp"

namespace fingerprints::date {
InstructionAction add_days(State &, Fungespace &, InstructionPointer &);
InstructionAction julian_to_calendar(State &, Fungespace &, InstructionPointer &);
InstructionAction days_difference(State &, Fungespace &, InstructionPointer &);
InstructionAction calendar_to_julian(State &, Fungespace &, InstructionPointer &);
InstructionAction yd_to_ymd(State &, Fungespace &, InstructionPointer &);
InstructionAction day_of_week(State &, Fungespace &, InstructionPointer &);
InstructionAction day_of_year(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .id = 0x44415445,
        .fns = {{Instruction::A, add_days},
                {Instruction::C, julian_to_calendar},
                {Instruction::D, days_difference},
                {Instruction::J, calendar_to_julian},
                {Instruction::T, yd_to_ymd},
                {Instruction::W, day_of_week},
                {Instruction::Y, day_of_year}}};
} // namespace fingerprints::date

#endif // AMANITA_DATE_HPP
