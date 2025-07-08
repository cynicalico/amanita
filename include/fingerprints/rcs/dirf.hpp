#ifndef AMANITA_DIRF_HPP
#define AMANITA_DIRF_HPP

/* C    (0gnirts -- )	Change directory
 * M	(0gnirts -- )	Make a directory
 * R	(0gnirts -- )	Remove a directory
 *
 * All functions act as r on failure
 */

#include "common.hpp"

namespace fingerprints::dirf {
InstructionAction cd(Fungespace &, InstructionPointer &ip);
InstructionAction mkdir(Fungespace &, InstructionPointer &ip);
InstructionAction rmdir(Fungespace &, InstructionPointer &ip);

const Fingerprint SPEC{
        .id = 0x44495246,
        .fns = {
                {Instruction::C, cd},
                {Instruction::M, mkdir},
                {Instruction::R, rmdir},
        }};
} // namespace fingerprints::dirf

#endif // AMANITA_DIRF_HPP
