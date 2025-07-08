#ifndef AMANITA_BASE_INSTRUCTIONS_HPP
#define AMANITA_BASE_INSTRUCTIONS_HPP

#include "common.hpp"

InstructionAction instruction_space(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_logical_not(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_toggle_stringmode(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_trampoline(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_pop(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_remainder(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_input_integer(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_fetch_character(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_load_semantics(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_unload_semantics(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_multiply(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_add(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_output_character(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_subtract(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_output_integer(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_divide(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_zero(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_one(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_two(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_three(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_four(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_five(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_six(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_seven(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_eight(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_niner(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_duplicate(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_jump_over(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_go_west(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_execute(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_go_east(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_go_away(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_stop(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_turn_left(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_swap(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_turn_right(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_go_north(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_east_west_if(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_greater_than(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_ten(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_eleven(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_twelve(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_thirteen(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_fourteen(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_push_fifteen(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_get(State &, const Fungespace &, InstructionPointer &);
InstructionAction instruction_go_high(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_input_file(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_jump_forward(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_iterate(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_go_low(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_high_low_if(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_clear_stack(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_output_file(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_put(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_quit(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_reflect(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_store_character(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_split(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_stack_under_stack(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_go_south(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_compare(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_absolute_delta(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_get_sysinfo(State &, const Fungespace &, InstructionPointer &);
InstructionAction instruction_no_operation(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_begin_block(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_north_south_if(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_end_block(State &, Fungespace &, InstructionPointer &);
InstructionAction instruction_input_character(State &, Fungespace &, InstructionPointer &);

#endif // AMANITA_BASE_INSTRUCTIONS_HPP
