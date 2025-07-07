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

namespace date {
InstructionAction add_days(Fungespace &, InstructionPointer &ip);
InstructionAction julian_to_calendar(Fungespace &, InstructionPointer &ip);
InstructionAction days_difference(Fungespace &, InstructionPointer &ip);
InstructionAction calendar_to_julian(Fungespace &, InstructionPointer &ip);
InstructionAction yd_to_ymd(Fungespace &, InstructionPointer &ip);
InstructionAction day_of_week(Fungespace &, InstructionPointer &ip);
InstructionAction day_of_year(Fungespace &, InstructionPointer &ip);

const Fingerprint FINGERPRINT{
        .id = 0x44415445,
        .fns = {{Instruction::A, add_days},
                {Instruction::C, julian_to_calendar},
                {Instruction::D, days_difference},
                {Instruction::J, calendar_to_julian},
                {Instruction::T, yd_to_ymd},
                {Instruction::W, day_of_week},
                {Instruction::Y, day_of_year}}};
} // namespace date

#endif // AMANITA_DATE_HPP
