#include "instruction_stack.hpp"
#include <fmt/format.h>
#include <ranges>
#include <unordered_map>
#include "base_instructions.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"
#include "instructions.hpp"

#include "fingerprints/catseye/hrti.hpp"
#include "fingerprints/catseye/mode.hpp"
#include "fingerprints/catseye/modu.hpp"
#include "fingerprints/catseye/null.hpp"
#include "fingerprints/catseye/orth.hpp"
#include "fingerprints/catseye/perl.hpp"
#include "fingerprints/catseye/refc.hpp"
#include "fingerprints/catseye/roma.hpp"
#include "fingerprints/catseye/toys.hpp"
#include "fingerprints/rcs/dirf.hpp"
#include "fingerprints/rcs/evar.hpp"
#include "fingerprints/rcs/file.hpp"
#include "fingerprints/rcs/fixp.hpp"
#include "fingerprints/rcs/fpdp.hpp"
#include "fingerprints/rcs/fpsp.hpp"
#include "fingerprints/rcs/subr.hpp"

const std::unordered_map<std::int64_t, const Fingerprint &> &registry() {
    static std::unordered_map<std::int64_t, const Fingerprint &> registry{
            // Cat's Eye
            {hrti::FINGERPRINT.id, hrti::FINGERPRINT},
            {mode::FINGERPRINT.id, mode::FINGERPRINT},
            {modu::FINGERPRINT.id, modu::FINGERPRINT},
            {null::FINGERPRINT.id, null::FINGERPRINT},
            {orth::FINGERPRINT.id, orth::FINGERPRINT},
            {perl::FINGERPRINT.id, perl::FINGERPRINT},
            {refc::FINGERPRINT.id, refc::FINGERPRINT},
            {roma::FINGERPRINT.id, roma::FINGERPRINT},
            {toys::FINGERPRINT.id, toys::FINGERPRINT},
            // RCS
            {dirf::FINGERPRINT.id, dirf::FINGERPRINT},
            {evar::FINGERPRINT.id, evar::FINGERPRINT},
            {file::FINGERPRINT.id, file::FINGERPRINT},
            {fixp::FINGERPRINT.id, fixp::FINGERPRINT},
            {fpdp::FINGERPRINT.id, fpdp::FINGERPRINT},
            {fpsp::FINGERPRINT.id, fpsp::FINGERPRINT},
            {subr::FINGERPRINT.id, subr::FINGERPRINT},
    };
    return registry;
}

InstructionStack::InstructionStack() {
    populate_default_fns_();
    for (std::size_t i = 0; i < 26; ++i)
        loaded_fingerprints[i] = std::vector{"none"};
}

InstructionAction InstructionStack::perform(Instruction ins, Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.string_mode) {
        if (ins != Instruction::ToggleStringmode) {
            ip.stack.push(static_cast<std::int64_t>(ins));
            return MoveAction{};
        }
    }

    if (ins < Instruction::Space || ins > Instruction::InputCharacter) {
        fmt::println("Unknown instruction: {}/{}, reflecting", static_cast<std::int64_t>(ins), static_cast<char>(ins));
        return fns[static_cast<std::size_t>(Instruction::Reflect)].back()(fungespace, ip);
    }

    return fns[static_cast<std::size_t>(ins)].back()(fungespace, ip);
}

bool InstructionStack::load_fingerprint(const std::int64_t fingerprint) {
    const auto &r = registry();
    if (const auto it = r.find(fingerprint); it != r.end()) {
        for (const auto &[ins, fn]: it->second.fns) {
            fns[static_cast<std::int64_t>(ins)].push_back(fn);
            loaded_fingerprints[static_cast<std::size_t>(ins) - 65].push_back(it->second.name);
        }
        return true;
    }

    return false;
}

