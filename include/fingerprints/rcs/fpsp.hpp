#ifndef AMANITA_FPSP_HPP
#define AMANITA_FPSP_HPP

/*
 * A	(a b -- n)	    Add two single precision fp numbers
 * B	(n -- n)	    Sin of single precision fp number
 * C	(n -- n)	    Cosin of single precision fp number
 * D	(a b -- n)	    Divide two single precision fp numbers
 * E	(n -- n)	    Arcsin of single precision fp number
 * F	(n -- n)	    Convert integer to floating point
 * G	(n -- n)	    Arctangent of single precision fp number
 * H	(n -- n)	    Arccosin of single precision fp number
 * I	(n -- n)	    Convert floating point to integer
 * K	(n -- n)	    Natural logarithm of single precision fp number
 * L	(n -- n)	    Base 10 logarithm of single precision fp number
 * M	(a b -- n)	    Multiply two single precision fp numbers
 * N	(n -- n)	    Negate single precision fp number
 * P	(n -- )	        Print a floating point number
 * Q	(n -- n)	    Single precision square root
 * R	(0gnirts -- n)	Convert ascii number to floating point
 * S	(a b -- n)	    Subtract two single precision fp numbers
 * T	(n -- n)	    Tangent of single precision fp number
 * V	(n -- n)	    Absolute value of single precision fp number
 * X	(n -- n)	    Exponential of single precision fp number (e**n)
 * Y	(x y -- n)	    Raise x to the power of y
 *
 *     Trig functions work in radians
 */

#include "common.hpp"

namespace fingerprints::fpsp {
InstructionAction add(State &, Fungespace &, InstructionPointer &);
InstructionAction sin(State &, Fungespace &, InstructionPointer &);
InstructionAction cos(State &, Fungespace &, InstructionPointer &);
InstructionAction div(State &, Fungespace &, InstructionPointer &);
InstructionAction asin(State &, Fungespace &, InstructionPointer &);
InstructionAction itof(State &, Fungespace &, InstructionPointer &);
InstructionAction atan(State &, Fungespace &, InstructionPointer &);
InstructionAction acos(State &, Fungespace &, InstructionPointer &);
InstructionAction ftoi(State &, Fungespace &, InstructionPointer &);
InstructionAction ln(State &, Fungespace &, InstructionPointer &);
InstructionAction log10(State &, Fungespace &, InstructionPointer &);
InstructionAction mul(State &, Fungespace &, InstructionPointer &);
InstructionAction neg(State &, Fungespace &, InstructionPointer &);
InstructionAction print(State &, Fungespace &, InstructionPointer &);
InstructionAction sqrt(State &, Fungespace &, InstructionPointer &);
InstructionAction parse(State &, Fungespace &, InstructionPointer &);
InstructionAction sub(State &, Fungespace &, InstructionPointer &);
InstructionAction tan(State &, Fungespace &, InstructionPointer &);
InstructionAction abs(State &, Fungespace &, InstructionPointer &);
InstructionAction exp(State &, Fungespace &, InstructionPointer &);
InstructionAction pow(State &, Fungespace &, InstructionPointer &);

const Fingerprint SPEC{
        .name = "FPSP",
        .id = 0x46505350,
        .fns = {
                {Instruction::A, add},  {Instruction::B, sin},   {Instruction::C, cos},   {Instruction::D, div},
                {Instruction::E, asin}, {Instruction::F, itof},  {Instruction::G, atan},  {Instruction::H, acos},
                {Instruction::I, ftoi}, {Instruction::K, ln},    {Instruction::L, log10}, {Instruction::M, mul},
                {Instruction::N, neg},  {Instruction::P, print}, {Instruction::Q, sqrt},  {Instruction::R, parse},
                {Instruction::S, sub},  {Instruction::T, tan},   {Instruction::V, abs},   {Instruction::X, exp},
                {Instruction::Y, pow},
        }};
} // namespace fingerprints::fpsp

#endif // AMANITA_FPSP_HPP
