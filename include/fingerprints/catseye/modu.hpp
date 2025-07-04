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

namespace modu {
InstructionAction signed_result_modulo(Fungespace &, InstructionPointer &ip);
InstructionAction sam_holden_unsigned_result_modulo(Fungespace &, InstructionPointer &ip);
InstructionAction c_language_integer_remainder(Fungespace &, InstructionPointer &ip);

const Fingerprint FINGERPRINT{
        .name = "MODU",
        .id = 0x4d4f4455,
        .fns = {
                {Instruction::M, signed_result_modulo},
                {Instruction::U, sam_holden_unsigned_result_modulo},
                {Instruction::R, c_language_integer_remainder},
        }};
} // namespace modu

#endif // AMANITA_MODU_HPP
