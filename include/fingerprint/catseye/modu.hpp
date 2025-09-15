#pragma once

#include "fingerprint.hpp"

namespace amanita::modu {
void semantic_signed_result_modulo(State *, InstructionPointer *, std::vector<Action> &);
void semantic_sam_holden_unsigned_result_modulo(State *, InstructionPointer *, std::vector<Action> &);
void semantic_c_language_integer_remainder(State *, InstructionPointer *, std::vector<Action> &);

const static Fingerprint FINGERPRINT{
        .name = "MODU",
        .id = 0x4d4f4455,
        .semantics = {
                {Instruction::M, semantic_signed_result_modulo},
                {Instruction::U, semantic_sam_holden_unsigned_result_modulo},
                {Instruction::R, semantic_c_language_integer_remainder},
        }};
} // namespace amanita::modu
