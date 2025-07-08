#ifndef AMANITA_CPLI_HPP
#define AMANITA_CPLI_HPP

/*
 * A	(ar ai br bi -- r i)	Add two complex integers
 * D	(ar ai br bi -- r i)	Divide two complex integers
 * M	(ar ai br bi -- r i)	Multiply two complex integers
 * O	(r i -- )	            Output a complex number
 * S	(ar ai br bi -- r i)	Subtract two complex integers
 * V	(r i -- n)	            Absolute value of a complex integer
 */

#include "common.hpp"

namespace fingerprints::cpli {
InstructionAction add(State &, Fungespace &, InstructionPointer &);
InstructionAction div(State &, Fungespace &, InstructionPointer &);
InstructionAction mul(State &, Fungespace &, InstructionPointer &);
InstructionAction print(State &, Fungespace &, InstructionPointer &);
InstructionAction sub(State &, Fungespace &, InstructionPointer &);
InstructionAction abs(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .name = "CPLI",
        .id = 0x43504c49,
        .fns = {
                {Instruction::A, add},
                {Instruction::D, div},
                {Instruction::M, mul},
                {Instruction::O, print},
                {Instruction::S, sub},
                {Instruction::V, abs},
        }};
} // namespace fingerprints::cpli

#endif // AMANITA_CPLI_HPP
