#include "instruction_stack.hpp"
#include <chrono>
#include <utility>
#include "fingerprints.hpp"
#include "fmt/format.h"
#include "instruction_pointer.hpp"
#include "instructions.hpp"
#include "mizu/util/rng.hpp"

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
InstructionAction instruction_a(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_b(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_c(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_d(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_e(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_f(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_g(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_h(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_i(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_j(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_k(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_l(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_m(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_n(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_o(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_p(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_q(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_r(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_s(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_t(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_u(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_v(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_w(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_x(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_y(Fungespace &, InstructionPointer &ip);
InstructionAction instruction_z(Fungespace &, InstructionPointer &ip);
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

InstructionStack::InstructionStack() {
    populate_default_fns_();
}

InstructionAction InstructionStack::perform(Instruction ins, Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.stringmode) {
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
    fns[static_cast<std::size_t>(Instruction::A)].push_back(instruction_a);
    fns[static_cast<std::size_t>(Instruction::B)].push_back(instruction_b);
    fns[static_cast<std::size_t>(Instruction::C)].push_back(instruction_c);
    fns[static_cast<std::size_t>(Instruction::D)].push_back(instruction_d);
    fns[static_cast<std::size_t>(Instruction::E)].push_back(instruction_e);
    fns[static_cast<std::size_t>(Instruction::F)].push_back(instruction_f);
    fns[static_cast<std::size_t>(Instruction::G)].push_back(instruction_g);
    fns[static_cast<std::size_t>(Instruction::H)].push_back(instruction_h);
    fns[static_cast<std::size_t>(Instruction::I)].push_back(instruction_i);
    fns[static_cast<std::size_t>(Instruction::J)].push_back(instruction_j);
    fns[static_cast<std::size_t>(Instruction::K)].push_back(instruction_k);
    fns[static_cast<std::size_t>(Instruction::L)].push_back(instruction_l);
    fns[static_cast<std::size_t>(Instruction::M)].push_back(instruction_m);
    fns[static_cast<std::size_t>(Instruction::N)].push_back(instruction_n);
    fns[static_cast<std::size_t>(Instruction::O)].push_back(instruction_o);
    fns[static_cast<std::size_t>(Instruction::P)].push_back(instruction_p);
    fns[static_cast<std::size_t>(Instruction::Q)].push_back(instruction_q);
    fns[static_cast<std::size_t>(Instruction::R)].push_back(instruction_r);
    fns[static_cast<std::size_t>(Instruction::S)].push_back(instruction_s);
    fns[static_cast<std::size_t>(Instruction::T)].push_back(instruction_t);
    fns[static_cast<std::size_t>(Instruction::U)].push_back(instruction_u);
    fns[static_cast<std::size_t>(Instruction::V)].push_back(instruction_v);
    fns[static_cast<std::size_t>(Instruction::W)].push_back(instruction_w);
    fns[static_cast<std::size_t>(Instruction::X)].push_back(instruction_x);
    fns[static_cast<std::size_t>(Instruction::Y)].push_back(instruction_y);
    fns[static_cast<std::size_t>(Instruction::Z)].push_back(instruction_z);
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

InstructionAction instruction_space(Fungespace &, InstructionPointer &) {
    std::unreachable();
}

InstructionAction instruction_logical_not(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(ip.stack.pop() == 0 ? 1 : 0);
    return MoveAction{};
}

InstructionAction instruction_toggle_stringmode(Fungespace &, InstructionPointer &ip) {
    ip.stringmode = !ip.stringmode;
    return MoveAction{};
}

InstructionAction instruction_trampoline(Fungespace &fungespace, InstructionPointer &ip) {
    ip.step_wrap(fungespace);
    return MoveAction{};
}

InstructionAction instruction_pop(Fungespace &, InstructionPointer &ip) {
    ip.stack.pop();
    return MoveAction{};
}

InstructionAction instruction_remainder(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}

InstructionAction instruction_input_integer(Fungespace &, InstructionPointer &ip) {
    // Decimal input reads and discards characters until it encounters decimal digit characters [...]
    // TODO: deal with the case where the '-' isn't immediately followed by digits

    int ch;
    do {
        ch = std::getchar();

        // Detect EOF for piped input
        if (ch == EOF) {
            ip.reflect();
            return MoveAction{};
        }
    } while (!(ch == '-' || std::isdigit(ch)));

    bool negate_result = ch == '-';

    // [...] at which point it reads a decimal number from those digits, up until (but not including)
    // the point at which input characters stop being digits, or the point where the next digit
    // would cause a cell overflow, whichever comes first

    std::int64_t i = ch == '-' ? 0 : ch - '0';
    do {
        ch = std::getchar();
        if (std::isdigit(ch)) {
            std::int64_t tmp = i;
            i *= 10;
            if (i / 10 != tmp) {
                // We overflowed, put the digit back and exit early
                std::ungetc(ch, stdin);
                i = tmp;
                break;
            }
            i += ch - '0';
        } else {
            // Not eating it seems wrong for line-buffered input
            if (ch != '\n')
                std::ungetc(ch, stdin);
        }
    } while (std::isdigit(ch));

    ip.stack.push(negate_result ? -i : i);

    return MoveAction{};
}

InstructionAction instruction_fetch_character(Fungespace &fungespace, InstructionPointer &ip) {
    ip.step_wrap(fungespace);
    ip.stack.push(fungespace.get(ip.pos[0], ip.pos[1]));
    return MoveAction{};
}

InstructionAction instruction_load_semantics(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.stack.pop();

    std::int64_t fingerprint = 0;
    for (std::int64_t i = 0; i < n; i++) {
        fingerprint *= 256;
        fingerprint += ip.stack.pop();
    }

    if (!load_fingerprint(ip.instruction_stack, fingerprint)) {
        ip.reflect();
    } else {
        ip.stack.push(fingerprint);
        ip.stack.push(1);
    }

    return MoveAction{};
}

InstructionAction instruction_unload_semantics(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.stack.pop();

    std::int64_t fingerprint = 0;
    for (std::int64_t i = 0; i < n; i++) {
        fingerprint *= 256;
        fingerprint += ip.stack.pop();
    }

    if (!unload_fingerprint(ip.instruction_stack, fingerprint))
        ip.reflect();

    return MoveAction{};
}

InstructionAction instruction_multiply(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a * b);
    return MoveAction{};
}

InstructionAction instruction_add(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a + b);
    return MoveAction{};
}

InstructionAction instruction_output_character(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    fmt::print("{}", static_cast<char>(v));
    return MoveAction{};
}

InstructionAction instruction_subtract(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a - b);
    return MoveAction{};
}

InstructionAction instruction_output_integer(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    fmt::print("{} ", v);
    return MoveAction{};
}

InstructionAction instruction_divide(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(b == 0 ? 0 : a / b);
    return MoveAction{};
}

InstructionAction instruction_push_zero(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(0);
    return MoveAction{};
}

InstructionAction instruction_push_one(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(1);
    return MoveAction{};
}

InstructionAction instruction_push_two(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(2);
    return MoveAction{};
}

InstructionAction instruction_push_three(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(3);
    return MoveAction{};
}

InstructionAction instruction_push_four(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(4);
    return MoveAction{};
}

InstructionAction instruction_push_five(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(5);
    return MoveAction{};
}

InstructionAction instruction_push_six(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(6);
    return MoveAction{};
}

InstructionAction instruction_push_seven(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(7);
    return MoveAction{};
}

InstructionAction instruction_push_eight(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(8);
    return MoveAction{};
}

InstructionAction instruction_push_niner(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(9);
    return MoveAction{};
}

InstructionAction instruction_duplicate(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    ip.stack.push(v);
    ip.stack.push(v);
    return MoveAction{};
}

InstructionAction instruction_jump_over(Fungespace &, InstructionPointer &) {
    std::unreachable();
}

InstructionAction instruction_go_west(Fungespace &, InstructionPointer &ip) {
    ip.delta[0] = WEST[0];
    ip.delta[1] = WEST[1];
    return MoveAction{};
}

InstructionAction instruction_execute(Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction instruction_go_east(Fungespace &, InstructionPointer &ip) {
    ip.delta[0] = EAST[0];
    ip.delta[1] = EAST[1];
    return MoveAction{};
}

InstructionAction instruction_go_away(Fungespace &, InstructionPointer &ip) {
    switch (mizu::rng::get<std::size_t>(3)) {
    case 0:
        ip.delta[0] = SOUTH[0];
        ip.delta[1] = SOUTH[1];
        break;
    case 1:
        ip.delta[0] = EAST[0];
        ip.delta[1] = EAST[1];
        break;
    case 2:
        ip.delta[0] = NORTH[0];
        ip.delta[1] = NORTH[1];
        break;
    case 3:
        ip.delta[0] = WEST[0];
        ip.delta[1] = WEST[1];
        break;
    default:
        std::unreachable();
    }
    return MoveAction{};
}

InstructionAction instruction_stop(Fungespace &, InstructionPointer &ip) {
    ip.alive = false;
    return KillAction{};
}

InstructionAction instruction_a(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_b(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_c(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_d(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_e(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_f(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_g(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_h(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_i(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_j(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_k(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_l(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_m(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_n(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_o(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_p(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_q(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_r(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_s(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_t(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_u(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_v(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_w(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_x(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_y(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_z(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_turn_left(Fungespace &, InstructionPointer &ip) {
    ip.turn_left();
    return MoveAction{};
}

InstructionAction instruction_swap(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(b);
    ip.stack.push(a);
    return MoveAction{};
}

InstructionAction instruction_turn_right(Fungespace &, InstructionPointer &ip) {
    ip.turn_right();
    return MoveAction{};
}

InstructionAction instruction_go_north(Fungespace &, InstructionPointer &ip) {
    ip.delta[0] = NORTH[0];
    ip.delta[1] = NORTH[1];
    return MoveAction{};
}

InstructionAction instruction_east_west_if(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    if (v == 0) {
        ip.delta[0] = EAST[0];
        ip.delta[1] = EAST[1];
    } else {
        ip.delta[0] = WEST[0];
        ip.delta[1] = WEST[1];
    }
    return MoveAction{};
}

InstructionAction instruction_greater_than(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a > b ? 1 : 0);
    return MoveAction{};
}

InstructionAction instruction_push_ten(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(10);
    return MoveAction{};
}

InstructionAction instruction_push_eleven(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(11);
    return MoveAction{};
}

InstructionAction instruction_push_twelve(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(12);
    return MoveAction{};
}

InstructionAction instruction_push_thirteen(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(13);
    return MoveAction{};
}

InstructionAction instruction_push_fourteen(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(14);
    return MoveAction{};
}

InstructionAction instruction_push_fifteen(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(15);
    return MoveAction{};
}

InstructionAction instruction_get(const Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();
    ip.stack.push(fungespace.get(x + ip.storage_offset[0], y + ip.storage_offset[1]));
    return MoveAction{};
}

InstructionAction instruction_go_high(Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction instruction_input_file(Fungespace &fungespace, InstructionPointer &ip) {
    const auto filename = ip.stack.pop_gnirts();
    const auto flags = ip.stack.pop();
    const auto y = ip.stack.pop() + ip.storage_offset[1];
    const auto x = ip.stack.pop() + ip.storage_offset[0];

    std::int64_t size[2];
    if (fungespace.input_file(filename, flags, x, y, size)) {
        ip.stack.push(size[0]);
        ip.stack.push(size[1]);
        ip.stack.push(x);
        ip.stack.push(y);
    } else {
        ip.reflect();
    }

    return MoveAction{};
}

InstructionAction instruction_jump_forward(Fungespace &fungespace, InstructionPointer &ip) {
    auto n = ip.stack.pop();

    ip.save_delta();

    if (n < 0) {
        ip.reflect();
        n = std::abs(n);
    }
    for (std::int64_t i = 0; i < n; ++i)
        ip.step_wrap(fungespace);

    ip.restore_delta();

    return MoveAction{};
}

InstructionAction instruction_iterate(Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.stack.pop();

    ip.save_pos();
    ip.step_to_next_instruction(fungespace, '\0', false);

    if (n == 0)
        return MoveAction{};

    const auto iter_ins = fungespace.get(ip.pos[0], ip.pos[1]);
    ip.restore_pos();

    std::vector<InstructionAction> ret{};
    for (std::int64_t i = 0; i < n; ++i)
        ret.emplace_back(ip.instruction_stack.perform(static_cast<Instruction>(iter_ins), fungespace, ip));

    return IterAction{ret};
}

InstructionAction instruction_go_low(Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction instruction_high_low_if(Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction instruction_clear_stack(Fungespace &, InstructionPointer &ip) {
    ip.stack.clear();
    return MoveAction{};
}

InstructionAction instruction_output_file(Fungespace &fungespace, InstructionPointer &ip) {
    const auto filename = ip.stack.pop_gnirts();
    const auto flags = ip.stack.pop();
    const auto y = ip.stack.pop() + ip.storage_offset[1];
    const auto x = ip.stack.pop() + ip.storage_offset[0];
    const auto h = ip.stack.pop();
    const auto w = ip.stack.pop();

    if (!fungespace.output_file(filename, flags, x, y, w, h))
        ip.reflect();

    return MoveAction{};
}

InstructionAction instruction_put(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();
    const auto v = ip.stack.pop();
    fungespace.put(x + ip.storage_offset[0], y + ip.storage_offset[1], v);
    return MoveAction{};
}

InstructionAction instruction_quit(Fungespace &, InstructionPointer &ip) {
    return QuitAction{static_cast<int>(ip.stack.pop())};
}

InstructionAction instruction_reflect(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_store_character(Fungespace &fungespace, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    ip.step_wrap(fungespace);
    fungespace.put(ip.pos[0], ip.pos[1], v);
    return MoveAction{};
}

InstructionAction instruction_split(Fungespace &, InstructionPointer &) {
    return SplitAction{};
}

InstructionAction instruction_stack_under_stack(Fungespace &, InstructionPointer &ip) {
    ip.stack_under_stack();
    return MoveAction{};
}

InstructionAction instruction_go_south(Fungespace &, InstructionPointer &ip) {
    ip.delta[0] = SOUTH[0];
    ip.delta[1] = SOUTH[1];
    return MoveAction{};
}

InstructionAction instruction_compare(Fungespace &fungespace, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    if (a > b)
        return ip.instruction_stack.perform(Instruction::TurnRight, fungespace, ip);
    if (b > a)
        return ip.instruction_stack.perform(Instruction::TurnLeft, fungespace, ip);
    return MoveAction{};
}

InstructionAction instruction_absolute_delta(Fungespace &, InstructionPointer &ip) {
    const auto dy = ip.stack.pop();
    const auto dx = ip.stack.pop();
    ip.delta[0] = dx;
    ip.delta[1] = dy;
    return MoveAction{};
}

InstructionAction instruction_get_sysinfo(const Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.stack.pop();

    std::vector<std::int64_t> sysinfo{};

    // 0x01: high if t is implemented
    // 0x02: high if i is implemented
    // 0x04: high if o is implemented
    // 0x08: high if = is implemented
    // 0x10: high if unbuffered stdio
    sysinfo.push_back(0b00111);

    // number of bytes per cell
    sysinfo.push_back(8);

    // implementation's handprint
    sysinfo.push_back(0);

    // implementation's version number
    sysinfo.push_back(1);

    // id code for the operating paradigm
    // 0 = unavailable
    // 1 = equivalent to C-language `system()` call behavior
    // 2 = equivalent to interpretation by a specific shell of program (document)
    // 3 = equivalent to interpretation by the same shell that started this Funge interpreter
    sysinfo.push_back(0);

    // path separator character
    sysinfo.push_back('/');

    // number of scalars per vector (1 for une, 2 for be, 3 for trefunge)
    sysinfo.push_back(2);

    // unique ID for current IP
    sysinfo.push_back(ip.id);

    // TODO: unique team number for current IP
    sysinfo.push_back(0);

    // fungespace position of current IP
    sysinfo.push_back(ip.pos[1]);
    sysinfo.push_back(ip.pos[0]);

    // fungespace delta of current IP
    sysinfo.push_back(ip.delta[1]);
    sysinfo.push_back(ip.delta[0]);

    // fungespace storage offset of current IP
    sysinfo.push_back(ip.storage_offset[1]);
    sysinfo.push_back(ip.storage_offset[0]);

    // least point which contains a non-space cell
    sysinfo.push_back(fungespace.min_coord[1]);
    sysinfo.push_back(fungespace.min_coord[0]);

    // greatest point which contains a non-space cell relative to the least
    sysinfo.push_back(fungespace.max_coord[1] - 1 + std::abs(fungespace.min_coord[1]));
    sysinfo.push_back(fungespace.max_coord[0] - 1 + std::abs(fungespace.min_coord[0]));

    const std::chrono::system_clock::time_point now_utc = std::chrono::system_clock::now();
    const std::chrono::time_point now = std::chrono::current_zone()->to_local(now_utc);
    const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    const std::chrono::hh_mm_ss hms{now - std::chrono::floor<std::chrono::days>(now)};
    const auto year = static_cast<int>(ymd.year());
    const auto month = static_cast<unsigned>(ymd.month());
    const auto day = static_cast<unsigned>(ymd.day());
    const auto hour = static_cast<long long>(hms.hours().count());
    const auto minute = static_cast<long long>(hms.minutes().count());
    const auto second = hms.seconds().count();

    // current ((year - 1900) * 256 * 256) + (month * 256) + (day of month)
    sysinfo.push_back(
            (static_cast<long long>(year) - 1900) * 256 * 256 + static_cast<long long>(month) * 256 +
            static_cast<long long>(day));

    // current (hour * 256 * 256) + (minute * 256) + (second)
    sysinfo.push_back(hour * 256 * 256 + minute * 256 + second);

    // number of stacks in use by IP
    sysinfo.push_back(static_cast<std::int64_t>(ip.stack.count()));

    // size of each stack in stackstack (from TOSS to BOSS)
    const auto sizes = ip.stack.sizes();
    for (std::size_t i = 0; i < sizes.size(); i++)
        sysinfo.push_back(static_cast<std::int64_t>(sizes[i]));

    // TODO: command line arguments followed by double null
    sysinfo.push_back('\0');
    sysinfo.push_back('\0');

    // TODO: env variables followed by null
    sysinfo.push_back('\0');

    if (n <= 0)
        for (std::size_t i = 0; i < sysinfo.size(); i++)
            ip.stack.push(sysinfo[sysinfo.size() - 1 - i]);
    else if (static_cast<std::size_t>(n) <= sysinfo.size())
        ip.stack.push(sysinfo[n - 1]);
    else
        ip.stack.push(ip.stack.pick(n - sysinfo.size()));

    return MoveAction{};
}

InstructionAction instruction_no_operation(Fungespace &, InstructionPointer &) {
    return MoveAction{};
}

InstructionAction instruction_begin_block(Fungespace &, InstructionPointer &ip) {
    ip.begin_block();
    return MoveAction{};
}

InstructionAction instruction_north_south_if(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    if (v == 0) {
        ip.delta[0] = SOUTH[0];
        ip.delta[1] = SOUTH[1];
    } else {
        ip.delta[0] = NORTH[0];
        ip.delta[1] = NORTH[1];
    }
    return MoveAction{};
}

InstructionAction instruction_end_block(Fungespace &, InstructionPointer &ip) {
    ip.end_block();
    return MoveAction{};
}

InstructionAction instruction_input_character(Fungespace &, InstructionPointer &ip) {
    int i = std::getchar();
    if (i == EOF)
        ip.reflect();
    else
        ip.stack.push(i);
    return MoveAction{};
}