bool InstructionStack::unload_fingerprint(const std::int64_t fingerprint) {
    const auto &r = registry();
    if (const auto it = r.find(fingerprint); it != r.end()) {
        for (const auto &ins: it->second.fns | std::views::keys) {
            fns[static_cast<std::int64_t>(ins)].pop_back();
            loaded_fingerprints[static_cast<std::size_t>(ins) - 65].pop_back();
        }
        return true;
    }

    return false;
}

void InstructionStack::populate_default_fns_() {
    fns.resize(127);
    fns[static_cast<std::size_t>(Instruction::Space)].push_back(instruction_space);
    fns[static_cast<std::size_t>(Instruction::LogicalNot)].push_back(instruction_logical_not);
    fns[static_cast<std::size_t>(Instruction::ToggleStringmode)].push_back(instruction_toggle_stringmode);
    fns[static_cast<std::size_t>(Instruction::Trampoline)].push_back(instruction_trampoline);
    fns[static_cast<std::size_t>(Instruction::Pop)].push_back(instruction_pop);
    fns[static_cast<std::size_t>(Instruction::Remainder)].push_back(instruction_remainder);
    fns[static_cast<std::size_t>(Instruction::InputInteger)].push_back(instruction_input_integer);
    fns[static_cast<std::size_t>(Instruction::FetchCharacter)].push_back(instruction_fetch_character);
    fns[static_cast<std::size_t>(Instruction::LoadSemantics)].push_back(instruction_load_semantics);
    fns[static_cast<std::size_t>(Instruction::UnloadSemantics)].push_back(instruction_unload_semantics);
    fns[static_cast<std::size_t>(Instruction::Multiply)].push_back(instruction_multiply);
    fns[static_cast<std::size_t>(Instruction::Add)].push_back(instruction_add);
    fns[static_cast<std::size_t>(Instruction::OutputCharacter)].push_back(instruction_output_character);
    fns[static_cast<std::size_t>(Instruction::Subtract)].push_back(instruction_subtract);
    fns[static_cast<std::size_t>(Instruction::OutputInteger)].push_back(instruction_output_integer);
    fns[static_cast<std::size_t>(Instruction::Divide)].push_back(instruction_divide);
    fns[static_cast<std::size_t>(Instruction::PushZero)].push_back(instruction_push_zero);
    fns[static_cast<std::size_t>(Instruction::PushOne)].push_back(instruction_push_one);
    fns[static_cast<std::size_t>(Instruction::PushTwo)].push_back(instruction_push_two);
    fns[static_cast<std::size_t>(Instruction::PushThree)].push_back(instruction_push_three);
    fns[static_cast<std::size_t>(Instruction::PushFour)].push_back(instruction_push_four);
    fns[static_cast<std::size_t>(Instruction::PushFive)].push_back(instruction_push_five);
    fns[static_cast<std::size_t>(Instruction::PushSix)].push_back(instruction_push_six);
    fns[static_cast<std::size_t>(Instruction::PushSeven)].push_back(instruction_push_seven);
    fns[static_cast<std::size_t>(Instruction::PushEight)].push_back(instruction_push_eight);
    fns[static_cast<std::size_t>(Instruction::PushNiner)].push_back(instruction_push_niner);
    fns[static_cast<std::size_t>(Instruction::Duplicate)].push_back(instruction_duplicate);
    fns[static_cast<std::size_t>(Instruction::JumpOver)].push_back(instruction_jump_over);
    fns[static_cast<std::size_t>(Instruction::GoWest)].push_back(instruction_go_west);
    fns[static_cast<std::size_t>(Instruction::Execute)].push_back(instruction_execute);
    fns[static_cast<std::size_t>(Instruction::GoEast)].push_back(instruction_go_east);
    fns[static_cast<std::size_t>(Instruction::GoAway)].push_back(instruction_go_away);
    fns[static_cast<std::size_t>(Instruction::Stop)].push_back(instruction_stop);
    fns[static_cast<std::size_t>(Instruction::A)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::B)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::C)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::D)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::E)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::F)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::G)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::H)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::I)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::J)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::K)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::L)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::M)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::N)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::O)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::P)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::Q)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::R)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::S)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::T)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::U)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::V)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::W)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::X)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::Y)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::Z)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::TurnLeft)].push_back(instruction_turn_left);
    fns[static_cast<std::size_t>(Instruction::Swap)].push_back(instruction_swap);
    fns[static_cast<std::size_t>(Instruction::TurnRight)].push_back(instruction_turn_right);
    fns[static_cast<std::size_t>(Instruction::GoNorth)].push_back(instruction_go_north);
    fns[static_cast<std::size_t>(Instruction::EastWestIf)].push_back(instruction_east_west_if);
    fns[static_cast<std::size_t>(Instruction::GreaterThan)].push_back(instruction_greater_than);
    fns[static_cast<std::size_t>(Instruction::PushTen)].push_back(instruction_push_ten);
    fns[static_cast<std::size_t>(Instruction::PushEleven)].push_back(instruction_push_eleven);
    fns[static_cast<std::size_t>(Instruction::PushTwelve)].push_back(instruction_push_twelve);
    fns[static_cast<std::size_t>(Instruction::PushThirteen)].push_back(instruction_push_thirteen);
    fns[static_cast<std::size_t>(Instruction::PushFourteen)].push_back(instruction_push_fourteen);
    fns[static_cast<std::size_t>(Instruction::PushFifteen)].push_back(instruction_push_fifteen);
    fns[static_cast<std::size_t>(Instruction::Get)].push_back(instruction_get);
    fns[static_cast<std::size_t>(Instruction::GoHigh)].push_back(instruction_go_high);
    fns[static_cast<std::size_t>(Instruction::InputFile)].push_back(instruction_input_file);
    fns[static_cast<std::size_t>(Instruction::JumpForward)].push_back(instruction_jump_forward);
    fns[static_cast<std::size_t>(Instruction::Iterate)].push_back(instruction_iterate);
    fns[static_cast<std::size_t>(Instruction::GoLow)].push_back(instruction_go_low);
    fns[static_cast<std::size_t>(Instruction::HighLowIf)].push_back(instruction_high_low_if);
    fns[static_cast<std::size_t>(Instruction::ClearStack)].push_back(instruction_clear_stack);
    fns[static_cast<std::size_t>(Instruction::OutputFile)].push_back(instruction_output_file);
    fns[static_cast<std::size_t>(Instruction::Put)].push_back(instruction_put);
    fns[static_cast<std::size_t>(Instruction::Quit)].push_back(instruction_quit);
    fns[static_cast<std::size_t>(Instruction::Reflect)].push_back(instruction_reflect);
    fns[static_cast<std::size_t>(Instruction::StoreCharacter)].push_back(instruction_store_character);
    fns[static_cast<std::size_t>(Instruction::Split)].push_back(instruction_split);
    fns[static_cast<std::size_t>(Instruction::StackUnderStack)].push_back(instruction_stack_under_stack);
    fns[static_cast<std::size_t>(Instruction::GoSouth)].push_back(instruction_go_south);
    fns[static_cast<std::size_t>(Instruction::Compare)].push_back(instruction_compare);
    fns[static_cast<std::size_t>(Instruction::AbsoluteDelta)].push_back(instruction_absolute_delta);
    fns[static_cast<std::size_t>(Instruction::GetSysinfo)].push_back(instruction_get_sysinfo);
    fns[static_cast<std::size_t>(Instruction::NoOperation)].push_back(instruction_no_operation);
    fns[static_cast<std::size_t>(Instruction::BeginBlock)].push_back(instruction_begin_block);
    fns[static_cast<std::size_t>(Instruction::NorthSouthIf)].push_back(instruction_north_south_if);
    fns[static_cast<std::size_t>(Instruction::EndBlock)].push_back(instruction_end_block);
    fns[static_cast<std::size_t>(Instruction::InputCharacter)].push_back(instruction_input_character);
}
