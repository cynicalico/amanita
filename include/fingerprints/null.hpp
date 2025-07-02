#ifndef AMANITA_NULL_HPP
#define AMANITA_NULL_HPP

#include "common.hpp"

InstructionAction null_all(Fungespace &, InstructionPointer &ip);

const Fingerprint FNG_NULL{
        .id = 0x4e554c4c,
        .fns = {
                {Instruction::A, null_all}, {Instruction::B, null_all}, {Instruction::C, null_all},
                {Instruction::D, null_all}, {Instruction::E, null_all}, {Instruction::F, null_all},
                {Instruction::G, null_all}, {Instruction::H, null_all}, {Instruction::I, null_all},
                {Instruction::J, null_all}, {Instruction::K, null_all}, {Instruction::L, null_all},
                {Instruction::M, null_all}, {Instruction::N, null_all}, {Instruction::O, null_all},
                {Instruction::P, null_all}, {Instruction::Q, null_all}, {Instruction::R, null_all},
                {Instruction::S, null_all}, {Instruction::T, null_all}, {Instruction::U, null_all},
                {Instruction::V, null_all}, {Instruction::W, null_all}, {Instruction::X, null_all},
                {Instruction::Y, null_all}, {Instruction::Z, null_all},
        }};

#endif // AMANITA_NULL_HPP
