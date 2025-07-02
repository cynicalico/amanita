#ifndef AMANITA_NULL_HPP
#define AMANITA_NULL_HPP

/* After successfully loading fingerprint 0x4e554c4c, all 26 instructions A to Z take on the semantics of r.
 *
 * This can be loaded before loading a regular transparent fingerprint to make it act opaquely.
 */

#include "common.hpp"

InstructionAction null_reflect(Fungespace &, InstructionPointer &ip);

const Fingerprint FNG_NULL{
        .id = 0x4e554c4c,
        .fns = {
                {Instruction::A, null_reflect}, {Instruction::B, null_reflect}, {Instruction::C, null_reflect},
                {Instruction::D, null_reflect}, {Instruction::E, null_reflect}, {Instruction::F, null_reflect},
                {Instruction::G, null_reflect}, {Instruction::H, null_reflect}, {Instruction::I, null_reflect},
                {Instruction::J, null_reflect}, {Instruction::K, null_reflect}, {Instruction::L, null_reflect},
                {Instruction::M, null_reflect}, {Instruction::N, null_reflect}, {Instruction::O, null_reflect},
                {Instruction::P, null_reflect}, {Instruction::Q, null_reflect}, {Instruction::R, null_reflect},
                {Instruction::S, null_reflect}, {Instruction::T, null_reflect}, {Instruction::U, null_reflect},
                {Instruction::V, null_reflect}, {Instruction::W, null_reflect}, {Instruction::X, null_reflect},
                {Instruction::Y, null_reflect}, {Instruction::Z, null_reflect},
        }};

#endif // AMANITA_NULL_HPP
