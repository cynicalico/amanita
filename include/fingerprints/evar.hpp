#ifndef AMANITA_EVAR_HPP
#define AMANITA_EVAR_HPP

/* G	(0gnirts -- 0gnirts)	Get value of an environment variable
 * N	( -- n )	            Get number of environment variables
 * P	(0gnirts --)	        Put a value into the environment (form: name=value)
 * V	(n -- 0gnirts)	        Get nth environment variable (form: name=value)
 */

#include "common.hpp"

namespace evar {
InstructionAction get(Fungespace &, InstructionPointer &ip);
InstructionAction count(Fungespace &, InstructionPointer &ip);
InstructionAction put(Fungespace &, InstructionPointer &ip);
InstructionAction get_nth(Fungespace &, InstructionPointer &ip);

const Fingerprint FINGERPRINT{
        .id = 0x45564152,
        .fns = {
                {Instruction::G, get},
                {Instruction::N, count},
                {Instruction::P, put},
                {Instruction::V, get_nth},
        }};
} // namespace evar

#endif // AMANITA_EVAR_HPP
