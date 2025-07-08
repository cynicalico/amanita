#ifndef AMANITA_FING_HPP
#define AMANITA_FING_HPP

/*
 * X	(sem sem -- )	Swap two semantics
 * Y	(sem -- )	    Pop semantic
 * Z	(src dst -- )	Push source semantic onto dst
 *
 *      This fingerprint works by pushing and popping the semantic stacks. an empty stack will pop a reflect
 *      sem can be 0-25 or 'A through 'Z. Any other value is an error and will reflect
 *      X will swap a reflect in place of an empty stack
 *      Y will not reflect popping an empty semantic stack
 *      Z will push a reflect if the source semantic stack is empty
 */

#include "common.hpp"

namespace fingerprints::fing {
InstructionAction swap(Fungespace &, InstructionPointer &ip);
InstructionAction pop(Fungespace &, InstructionPointer &ip);
InstructionAction push(Fungespace &, InstructionPointer &ip);

const Fingerprint SPEC{
        .id = 0x46494e47,
        .fns = {
                {Instruction::X, swap},
                {Instruction::Y, pop},
                {Instruction::Z, push},
        }};
} // namespace fingerprints::fing


#endif // AMANITA_FING_HPP
