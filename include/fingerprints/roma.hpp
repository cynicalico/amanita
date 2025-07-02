#ifndef AMANITA_ROMA_HPP
#define AMANITA_ROMA_HPP

#include "common.hpp"

InstructionAction roma_c(Fungespace &, InstructionPointer &ip);

InstructionAction roma_d(Fungespace &, InstructionPointer &ip);

InstructionAction roma_i(Fungespace &, InstructionPointer &ip);

InstructionAction roma_l(Fungespace &, InstructionPointer &ip);

InstructionAction roma_m(Fungespace &, InstructionPointer &ip);

InstructionAction roma_v(Fungespace &, InstructionPointer &ip);

InstructionAction roma_x(Fungespace &, InstructionPointer &ip);

const static Fingerprint ROMA{
        .id = 0x524f4d41,
        .fns = {
                {Instruction::C, roma_c},
                {Instruction::D, roma_d},
                {Instruction::I, roma_i},
                {Instruction::L, roma_l},
                {Instruction::M, roma_m},
                {Instruction::V, roma_v},
                {Instruction::X, roma_x},
        }};

// constexpr std::int64_t ROMA = 0x524f4d41;

#endif // AMANITA_ROMA_HPP
