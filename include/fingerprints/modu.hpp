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

InstructionAction modu_m(Fungespace &, InstructionPointer &ip);
InstructionAction modu_u(Fungespace &, InstructionPointer &ip);
InstructionAction modu_r(Fungespace &, InstructionPointer &ip);

const Fingerprint FNG_MODU{
        .id = 0x4d4f4455,
        .fns = {
                {Instruction::M, modu_m},
                {Instruction::U, modu_u},
                {Instruction::R, modu_r},
        }};

#endif // AMANITA_MODU_HPP
