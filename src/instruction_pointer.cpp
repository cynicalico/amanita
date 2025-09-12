#include "instruction_pointer.hpp"

#include "fungespace.hpp"
#include "semantic_stack.hpp"
#include "state.hpp"

#include <fmt/format.h>

amanita::InstructionPointer::InstructionPointer()
    : semantics(new SemanticStack()),
      curr_ins(Instruction::Space),
      prev_ins(Instruction::Space),
      alive(true),
      pos(Vec::ZERO),
      delta(Vec::EAST),
      stringmode(false),
      storage_offset(Vec::ZERO),
      stackstack(new StackStack()) {}

void amanita::InstructionPointer::perform(Instruction ins, State *state, std::vector<Action> &actions) {
    semantics->perform(ins, state, this, actions);
}

void amanita::InstructionPointer::perform(State *state, std::vector<Action> &actions) {
    perform(curr_ins, state, actions);
}

void amanita::InstructionPointer::stack_clear() {
    stackstack->clear();
}

void amanita::InstructionPointer::stack_push(std::int64_t value) {
    stackstack->push(value);
}

std::int64_t amanita::InstructionPointer::stack_peek() const {
    return stackstack->peek();
}

std::int64_t amanita::InstructionPointer::stack_pop() {
    return stackstack->pop();
}

amanita::Vec amanita::InstructionPointer::stack_pop_vec() {
    const auto y = stack_pop();
    const auto x = stack_pop();
    return {x, y};
}

amanita::Vec amanita::InstructionPointer::stack_pop_offset_vec() {
    return stack_pop_vec() + storage_offset;
}

void amanita::InstructionPointer::reflect() {
    delta *= -1;
}

void amanita::InstructionPointer::go_north() {
    delta = Vec::NORTH;
}

void amanita::InstructionPointer::go_south() {
    delta = Vec::SOUTH;
}

void amanita::InstructionPointer::go_east() {
    delta = Vec::EAST;
}

void amanita::InstructionPointer::go_west() {
    delta = Vec::WEST;
}

void amanita::InstructionPointer::turn_left() {
    delta = {delta.y, -delta.x};
}

void amanita::InstructionPointer::turn_right() {
    delta = {-delta.y, delta.x};
}

void amanita::InstructionPointer::step() {
    pos += delta;
}

void amanita::InstructionPointer::step_wrap(State *state) {
    step();
    if (!state->fungespace->is_in_bounds(pos)) {
        reflect();
        step();
        while (state->fungespace->is_in_bounds(pos))
            step();
        reflect();
        step();
    }
}

void amanita::InstructionPointer::step_to_next(State *state, const Instruction target_ins) {
    do {
        step_wrap(state);
        curr_ins = state->fungespace->get_ins(pos);
    } while (curr_ins != target_ins);
}

void amanita::InstructionPointer::step_to_next_instruction(State *state) {
    if (stringmode)
        step_next_instruction_stringmode_(state);
    else
        step_next_instruction_no_stringmode_(state);
}

void amanita::InstructionPointer::check_step_to_next_instruction(State *state) {
    // On file load, an IP may not be on top of a valid instruction.
    // With multiple IPs, the instruction an IP was going to execute could also be replaced with `;` or ` `.
    // In either case, we need to step to something valid before we execute anything.

    curr_ins = state->fungespace->get_ins(pos);
    if (!stringmode) {
        switch (curr_ins) {
        case Instruction::JumpOver: step_to_next(state, Instruction::JumpOver);
        case Instruction::Space: step_to_next_instruction(state); break;
        default:;
        }
    }
}

void amanita::InstructionPointer::step_next_instruction_stringmode_(State *state) {
    do {
        step_wrap(state);
        curr_ins = state->fungespace->get_ins(pos);
    } while (curr_ins == Instruction::Space && prev_ins == Instruction::Space);
}

void amanita::InstructionPointer::step_next_instruction_no_stringmode_(State *state) {
    do {
        step_wrap(state);
        curr_ins = state->fungespace->get_ins(pos);
        if (curr_ins == Instruction::JumpOver)
            step_to_next(state, Instruction::JumpOver);
    } while (curr_ins == Instruction::Space || curr_ins == Instruction::JumpOver);
}
