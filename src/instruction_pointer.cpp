#include "instruction_pointer.hpp"

#include "fungespace.hpp"
#include "semantic_stack.hpp"
#include "state.hpp"

#include <fmt/format.h>

amanita::InstructionPointer::InstructionPointer()
    : semantics(new SemanticStack()),
      curr_ins(Instruction::Space),
      prev_ins(Instruction::Space),
      pos(Vec::ZERO),
      delta(Vec::EAST),
      stringmode(false),
      stackstack(new StackStack()) {}

void amanita::InstructionPointer::perform(State *state, std::vector<Action> &actions) {
    semantics->perform(curr_ins, state, this, actions);
}

void amanita::InstructionPointer::push(std::int64_t value) {
    stackstack->push(value);
}

std::int64_t amanita::InstructionPointer::pop() {
    return stackstack->pop();
}

void amanita::InstructionPointer::reflect() {
    delta *= -1;
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
