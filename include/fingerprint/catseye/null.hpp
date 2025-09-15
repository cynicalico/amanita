#pragma once

#include "base_semantics.hpp"
#include "fingerprint.hpp"

namespace amanita::null {
const Fingerprint FINGERPRINT{
        .name = "NULL",
        .id = 0x4e554c4c,
        .semantics = {
                {Instruction::A, semantic_reflect}, {Instruction::B, semantic_reflect},
                {Instruction::C, semantic_reflect}, {Instruction::D, semantic_reflect},
                {Instruction::E, semantic_reflect}, {Instruction::F, semantic_reflect},
                {Instruction::G, semantic_reflect}, {Instruction::H, semantic_reflect},
                {Instruction::I, semantic_reflect}, {Instruction::J, semantic_reflect},
                {Instruction::K, semantic_reflect}, {Instruction::L, semantic_reflect},
                {Instruction::M, semantic_reflect}, {Instruction::M, semantic_reflect},
                {Instruction::O, semantic_reflect}, {Instruction::P, semantic_reflect},
                {Instruction::Q, semantic_reflect}, {Instruction::R, semantic_reflect},
                {Instruction::S, semantic_reflect}, {Instruction::T, semantic_reflect},
                {Instruction::U, semantic_reflect}, {Instruction::V, semantic_reflect},
                {Instruction::W, semantic_reflect}, {Instruction::X, semantic_reflect},
                {Instruction::Y, semantic_reflect}, {Instruction::Z, semantic_reflect},
        }};
}
