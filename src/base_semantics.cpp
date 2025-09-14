#include "base_semantics.hpp"

#include "fungespace.hpp"
#include "instruction_pointer.hpp"

#include <fmt/format.h>

#include <utility>

void amanita::semantic_space(State *, InstructionPointer *, std::vector<Action> &) {
    std::unreachable();
}

void amanita::semantic_logical_not(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto v = ip->stack_pop();
    ip->stack_push(v == 0 ? 1 : 0);
}

void amanita::semantic_toggle_stringmode(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stringmode = !ip->stringmode;
}

void amanita::semantic_trampoline(State *state, InstructionPointer *ip, std::vector<Action> &) {
    ip->step_wrap(state);
}

void amanita::semantic_pop(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_pop();
}

void amanita::semantic_remainder(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(b == 0 ? 0 : a % b);
}

void amanita::semantic_input_integer(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_fetch_character(State *state, InstructionPointer *ip, std::vector<Action> &) {
    ip->step_wrap(state);
    ip->stack_push(state->fungespace->get(ip->pos));
}

void amanita::semantic_load_semantics(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_unload_semantics(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_multiply(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(a * b);
}

void amanita::semantic_add(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(a + b);
}

void amanita::semantic_output_character(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto v = ip->stack_pop();
    fmt::print("{}", static_cast<char>(v & 0xff));
}

void amanita::semantic_subtract(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(a - b);
}

void amanita::semantic_output_integer(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto v = ip->stack_pop();
    fmt::print("{} ", v);
}

void amanita::semantic_divide(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(b == 0 ? 0 : a / b);
}

void amanita::semantic_push_zero(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(0);
}

void amanita::semantic_push_one(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(1);
}

void amanita::semantic_push_two(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(2);
}

void amanita::semantic_push_three(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(3);
}

void amanita::semantic_push_four(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(4);
}

void amanita::semantic_push_five(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(5);
}

void amanita::semantic_push_six(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(6);
}

void amanita::semantic_push_seven(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(7);
}

void amanita::semantic_push_eight(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(8);
}

void amanita::semantic_push_niner(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(9);
}

void amanita::semantic_duplicate(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(ip->stack_peek());
}

void amanita::semantic_jump_over(State *, InstructionPointer *ip, std::vector<Action> &) {
    std::unreachable();
}

void amanita::semantic_go_west(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->go_west();
}

void amanita::semantic_execute(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_go_east(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->go_east();
}

void amanita::semantic_go_away(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_stop(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->alive = false;
}

void amanita::semantic_turn_left(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->turn_left();
}

void amanita::semantic_swap(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(b);
    ip->stack_push(a);
}

void amanita::semantic_turn_right(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->turn_right();
}

void amanita::semantic_go_north(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->go_north();
}

void amanita::semantic_east_west_if(State *, InstructionPointer *ip, std::vector<Action> &) {
    if (const auto v = ip->stack_pop(); v == 0)
        ip->go_east();
    else
        ip->go_west();
}

void amanita::semantic_greater_than(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(a > b ? 1 : 0);
}

void amanita::semantic_push_ten(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(10);
}

void amanita::semantic_push_eleven(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(11);
}

void amanita::semantic_push_twelve(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(12);
}

void amanita::semantic_push_thirteen(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(13);
}

void amanita::semantic_push_fourteen(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(14);
}

void amanita::semantic_push_fifteen(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(15);
}

void amanita::semantic_get(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto vec = ip->stack_pop_offset_vec();
    ip->stack_push(state->fungespace->get(vec));
}

void amanita::semantic_go_high(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // not supported in Befunge mode
}

void amanita::semantic_input_file(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_jump_forward(State *state, InstructionPointer *ip, std::vector<Action> &) {
    auto n = ip->stack_pop();

    const auto saved_delta = ip->delta;

    if (n < 0) {
        ip->reflect();
        n = std::abs(n);
    }
    for (std::int64_t i = 0; i < n; ++i)
        ip->step_wrap(state);

    ip->delta = saved_delta;
}

void amanita::semantic_iterate(State *state, InstructionPointer *ip, std::vector<Action> &actions) {
    const auto n = ip->stack_pop();

    const auto saved_pos = ip->pos;
    ip->step_to_next_instruction(state);

    if (n == 0)
        return;

    const auto ins = state->fungespace->get_ins(ip->pos);
    ip->pos = saved_pos;

    for (std::int64_t i = 0; i < n; ++i)
        ip->perform(ins, state, actions);
}

void amanita::semantic_go_low(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // not supported in Befunge mode
}

void amanita::semantic_high_low_if(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // not supported in Befunge mode
}

void amanita::semantic_clear_stack(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_clear();
}

void amanita::semantic_output_file(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_put(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto vec = ip->stack_pop_offset_vec();
    const auto v = ip->stack_pop();
    state->fungespace->put(vec, v);
}

void amanita::semantic_quit(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto exit_code = ip->stack_pop();
    state->exit_code = static_cast<int>(exit_code);
    state->status = Status::Stopped;
}

void amanita::semantic_reflect(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect();
}

void amanita::semantic_store_character(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto value = ip->stack_pop();
    ip->step_wrap(state);
    state->fungespace->put(ip->pos, value);
}

void amanita::semantic_split(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_stack_under_stack(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_stack_under_stack();
}

void amanita::semantic_go_south(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->go_south();
}

void amanita::semantic_compare(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    if (a > b)
        ip->turn_right();
    else if (a < b)
        ip->turn_left();
}

void amanita::semantic_absolute_delta(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->delta = ip->stack_pop_vec();
}

void amanita::semantic_get_sysinfo(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}

void amanita::semantic_no_operation(State *, InstructionPointer *ip, std::vector<Action> &) {}

void amanita::semantic_begin_block(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_begin_block();
}

void amanita::semantic_north_south_if(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto v = ip->stack_pop();
    if (v == 0)
        ip->go_south();
    else
        ip->go_north();
}

void amanita::semantic_end_block(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_end_block();
}

void amanita::semantic_input_character(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->reflect(); // TODO
}
