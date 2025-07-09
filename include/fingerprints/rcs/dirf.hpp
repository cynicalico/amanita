#pragma once

/* C    (0gnirts -- )	Change directory
 * M	(0gnirts -- )	Make a directory
 * R	(0gnirts -- )	Remove a directory
 *
 * All functions act as r on failure
 */

#include "common.hpp"

namespace fingerprints::dirf {
InstructionAction cd(State &, Fungespace &, InstructionPointer &);
InstructionAction mkdir(State &, Fungespace &, InstructionPointer &);
InstructionAction rmdir(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .name = "DIRF",
        .id = 0x44495246,
        .fns = {
                {Instruction::C, cd},
                {Instruction::M, mkdir},
                {Instruction::R, rmdir},
        }};
} // namespace fingerprints::dirf
