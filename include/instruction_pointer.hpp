#pragma once

#include "action.hpp"
#include "instruction.hpp"
#include "semantic_stack.hpp"
#include "stackstack.hpp"
#include "vec.hpp"

#include <memory>
#include <vector>

namespace amanita {
std::int64_t next_ip_id();

class InstructionPointer {
public:
    std::unique_ptr<SemanticStack> semantics;
    Instruction curr_ins;
    Instruction prev_ins;

    std::int64_t id{next_ip_id()};
    bool alive;
    Vec pos;
    Vec delta;
    bool stringmode;
    Vec storage_offset;
    std::unique_ptr<StackStack> stackstack;

    InstructionPointer();

    InstructionPointer(const InstructionPointer &other);
    InstructionPointer &operator=(const InstructionPointer &other) = delete;

    InstructionPointer(InstructionPointer &&other) noexcept = default;
    InstructionPointer &operator=(InstructionPointer &&other) noexcept = default;

    void perform(Instruction ins, State *state, std::vector<Action> &actions);
    void perform(State *state, std::vector<Action> &actions);

    void stack_clear();
    void stack_push(std::int64_t value);
    std::int64_t stack_peek() const;
    std::int64_t stack_pop();
    Vec stack_pop_vec();
    Vec stack_pop_offset_vec();
    void stack_begin_block();
    void stack_end_block();
    void stack_stack_under_stack();
    std::size_t stack_count() const;
    std::vector<std::size_t> stack_sizes() const;
    std::int64_t stack_pick(std::size_t i) const;

    void reflect();
    void go_north();
    void go_south();
    void go_east();
    void go_west();
    void turn_left();
    void turn_right();

    bool load_fingerprint(std::int64_t fingerprint);
    bool unload_fingerprint(std::int64_t fingerprint);

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
