#ifndef AMANITA_REFC_HPP
#define AMANITA_REFC_HPP

/* The REFC fingerprint allows vectors to be encoded into and decoded from single scalar cell values.
 * After successfully loading REFC, the instructions D and R take on new semantics.
 *
 * R 'Reference' pops a vector off the stack, and pushes a scalar value back onto the stack, unique within an internal
 *      list of references, which refers to that vector.
 *
 * D 'Dereference' pops a scalar value off the stack, and pushes the vector back onto the stack which corresponds to
 *      that unique reference value.
 *
 * The internal list of references is considered shared among all IP's, so a global static can be used to store this
 * list, so that this extension remains tame.
 */

#include "common.hpp"

namespace refc {
InstructionAction reference(Fungespace &, InstructionPointer &ip);
InstructionAction dereference(Fungespace &, InstructionPointer &ip);

const Fingerprint FINGERPRINT{
        .name = "REFC",
        .id = 0x52454643,
        .fns = {
                {Instruction::R, reference},
                {Instruction::D, dereference},
        }};
} // namespace refc

#endif // AMANITA_REFC_HPP
