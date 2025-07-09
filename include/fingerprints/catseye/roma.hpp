#pragma once

/* After successfully loading ROMA, the instructions C, D, I, L, M, V, and X take on new semantics.
 *
 * C pushes 100 onto the stack.
 * D pushes 500 onto the stack.
 * I pushes 1 onto the stack.
 * L pushes 50 onto the stack.
 * M pushes 1000 onto the stack.
 * V pushes 5 onto the stack.
 * X pushes 10 onto the stack.
 *
 * Note that these are just digits, you still have to do the arithmetic yourself. Executing MCMLXXXIV will not leave
 *      1984 on the stack. But executing MCM\-+LXXX+++IV\-++ should.
 */

#include "common.hpp"

namespace fingerprints::roma {
InstructionAction push_100(State &, Fungespace &, InstructionPointer &);
InstructionAction push_500(State &, Fungespace &, InstructionPointer &);
InstructionAction push_1(State &, Fungespace &, InstructionPointer &);
InstructionAction push_50(State &, Fungespace &, InstructionPointer &);
InstructionAction push_1000(State &, Fungespace &, InstructionPointer &);
InstructionAction push_5(State &, Fungespace &, InstructionPointer &);
InstructionAction push_10(State &, Fungespace &, InstructionPointer &);

const static Fingerprint SPEC{
        .name = "ROMA",
        .id = 0x524f4d41,
        .fns = {
                {Instruction::C, push_100},
                {Instruction::D, push_500},
                {Instruction::I, push_1},
                {Instruction::L, push_50},
                {Instruction::M, push_1000},
                {Instruction::V, push_5},
                {Instruction::X, push_10},
        }};
} // namespace fingerprints::roma
