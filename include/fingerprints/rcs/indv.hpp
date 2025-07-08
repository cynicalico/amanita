#ifndef AMANITA_INDV_HPP
#define AMANITA_INDV_HPP

/* G   (Vp - n)    Pointer get number
 * P   (n Vp -- )  Pointer put number
 * V   (Va -- V)   Pointer get vector
 * W   (V Va --)   Pointer put vector
 *
 *     Pointer functions pop a vector off the stack which points to another vector in memory which is the pointer to the
 *     target cell.
 *
 * Clarification
 *
 *     This fingerprint was originally called PNTR. Early on it was renamed. to INDV. Some interpreters may implement
 *     this fingerprint as PNTR. Any use of PNTR should be changed to use INDV. Otherwise consider PNTR to be a synonum
 *     of INDV
 *
 *     Vectors are stored in memory with a delta of 1,0,0 with Z being first in trefunge, and Y first in befunge.
 *     Originally Rc/Funge-98 stored this vector in reverse and became known as Rc/Funge-98 illogical order. Other
 *     interpreters may have copied the original way that Rc/Funge-98 stored the vectors.
 */

#include "common.hpp"

namespace fingerprints::indv {
InstructionAction get_number(State &, Fungespace &, InstructionPointer &);
InstructionAction put_number(State &, Fungespace &, InstructionPointer &);
InstructionAction get_vector(State &, Fungespace &, InstructionPointer &);
InstructionAction put_vector(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .id = 0x494E4456,
        .fns = {
                {Instruction::G, get_number},
                {Instruction::P, put_number},
                {Instruction::V, get_vector},
                {Instruction::W, put_vector},
        }};
} // namespace fingerprints::indv

#endif // AMANITA_INDV_HPP
