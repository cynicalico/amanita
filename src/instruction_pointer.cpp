#include "instruction_pointer.hpp"

void InstructionPointer::step() {
    pos[0] += delta[0];
    pos[1] += delta[1];
}

void InstructionPointer::reflect() {
    delta[0] = -delta[0];
    delta[1] = -delta[1];
}

void InstructionPointer::begin_block() {
    stack.begin_block(storage_offset);
    storage_offset[0] = pos[0] + delta[0];
    storage_offset[1] = pos[1] + delta[1];
}

void InstructionPointer::end_block() {
    std::int64_t new_storage_offset[2];
    const auto success = stack.end_block(new_storage_offset);
    if (!success) {
        reflect();
    } else {
        storage_offset[0] = new_storage_offset[0];
        storage_offset[1] = new_storage_offset[1];
    }
}

void InstructionPointer::stack_under_stack() {
    if (!stack.stack_under_stack())
        reflect();
}
