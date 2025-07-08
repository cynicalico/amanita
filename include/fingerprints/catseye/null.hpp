#ifndef AMANITA_NULL_HPP
#define AMANITA_NULL_HPP

/* After successfully loading fingerprint 0x4e554c4c, all 26 instructions A to Z take on the semantics of r.
 *
 * This can be loaded before loading a regular transparent fingerprint to make it act opaquely.
 */

#include "base_instructions.hpp"
#include "common.hpp"

namespace fingerprints::null {
const Fingerprint SPEC{
        .name = "NULL",
        .id = 0x4e554c4c,
        .fns = {
                {Instruction::A, instruction_reflect}, {Instruction::B, instruction_reflect},
                {Instruction::C, instruction_reflect}, {Instruction::D, instruction_reflect},
                {Instruction::E, instruction_reflect}, {Instruction::F, instruction_reflect},
                {Instruction::G, instruction_reflect}, {Instruction::H, instruction_reflect},
                {Instruction::I, instruction_reflect}, {Instruction::J, instruction_reflect},
                {Instruction::K, instruction_reflect}, {Instruction::L, instruction_reflect},
                {Instruction::M, instruction_reflect}, {Instruction::N, instruction_reflect},
                {Instruction::O, instruction_reflect}, {Instruction::P, instruction_reflect},
                {Instruction::Q, instruction_reflect}, {Instruction::R, instruction_reflect},
                {Instruction::S, instruction_reflect}, {Instruction::T, instruction_reflect},
                {Instruction::U, instruction_reflect}, {Instruction::V, instruction_reflect},
                {Instruction::W, instruction_reflect}, {Instruction::X, instruction_reflect},
                {Instruction::Y, instruction_reflect}, {Instruction::Z, instruction_reflect},
        }};
} // namespace fingerprints::null

#endif // AMANITA_NULL_HPP
