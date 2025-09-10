#include "base_semantics.hpp"

#include "fungespace.hpp"
#include "instruction_pointer.hpp"

#include <fmt/format.h>

void amanita::semantic_space(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_logical_not(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_toggle_stringmode(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_trampoline(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->step();
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_pop(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_remainder(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_input_integer(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_fetch_character(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_load_semantics(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_unload_semantics(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_multiply(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_add(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_output_character(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_subtract(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_output_integer(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    const auto value = ip->pop();
    fmt::print("{} ", value);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_divide(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_zero(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(0);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_one(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(1);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_two(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(2);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_three(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(3);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_four(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(4);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_five(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(5);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_six(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(6);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_seven(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(7);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_eight(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(8);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_niner(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->push(9);
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_duplicate(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_jump_over(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_west(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_execute(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_east(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_away(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_stop(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    actions.emplace_back(ActionKill{ip});
}

void amanita::semantic_turn_left(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_swap(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_turn_right(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_north(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_east_west_if(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_greater_than(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_ten(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_eleven(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_twelve(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_thirteen(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_fourteen(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_push_fifteen(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_get(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_high(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_input_file(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_jump_forward(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_iterate(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_low(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_high_low_if(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_clear_stack(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_output_file(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_put(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_quit(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    actions.emplace_back(ActionQuit{});
}

void amanita::semantic_reflect(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_store_character(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_split(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_stack_under_stack(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_go_south(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_compare(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_absolute_delta(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_get_sysinfo(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_no_operation(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_begin_block(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_north_south_if(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_end_block(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}

void amanita::semantic_input_character(State *, InstructionPointer *ip, std::vector<Action> &actions) {
    ip->reflect(); // TODO
    actions.emplace_back(ActionMove{ip});
}
