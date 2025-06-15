#include "instruction_pointer.hpp"

void InstructionPointer::step() {
    pos[0] += delta[0];
    pos[1] += delta[1];
}

void InstructionPointer::reflect() {
    delta[0] = -delta[0];
    delta[1] = -delta[1];
}
