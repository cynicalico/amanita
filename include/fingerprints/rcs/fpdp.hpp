#ifndef AMANITA_FPDP_HPP
#define AMANITA_FPDP_HPP

/*
 * A	(a b -- n)	    Add two double precision fp numbers
 * B	(n -- n)	    Sin of double precision fp number
 * C	(n -- n)	    Cosin of double precision fp number
 * D	(a b -- n)	    Divide two double precision fp numbers
 * E	(n -- n)	    Arcsin of double precision fp number
 * F	(n -- n)	    Convert integer to floating point
 * G	(n -- n)	    Arctangent of double precision fp number
 * H	(n -- n)	    Arccosin of double precision fp number
 * I	(n -- n)	    Convert floating point to integer
 * K	(n -- n)	    Natural logarithm of double precision fp number
 * L	(n -- n)	    Base 10 logarithm of double precision fp number
 * M	(a b -- n)	    Multiply two double precision fp numbers
 * N	(n -- n)	    Negate double precision fp number
 * P	(n -- )	        Print a floating point number
 * Q	(n -- n)	    Double precision square root
 * R	(0gnirts -- n)	Convert ascii number to floating point
 * S	(a b -- n)	    Subtract two double precision fp numbers
 * T	(n -- n)	    Tangent of double precision fp number
 * V	(n -- n)	    Absolute value of double precision fp number
 * X	(n -- n)	    Exponential of double precision fp number (e**n)
 * Y	(x y -- n)	    Raise x to the power of y
 */

#include "common.hpp"

namespace fpdp {
InstructionAction add(Fungespace &, InstructionPointer &ip);
InstructionAction sin(Fungespace &, InstructionPointer &ip);
InstructionAction cos(Fungespace &, InstructionPointer &ip);
InstructionAction div(Fungespace &, InstructionPointer &ip);
InstructionAction asin(Fungespace &, InstructionPointer &ip);
InstructionAction itof(Fungespace &, InstructionPointer &ip);
InstructionAction atan(Fungespace &, InstructionPointer &ip);
InstructionAction acos(Fungespace &, InstructionPointer &ip);
InstructionAction ftoi(Fungespace &, InstructionPointer &ip);
InstructionAction ln(Fungespace &, InstructionPointer &ip);
InstructionAction log10(Fungespace &, InstructionPointer &ip);
InstructionAction mul(Fungespace &, InstructionPointer &ip);
InstructionAction neg(Fungespace &, InstructionPointer &ip);
InstructionAction print(Fungespace &, InstructionPointer &ip);
InstructionAction sqrt(Fungespace &, InstructionPointer &ip);
InstructionAction parse(Fungespace &, InstructionPointer &ip);
InstructionAction sub(Fungespace &, InstructionPointer &ip);
InstructionAction tan(Fungespace &, InstructionPointer &ip);
InstructionAction abs(Fungespace &, InstructionPointer &ip);
InstructionAction exp(Fungespace &, InstructionPointer &ip);
InstructionAction pow(Fungespace &, InstructionPointer &ip);

const Fingerprint FINGERPRINT{
        .id = 0x46504450,
        .fns = {
                {Instruction::A, add},  {Instruction::B, sin},   {Instruction::C, cos},   {Instruction::D, div},
                {Instruction::E, asin}, {Instruction::F, itof},  {Instruction::G, atan},  {Instruction::H, acos},
                {Instruction::I, ftoi}, {Instruction::K, ln},    {Instruction::L, log10}, {Instruction::M, mul},
                {Instruction::N, neg},  {Instruction::P, print}, {Instruction::Q, sqrt},  {Instruction::R, parse},
                {Instruction::S, sub},  {Instruction::T, tan},   {Instruction::V, abs},   {Instruction::X, exp},
                {Instruction::Y, pow},
        }};
} // namespace fpdp

#endif // AMANITA_FPDP_HPP
