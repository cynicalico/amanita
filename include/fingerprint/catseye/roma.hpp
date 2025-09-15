#pragma once

#include "fingerprint.hpp"

namespace amanita::roma {
void semantic_c(State *, InstructionPointer *, std::vector<Action> &);
void semantic_d(State *, InstructionPointer *, std::vector<Action> &);
void semantic_i(State *, InstructionPointer *, std::vector<Action> &);
void semantic_l(State *, InstructionPointer *, std::vector<Action> &);
void semantic_m(State *, InstructionPointer *, std::vector<Action> &);
void semantic_v(State *, InstructionPointer *, std::vector<Action> &);
void semantic_x(State *, InstructionPointer *, std::vector<Action> &);

const static Fingerprint FINGERPRINT(
        "ROMA",
        {
                {Instruction::C, semantic_c},
                {Instruction::D, semantic_d},
                {Instruction::I, semantic_i},
                {Instruction::L, semantic_l},
                {Instruction::M, semantic_m},
                {Instruction::V, semantic_v},
                {Instruction::X, semantic_x},
        });
} // namespace amanita::roma
