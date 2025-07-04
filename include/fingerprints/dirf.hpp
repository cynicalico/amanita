#ifndef AMANITA_DIRF_HPP
#define AMANITA_DIRF_HPP

/* C    (0gnirts -- )	Change directory
 * M	(0gnirts -- )	Make a directory
 * R	(0gnirts -- )	Remove a directory
 *
 * All functions act as r on failure
 */

#include "common.hpp"

InstructionAction dirf_cd(Fungespace &, InstructionPointer &ip);
InstructionAction dirf_mkdir(Fungespace &, InstructionPointer &ip);
InstructionAction dirf_rmdir(Fungespace &, InstructionPointer &ip);

const Fingerprint FNG_DIRF{
        .id = 0x44495246,
        .fns = {
                {Instruction::C, dirf_cd},
                {Instruction::M, dirf_mkdir},
                {Instruction::R, dirf_rmdir},
        }};

#endif // AMANITA_DIRF_HPP
