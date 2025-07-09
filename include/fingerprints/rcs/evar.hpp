#pragma once

/* G	(0gnirts -- 0gnirts)	Get value of an environment variable
 * N	( -- n )	            Get number of environment variables
 * P	(0gnirts --)	        Put a value into the environment (form: name=value)
 * V	(n -- 0gnirts)	        Get nth environment variable (form: name=value)
 */

#include "common.hpp"

namespace fingerprints::evar {
InstructionAction get(State &, Fungespace &, InstructionPointer &);
InstructionAction count(State &, Fungespace &, InstructionPointer &);
InstructionAction put(State &, Fungespace &, InstructionPointer &);
InstructionAction get_nth(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .name = "EVAR",
        .id = 0x45564152,
        .fns = {
                {Instruction::G, get},
                {Instruction::N, count},
                {Instruction::P, put},
                {Instruction::V, get_nth},
        }};
} // namespace fingerprints::evar
