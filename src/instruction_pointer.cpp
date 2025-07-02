#include "instruction_pointer.hpp"

#include "instructions.hpp"

std::int64_t next_ip_id() {
    static std::int64_t next_id = 0;
    return ++next_id;
}

InstructionPointer::InstructionPointer(const InstructionPointer &other)
    : id(next_ip_id()), // Redundant, but it makes the intent clearer
      alive(other.alive),
      pos{other.pos[0], other.pos[1]},
      delta{other.delta[0], other.delta[1]},
      stringmode(other.stringmode),
      cache_ins(other.cache_ins),
      stack(other.stack),
      storage_offset{other.storage_offset[0], other.storage_offset[1]},
      instruction_stack(other.instruction_stack) {
}

void InstructionPointer::step() {
    pos[0] += delta[0];
    pos[1] += delta[1];
}

void InstructionPointer::step_wrap(Fungespace &fungespace) {
    step();
    if (!fungespace.in_bounds(pos[0], pos[1])) {
        reflect();
        step();
        while (fungespace.in_bounds(pos[0], pos[1]))
            step();
        reflect();
        step();
    }
}

void InstructionPointer::step_to_next_instruction(Fungespace &fungespace, Cell prev_ins, bool start_skipping) {
    bool skipping = start_skipping;
    do {
        step_wrap(fungespace);
        const auto ins = fungespace.get(pos[0], pos[1]);

        if (stringmode) {
            if (!skipping) {
                // SFML spaces, start skipping any spaces after first
                if (ins == Instruction::Space && prev_ins == Instruction::Space) {
                    skipping = true;
                    continue;
                }
            } else if (ins == Instruction::Space) {
                continue;
            }
        } else if (!skipping) {
            // Start skipping comment
            if (ins == Instruction::JumpOver) {
                skipping = true;
                continue;
            }
            // Ignore spaces
            if (ins == Instruction::Space)
                continue;
        } else {
            // Stop skipping at end of comment
            if (ins == Instruction::JumpOver)
                skipping = false;
            // Need to move at least one more time even if skipping stopped
            continue;
        }

        break;
    } while (true);
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
