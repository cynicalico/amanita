#pragma once

/*
 * D   ( -- n) Day of Month
 * F   ( -- n) Day since First of year
 * G   ( -- )  Set time functions to GMT
 * H   ( -- n) Hours
 * L   ( -- )  Set time functions to local time (default)
 * M   ( -- n) Minutes
 * O   ( -- n) Month (1=January)
 * S   ( -- n) Seconds
 * W   ( -- n) Day of Week (1=Sunday)
 * Y   ( -- n) Year
 */

#include "common.hpp"

namespace fingerprints::time {
InstructionAction day(State &, Fungespace &, InstructionPointer &);
InstructionAction day_of_year(State &, Fungespace &, InstructionPointer &);
InstructionAction set_gmt(State &, Fungespace &, InstructionPointer &);
InstructionAction hours(State &, Fungespace &, InstructionPointer &);
InstructionAction set_local(State &, Fungespace &, InstructionPointer &);
InstructionAction minutes(State &, Fungespace &, InstructionPointer &);
InstructionAction month(State &, Fungespace &, InstructionPointer &);
InstructionAction seconds(State &, Fungespace &, InstructionPointer &);
InstructionAction day_of_week(State &, Fungespace &, InstructionPointer &);
InstructionAction year(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .name = "TIME",
        .id = 0x54494D45,
        .fns = {
                {Instruction::D, day},
                {Instruction::F, day_of_year},
                {Instruction::G, set_gmt},
                {Instruction::H, hours},
                {Instruction::L, set_local},
                {Instruction::M, minutes},
                {Instruction::O, month},
                {Instruction::S, seconds},
                {Instruction::W, day_of_week},
                {Instruction::Y, year},
        }};
} // namespace fingerprints::time
