#include "instruction_pointer.hpp"
#include "fungespace.hpp"

Cell next_ip_id() {
    static Cell next_id = 0;
    return ++next_id;
}

InstructionPointer::InstructionPointer(CliArgs *interpreter)
    : cli_args(interpreter) {}

InstructionPointer::InstructionPointer(const InstructionPointer &other)
    : cli_args(other.cli_args),
      id(next_ip_id()), // Redundant, but it makes the intent clearer
      alive(other.alive),
      pos{other.pos},
      delta{other.delta},
      string_mode(other.string_mode),
      cache_ins(other.cache_ins),
      stack(other.stack),
      storage_offset{other.storage_offset},
      instruction_stack(other.instruction_stack),
      hover_mode(other.hover_mode),
      switch_mode(other.switch_mode),
      relative_mode(other.relative_mode),
      call_stack(other.call_stack) {}

void InstructionPointer::step() { pos += delta; }

void InstructionPointer::step_wrap(const Fungespace &fungespace) {
    step();
    if (!fungespace.in_bounds(pos.x, pos.y)) {
        reflect();
        step();
        while (fungespace.in_bounds(pos.x, pos.y))
            step();
        reflect();
        step();
    }
}

void InstructionPointer::step_to_next_instruction(
        const Fungespace &fungespace, const Cell prev_ins, const bool start_skipping) {
    bool skipping = start_skipping;
    do {
        step_wrap(fungespace);
        const auto ins = fungespace.get(pos.x, pos.y);

        if (string_mode) {
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

void InstructionPointer::go_south() {
    if (hover_mode)
        delta.y += 1;
    else
        delta = SOUTH;
}

void InstructionPointer::go_east() {
    if (hover_mode)
        delta.x += 1;
    else
        delta = EAST;
}

void InstructionPointer::go_north() {
    if (hover_mode)
        delta.y -= 1;
    else
        delta = NORTH;
}

void InstructionPointer::go_west() {
    if (hover_mode)
        delta.x -= 1;
    else
        delta = WEST;
}

void InstructionPointer::turn_left() {
    const auto tmp = delta.x;
    delta.x = delta.y;
    delta.y = -tmp;
}

void InstructionPointer::turn_right() {
    const auto tmp = delta.x;
    delta.x = -delta.y;
    delta.y = tmp;
}

void InstructionPointer::reflect() { delta *= -1; }

void InstructionPointer::save_pos() { saved_pos_ = pos; }

void InstructionPointer::save_delta() { saved_delta_ = delta; }

void InstructionPointer::restore_pos() { pos = saved_pos_; }

void InstructionPointer::restore_delta() { delta = saved_delta_; }

Cell InstructionPointer::pop() { return stack.pop(); }

Vec InstructionPointer::pop_vec() {
    Vec v;
    v.y = stack.pop();
    v.x = stack.pop();
    return v;
}

Vec InstructionPointer::pop_offset_vec() {
    Vec v;
    v.y = stack.pop();
    v.x = stack.pop();
    return v + storage_offset;
}

void InstructionPointer::push(Cell v) { stack.push(v); }

void InstructionPointer::push_vec(Vec v) {
    stack.push(v.x);
    stack.push(v.y);
}

void InstructionPointer::begin_block() {
    stack.begin_block(storage_offset);
    storage_offset = pos + delta;
}

void InstructionPointer::end_block() {
    Vec new_storage_offset;
    if (const auto success = stack.end_block(new_storage_offset); !success)
        reflect();
    else
        storage_offset = new_storage_offset;
}

void InstructionPointer::stack_under_stack() {
    if (!stack.stack_under_stack())
        reflect();
}
