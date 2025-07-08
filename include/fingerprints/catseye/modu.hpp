#ifndef AMANITA_MODU_HPP
#define AMANITA_MODU_HPP

/* The MODU fingerprint implements some of the finer, less-well-agreed-upon points of modulo arithmetic. With positive
 *      arguments, these instructions work exactly the same as % does. However, when negative values are involved, they
 *      all work differently:
 *
 * M: signed-result modulo:
 *
 * U: Sam Holden's unsigned-result modulo
 *
 * R: C-language integer remainder
 */

#include "common.hpp"

namespace fingerprints::modu {
InstructionAction signed_result_modulo(State &, Fungespace &, InstructionPointer &);
InstructionAction sam_holden_unsigned_result_modulo(State &, Fungespace &, InstructionPointer &);
InstructionAction c_language_integer_remainder(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .name = "MODU",
        .id = 0x4d4f4455,
        .fns = {
                {Instruction::M, signed_result_modulo},
                {Instruction::U, sam_holden_unsigned_result_modulo},
                {Instruction::R, c_language_integer_remainder},
        }};
} // namespace fingerprints::modu

#endif // AMANITA_MODU_HPP
