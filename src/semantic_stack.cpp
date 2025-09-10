#include "semantic_stack.hpp"

#include "base_semantics.hpp"
#include "instruction_pointer.hpp"

#include <fmt/format.h>

amanita::SemanticStack::SemanticStack() {
    populate_default_fns_();
}

void amanita::SemanticStack::perform(
        Instruction ins, State *state, InstructionPointer *ip, std::vector<Action> &actions) {
    if (ip->stringmode) {
        if (ins != Instruction::ToggleStringmode) {
            ip->push(static_cast<std::int64_t>(ins));
            actions.emplace_back(ActionMove{ip});
            return;
        }
    }

    if (ins < Instruction::Space || ins > Instruction::InputCharacter) {
        fmt::println(stderr, "Unknown instruction: {}, reflecting", static_cast<std::int64_t>(ins));
        semantics_[static_cast<std::size_t>(Instruction::Reflect)].back()(state, ip, actions);
        return;
    }

    if (const auto stack = semantics_[static_cast<std::size_t>(ins)]; stack.empty())
        semantics_[static_cast<std::size_t>(Instruction::Reflect)].back()(state, ip, actions);
    else
        stack.back()(state, ip, actions);
}

void amanita::SemanticStack::populate_default_fns_() {
    semantics_.resize(static_cast<std::size_t>(Instruction::InputCharacter) + 1);
    semantics_[static_cast<std::size_t>(Instruction::Space)].emplace_back(semantic_space);
    semantics_[static_cast<std::size_t>(Instruction::LogicalNot)].emplace_back(semantic_logical_not);
    semantics_[static_cast<std::size_t>(Instruction::ToggleStringmode)].emplace_back(semantic_toggle_stringmode);
    semantics_[static_cast<std::size_t>(Instruction::Trampoline)].emplace_back(semantic_trampoline);
    semantics_[static_cast<std::size_t>(Instruction::Pop)].emplace_back(semantic_pop);
    semantics_[static_cast<std::size_t>(Instruction::Remainder)].emplace_back(semantic_remainder);
    semantics_[static_cast<std::size_t>(Instruction::InputInteger)].emplace_back(semantic_input_integer);
    semantics_[static_cast<std::size_t>(Instruction::FetchCharacter)].emplace_back(semantic_fetch_character);
    semantics_[static_cast<std::size_t>(Instruction::LoadSemantics)].emplace_back(semantic_load_semantics);
    semantics_[static_cast<std::size_t>(Instruction::UnloadSemantics)].emplace_back(semantic_unload_semantics);
    semantics_[static_cast<std::size_t>(Instruction::Multiply)].emplace_back(semantic_multiply);
    semantics_[static_cast<std::size_t>(Instruction::Add)].emplace_back(semantic_add);
    semantics_[static_cast<std::size_t>(Instruction::OutputCharacter)].emplace_back(semantic_output_character);
    semantics_[static_cast<std::size_t>(Instruction::Subtract)].emplace_back(semantic_subtract);
    semantics_[static_cast<std::size_t>(Instruction::OutputInteger)].emplace_back(semantic_output_integer);
    semantics_[static_cast<std::size_t>(Instruction::Divide)].emplace_back(semantic_divide);
    semantics_[static_cast<std::size_t>(Instruction::PushZero)].emplace_back(semantic_push_zero);
    semantics_[static_cast<std::size_t>(Instruction::PushOne)].emplace_back(semantic_push_one);
    semantics_[static_cast<std::size_t>(Instruction::PushTwo)].emplace_back(semantic_push_two);
    semantics_[static_cast<std::size_t>(Instruction::PushThree)].emplace_back(semantic_push_three);
    semantics_[static_cast<std::size_t>(Instruction::PushFour)].emplace_back(semantic_push_four);
    semantics_[static_cast<std::size_t>(Instruction::PushFive)].emplace_back(semantic_push_five);
    semantics_[static_cast<std::size_t>(Instruction::PushSix)].emplace_back(semantic_push_six);
    semantics_[static_cast<std::size_t>(Instruction::PushSeven)].emplace_back(semantic_push_seven);
    semantics_[static_cast<std::size_t>(Instruction::PushEight)].emplace_back(semantic_push_eight);
    semantics_[static_cast<std::size_t>(Instruction::PushNiner)].emplace_back(semantic_push_niner);
    semantics_[static_cast<std::size_t>(Instruction::Duplicate)].emplace_back(semantic_duplicate);
    semantics_[static_cast<std::size_t>(Instruction::JumpOver)].emplace_back(semantic_jump_over);
    semantics_[static_cast<std::size_t>(Instruction::GoWest)].emplace_back(semantic_go_west);
    semantics_[static_cast<std::size_t>(Instruction::Execute)].emplace_back(semantic_execute);
    semantics_[static_cast<std::size_t>(Instruction::GoEast)].emplace_back(semantic_go_east);
    semantics_[static_cast<std::size_t>(Instruction::GoAway)].emplace_back(semantic_go_away);
    semantics_[static_cast<std::size_t>(Instruction::Stop)].emplace_back(semantic_stop);
    semantics_[static_cast<std::size_t>(Instruction::TurnLeft)].emplace_back(semantic_turn_left);
    semantics_[static_cast<std::size_t>(Instruction::Swap)].emplace_back(semantic_swap);
    semantics_[static_cast<std::size_t>(Instruction::TurnRight)].emplace_back(semantic_turn_right);
    semantics_[static_cast<std::size_t>(Instruction::GoNorth)].emplace_back(semantic_go_north);
    semantics_[static_cast<std::size_t>(Instruction::EastWestIf)].emplace_back(semantic_east_west_if);
    semantics_[static_cast<std::size_t>(Instruction::GreaterThan)].emplace_back(semantic_greater_than);
    semantics_[static_cast<std::size_t>(Instruction::PushTen)].emplace_back(semantic_push_ten);
    semantics_[static_cast<std::size_t>(Instruction::PushEleven)].emplace_back(semantic_push_eleven);
    semantics_[static_cast<std::size_t>(Instruction::PushTwelve)].emplace_back(semantic_push_twelve);
    semantics_[static_cast<std::size_t>(Instruction::PushThirteen)].emplace_back(semantic_push_thirteen);
    semantics_[static_cast<std::size_t>(Instruction::PushFourteen)].emplace_back(semantic_push_fourteen);
    semantics_[static_cast<std::size_t>(Instruction::PushFifteen)].emplace_back(semantic_push_fifteen);
    semantics_[static_cast<std::size_t>(Instruction::Get)].emplace_back(semantic_get);
    semantics_[static_cast<std::size_t>(Instruction::GoHigh)].emplace_back(semantic_go_high);
    semantics_[static_cast<std::size_t>(Instruction::InputFile)].emplace_back(semantic_input_file);
    semantics_[static_cast<std::size_t>(Instruction::JumpForward)].emplace_back(semantic_jump_forward);
    semantics_[static_cast<std::size_t>(Instruction::Iterate)].emplace_back(semantic_iterate);
    semantics_[static_cast<std::size_t>(Instruction::GoLow)].emplace_back(semantic_go_low);
    semantics_[static_cast<std::size_t>(Instruction::HighLowIf)].emplace_back(semantic_high_low_if);
    semantics_[static_cast<std::size_t>(Instruction::ClearStack)].emplace_back(semantic_clear_stack);
    semantics_[static_cast<std::size_t>(Instruction::OutputFile)].emplace_back(semantic_output_file);
    semantics_[static_cast<std::size_t>(Instruction::Put)].emplace_back(semantic_put);
    semantics_[static_cast<std::size_t>(Instruction::Quit)].emplace_back(semantic_quit);
    semantics_[static_cast<std::size_t>(Instruction::Reflect)].emplace_back(semantic_reflect);
    semantics_[static_cast<std::size_t>(Instruction::StoreCharacter)].emplace_back(semantic_store_character);
    semantics_[static_cast<std::size_t>(Instruction::Split)].emplace_back(semantic_split);
    semantics_[static_cast<std::size_t>(Instruction::StackUnderStack)].emplace_back(semantic_stack_under_stack);
    semantics_[static_cast<std::size_t>(Instruction::GoSouth)].emplace_back(semantic_go_south);
    semantics_[static_cast<std::size_t>(Instruction::Compare)].emplace_back(semantic_compare);
    semantics_[static_cast<std::size_t>(Instruction::AbsoluteDelta)].emplace_back(semantic_absolute_delta);
    semantics_[static_cast<std::size_t>(Instruction::GetSysinfo)].emplace_back(semantic_get_sysinfo);
    semantics_[static_cast<std::size_t>(Instruction::NoOperation)].emplace_back(semantic_no_operation);
    semantics_[static_cast<std::size_t>(Instruction::BeginBlock)].emplace_back(semantic_begin_block);
    semantics_[static_cast<std::size_t>(Instruction::NorthSouthIf)].emplace_back(semantic_north_south_if);
    semantics_[static_cast<std::size_t>(Instruction::EndBlock)].emplace_back(semantic_end_block);
    semantics_[static_cast<std::size_t>(Instruction::InputCharacter)].emplace_back(semantic_input_character);
}
