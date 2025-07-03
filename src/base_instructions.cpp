#include "base_instructions.hpp"
#include <chrono>
#include <cstdlib>
#include <ranges>
#include <utility>
#include "fingerprints.hpp"
#include "fmt/format.h"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"
#include "interpreter.hpp"
#include "mizu/util/rng.hpp"

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

InstructionAction instruction_load_semantics(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switchmode)
        fungespace.put(ip.pos[0], ip.pos[1], static_cast<Cell>(Instruction::UnloadSemantics));

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

InstructionAction instruction_unload_semantics(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switchmode)
        fungespace.put(ip.pos[0], ip.pos[1], static_cast<Cell>(Instruction::LoadSemantics));

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
    ip.go_west();
    return MoveAction{};
}

InstructionAction instruction_execute(Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction instruction_go_east(Fungespace &, InstructionPointer &ip) {
    ip.go_east();
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

InstructionAction instruction_turn_left(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switchmode)
        fungespace.put(ip.pos[0], ip.pos[1], static_cast<Cell>(Instruction::TurnRight));
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

InstructionAction instruction_turn_right(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switchmode)
        fungespace.put(ip.pos[0], ip.pos[1], static_cast<Cell>(Instruction::TurnLeft));
    ip.turn_right();
    return MoveAction{};
}

InstructionAction instruction_go_north(Fungespace &, InstructionPointer &ip) {
    ip.go_north();
    return MoveAction{};
}

InstructionAction instruction_east_west_if(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    if (v == 0)
        ip.go_east();
    else
        ip.go_west();
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
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_input_file(Fungespace &fungespace, InstructionPointer &ip) {
    const auto filename = ip.stack.pop_0gnirts();
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
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_high_low_if(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_clear_stack(Fungespace &, InstructionPointer &ip) {
    ip.stack.clear();
    return MoveAction{};
}

InstructionAction instruction_output_file(Fungespace &fungespace, InstructionPointer &ip) {
    const auto filename = ip.stack.pop_0gnirts();
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
    ip.go_south();
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

    // implementation's handprint ("NITA")
    sysinfo.push_back(0x4e495441);

    // implementation's version number (1.0.0)
    sysinfo.push_back(100);

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
    for (const auto &size: sizes)
        sysinfo.push_back(static_cast<std::int64_t>(size));

    // command line arguments followed by double null
    for (const auto &arg: ip.interpreter->args) {
        for (const auto &c: arg)
            sysinfo.push_back(c);
        sysinfo.push_back('\0');
    }
    sysinfo.push_back('\0');
    sysinfo.push_back('\0');

    // env variables followed by null
    for (char **current = environ; *current; ++current) {
        for (char *c = *current; *c; ++c)
            sysinfo.push_back(*c);
        sysinfo.push_back('\0');
    }
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

InstructionAction instruction_begin_block(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switchmode)
        fungespace.put(ip.pos[0], ip.pos[1], static_cast<Cell>(Instruction::EndBlock));
    ip.begin_block();
    return MoveAction{};
}

InstructionAction instruction_north_south_if(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.stack.pop();
    if (v == 0)
        ip.go_south();
    else
        ip.go_north();
    return MoveAction{};
}

InstructionAction instruction_end_block(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switchmode)
        fungespace.put(ip.pos[0], ip.pos[1], static_cast<Cell>(Instruction::BeginBlock));
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
