#ifndef AMANITA_FIXP_HPP
#define AMANITA_FIXP_HPP

/*
 * A	(a b -- a and b)	And
 * B	(n -- arccos(b))	Find arccosin of tos
 * C	(n -- cos(b))	    Find cosin of tos
 * D	(n -- rnd(n))	    RanDom number
 * I	(n -- sin(b))	    Find sin of tos
 * J	(n -- arcsin(b))	Find arcsin of tos
 * N	(a -- 0-a)	        Negate
 * O	(a b -- a or b)	    Or
 * P	(a -- a*pi)     	Multiply by pi
 * Q	(a -- sqrt(a))	    Square root
 * R	(a b -- a**b)	    Raise a to the power of b
 * S	(n -- n)	        Replace tos with sign of tos
 * T	(n -- tan(b))	    Find tangent of tos
 * U	(n -- arctan(b)	    Find arctangent of tos
 * V	(n -- n)	        Absolute value of tos
 * X	(a b -- a xor b)    Xor
 *
 *      The functions C,I,T,B,J,U expect their arguments times 10000, for example: 45 should be passed as 450000. The
 * results will also be multiplied by 10000, thereby giving 4 digits of decimal precision.
 *
 *      Trigonometric functions work in degrees. not radians.
 */

#include "common.hpp"

namespace fingerprints::fixp {
InstructionAction and_(Fungespace &, InstructionPointer &ip);
InstructionAction acos(Fungespace &, InstructionPointer &ip);
InstructionAction cos(Fungespace &, InstructionPointer &ip);
InstructionAction rnd(Fungespace &, InstructionPointer &ip);
InstructionAction sin(Fungespace &, InstructionPointer &ip);
InstructionAction asin(Fungespace &, InstructionPointer &ip);
InstructionAction neg(Fungespace &, InstructionPointer &ip);
InstructionAction or_(Fungespace &, InstructionPointer &ip);
InstructionAction mul_pi(Fungespace &, InstructionPointer &ip);
InstructionAction sqrt(Fungespace &, InstructionPointer &ip);
InstructionAction pow(Fungespace &, InstructionPointer &ip);
InstructionAction sign(Fungespace &, InstructionPointer &ip);
InstructionAction tan(Fungespace &, InstructionPointer &ip);
InstructionAction atan(Fungespace &, InstructionPointer &ip);
InstructionAction abs(Fungespace &, InstructionPointer &ip);
InstructionAction xor_(Fungespace &, InstructionPointer &ip);

const Fingerprint SPEC{
        .id = 0x46495850,
        .fns = {
                {Instruction::A, and_},
                {Instruction::B, acos},
                {Instruction::C, cos},
                {Instruction::D, rnd},
                {Instruction::I, sin},
                {Instruction::J, asin},
                {Instruction::N, neg},
                {Instruction::O, or_},
                {Instruction::P, mul_pi},
                {Instruction::Q, sqrt},
                {Instruction::R, pow},
                {Instruction::S, sign},
                {Instruction::T, tan},
                {Instruction::U, atan},
                {Instruction::V, abs},
                {Instruction::X, xor_},
        }};
} // namespace fingerprints::fixp

#endif // AMANITA_FIXP_HPP
