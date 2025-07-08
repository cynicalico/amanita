#ifndef AMANITA_ORTH_HPP
#define AMANITA_ORTH_HPP

/* The ORTH fingerprint is designed to ease transition between the Orthogonal programming language and Befunge-98 (or
 * higher dimension Funges.) Even if transition from Orthogonal is not an issue, the ORTH library contains some
 * potentially interesting instructions not in standard Funge-98.
 *
 * After successfully loading ORTH, the instructions A, E, G, O, P, S, V, W, X, Y, and Z take on new semantics. The
 * following table, which can be used to translate Orthogonal to Funge-98 and back, includes which Orthogonal
 * instructions they emulate:
 *
 *     Funge   Orthogonal  Semantic
 *
 *     +       +           add
 *     *       *           multiply
 *     -       -           subtract
 *     /       /           divide
 *     %       %           modulo (positive values only)
 * >>> A       &           bitwise AND
 * >>> O       |           bitwise OR
 * >>> E       ^           bitwise EXOR
 *     !       !           logical negate
 *     \       ~           swap
 *     :       @           duplicate
 *     $       $           pop
 *     <       L           go west
 *     >       H           go east
 *     ^       K           go north
 *     v       J           go south
 *     ]       cw          rotate right
 *     [       ccw         rotate left
 *     r       rev         reverse
 * >>> X       x           change x
 * >>> Y       y           change y
 * >>> V       dx          change dx
 * >>> W       dy          change dy
 * >>> G       =           ortho get
 * >>> P       #           ortho put
 * >>> Z       ?           ramp if zero
 *     ,       c           output character
 * >>> S       s           output string
 *     .       d           output decimal
 *     z       nop         no operation
 *     q       ret         quit
 */

#include "common.hpp"

namespace fingerprints::orth {
InstructionAction bitwise_and(Fungespace &, InstructionPointer &ip);
InstructionAction bitwise_or(Fungespace &, InstructionPointer &ip);
InstructionAction bitwise_exor(Fungespace &, InstructionPointer &ip);
InstructionAction change_x(Fungespace &, InstructionPointer &ip);
InstructionAction change_y(Fungespace &, InstructionPointer &ip);
InstructionAction change_dx(Fungespace &, InstructionPointer &ip);
InstructionAction change_dy(Fungespace &, InstructionPointer &ip);
InstructionAction ortho_get(Fungespace &, InstructionPointer &ip);
InstructionAction ortho_put(Fungespace &, InstructionPointer &ip);
InstructionAction ramp_if_zero(Fungespace &, InstructionPointer &ip);
InstructionAction output_string(Fungespace &, InstructionPointer &ip);

const Fingerprint SPEC{
        .name = "ORTH",
        .id = 0x4f525448,
        .fns = {
                {Instruction::A, bitwise_and},
                {Instruction::O, bitwise_or},
                {Instruction::E, bitwise_exor},
                {Instruction::X, change_x},
                {Instruction::Y, change_y},
                {Instruction::V, change_dx},
                {Instruction::W, change_dy},
                {Instruction::G, ortho_get},
                {Instruction::P, ortho_put},
                {Instruction::Z, ramp_if_zero},
                {Instruction::S, output_string},
        }};
} // namespace fingerprints::orth

#endif // AMANITA_ORTH_HPP
