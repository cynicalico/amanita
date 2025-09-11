#pragma once

#include "action.hpp"
#include "instruction.hpp"
#include "stackstack.hpp"
#include "vec.hpp"

#include <vector>

namespace amanita {
class SemanticStack;
class State;

class InstructionPointer {
public:
    SemanticStack *semantics;
    Instruction curr_ins;
    Instruction prev_ins;

    Vec pos;
    Vec delta;
    bool stringmode;
    Vec storage_offset;
    StackStack *stackstack;

    InstructionPointer();
    ~InstructionPointer() = default;

    InstructionPointer(const InstructionPointer &other) = delete;
    InstructionPointer &operator=(const InstructionPointer &other) = delete;

    InstructionPointer(InstructionPointer &&other) noexcept = delete;
    InstructionPointer &operator=(InstructionPointer &&other) noexcept = delete;

    void perform(Instruction ins, State *state, std::vector<Action> &actions);
    void perform(State *state, std::vector<Action> &actions);

    void push(std::int64_t value);
    std::int64_t peek() const;
    std::int64_t pop();
    Vec pop_vec();
    Vec pop_offset_vec();

    void reflect();
    void go_north();
    void go_south();
    void go_east();
    void go_west();
    void turn_left();
    void turn_right();

    void step();
    void step_wrap(State *state);
    void step_to_next(State *state, Instruction target_ins);
    void step_to_next_instruction(State *state);
    void check_step_to_next_instruction(State *state);

private:
    void step_next_instruction_stringmode_(State *state);
    void step_next_instruction_no_stringmode_(State *state);
};
} // namespace amanita
