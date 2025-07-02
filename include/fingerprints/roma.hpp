#ifndef AMANITA_ROMA_HPP
#define AMANITA_ROMA_HPP

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

InstructionAction roma_c(Fungespace &, InstructionPointer &ip);

InstructionAction roma_d(Fungespace &, InstructionPointer &ip);

InstructionAction roma_i(Fungespace &, InstructionPointer &ip);

InstructionAction roma_l(Fungespace &, InstructionPointer &ip);

InstructionAction roma_m(Fungespace &, InstructionPointer &ip);

InstructionAction roma_v(Fungespace &, InstructionPointer &ip);

InstructionAction roma_x(Fungespace &, InstructionPointer &ip);

const static Fingerprint FNG_ROMA{
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
