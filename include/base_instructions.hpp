#ifndef AMANITA_BASE_INSTRUCTIONS_HPP
#define AMANITA_BASE_INSTRUCTIONS_HPP

#include "common.hpp"

InstructionAction instruction_space(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_logical_not(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_toggle_stringmode(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_trampoline(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_pop(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_remainder(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_input_integer(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_fetch_character(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_load_semantics(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_unload_semantics(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_multiply(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_add(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_output_character(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_subtract(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_output_integer(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_divide(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_zero(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_one(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_two(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_three(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_four(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_five(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_six(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_seven(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_eight(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_niner(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_duplicate(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_jump_over(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_west(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_execute(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_east(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_away(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_stop(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_turn_left(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_swap(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_turn_right(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_north(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_east_west_if(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_greater_than(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_ten(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_eleven(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_twelve(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_thirteen(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_fourteen(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_push_fifteen(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_get(const Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_high(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_input_file(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_jump_forward(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_iterate(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_low(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_high_low_if(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_clear_stack(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_output_file(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_put(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_quit(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_reflect(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_store_character(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_split(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_stack_under_stack(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_go_south(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_compare(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_absolute_delta(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_get_sysinfo(const Fungespace &, InstructionPointer &ip);
InstructionAction instruction_no_operation(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_begin_block(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_north_south_if(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_end_block(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_input_character(Fungespace &, InstructionPointer &ip);

#endif // AMANITA_BASE_INSTRUCTIONS_HPP
