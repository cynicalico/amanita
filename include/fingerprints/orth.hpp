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

InstructionAction orth_bitwise_and(Fungespace &, InstructionPointer &ip);
InstructionAction orth_bitwise_or(Fungespace &, InstructionPointer &ip);
InstructionAction orth_bitwise_exor(Fungespace &, InstructionPointer &ip);
InstructionAction orth_change_x(Fungespace &, InstructionPointer &ip);
InstructionAction orth_change_y(Fungespace &, InstructionPointer &ip);
InstructionAction orth_change_dx(Fungespace &, InstructionPointer &ip);
InstructionAction orth_change_dy(Fungespace &, InstructionPointer &ip);
InstructionAction orth_ortho_get(Fungespace &, InstructionPointer &ip);
InstructionAction orth_ortho_put(Fungespace &, InstructionPointer &ip);
InstructionAction orth_ramp_if_zero(Fungespace &, InstructionPointer &ip);
InstructionAction orth_output_string(Fungespace &, InstructionPointer &ip);

const Fingerprint FNG_ORTH{
        .name = "ORTH",
        .id = 0x4f525448,
        .fns = {
                {Instruction::A, orth_bitwise_and},
                {Instruction::O, orth_bitwise_or},
                {Instruction::E, orth_bitwise_exor},
                {Instruction::X, orth_change_x},
                {Instruction::Y, orth_change_y},
                {Instruction::V, orth_change_dx},
                {Instruction::W, orth_change_dy},
                {Instruction::G, orth_ortho_get},
                {Instruction::P, orth_ortho_put},
                {Instruction::Z, orth_ramp_if_zero},
                {Instruction::S, orth_output_string},
        }};

#endif // AMANITA_ORTH_HPP
