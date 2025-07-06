#include "base_instructions.hpp"
#include <chrono>
#include <cstdlib>
#include <fmt/format.h>
#include <stack>
#include <utility>
#include "fungespace.hpp"
#include "instruction_pointer.hpp"
#include "mizu/util/rng.hpp"

extern char **environ;

InstructionAction instruction_space(Fungespace &, InstructionPointer &) { std::unreachable(); }

InstructionAction instruction_logical_not(Fungespace &, InstructionPointer &ip) {
    ip.push(ip.pop() == 0 ? 1 : 0);
    return MoveAction{};
}

InstructionAction instruction_toggle_stringmode(Fungespace &, InstructionPointer &ip) {
    ip.string_mode = !ip.string_mode;
    return MoveAction{};
}

InstructionAction instruction_trampoline(Fungespace &fungespace, InstructionPointer &ip) {
    ip.step_wrap(fungespace);
    return MoveAction{};
}

InstructionAction instruction_pop(Fungespace &, InstructionPointer &ip) {
    ip.pop();
    return MoveAction{};
}

InstructionAction instruction_remainder(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(b == 0 ? 0 : a % b);
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
            if (ch != '\n') std::ungetc(ch, stdin);
        }
    } while (std::isdigit(ch));

    ip.push(negate_result ? -i : i);

    return MoveAction{};
}

InstructionAction instruction_fetch_character(Fungespace &fungespace, InstructionPointer &ip) {
    ip.step_wrap(fungespace);
    ip.push(fungespace.get(ip.pos.x, ip.pos.y));
    return MoveAction{};
}

InstructionAction instruction_load_semantics(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switch_mode) fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::UnloadSemantics));

    const auto n = ip.pop();

    std::int64_t fingerprint = 0;
    for (std::int64_t i = 0; i < n; i++) {
        fingerprint *= 256;
        fingerprint += ip.pop();
    }

    if (!ip.instruction_stack.load_fingerprint(fingerprint)) {
        ip.reflect();
    } else {
        ip.push(fingerprint);
        ip.push(1);
    }

    return MoveAction{};
}

InstructionAction instruction_unload_semantics(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switch_mode) fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::LoadSemantics));

    const auto n = ip.pop();

    std::int64_t fingerprint = 0;
    for (std::int64_t i = 0; i < n; i++) {
        fingerprint *= 256;
        fingerprint += ip.pop();
    }

    if (!ip.instruction_stack.unload_fingerprint(fingerprint)) ip.reflect();

    return MoveAction{};
}

InstructionAction instruction_multiply(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a * b);
    return MoveAction{};
}

InstructionAction instruction_add(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a + b);
    return MoveAction{};
}

InstructionAction instruction_output_character(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.pop();
    fmt::print("{}", static_cast<char>(v));
    return MoveAction{};
}

InstructionAction instruction_subtract(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a - b);
    return MoveAction{};
}

InstructionAction instruction_output_integer(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.pop();
    fmt::print("{} ", v);
    return MoveAction{};
}

InstructionAction instruction_divide(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(b == 0 ? 0 : a / b);
    return MoveAction{};
}

InstructionAction instruction_push_zero(Fungespace &, InstructionPointer &ip) {
    ip.push(0);
    return MoveAction{};
}

InstructionAction instruction_push_one(Fungespace &, InstructionPointer &ip) {
    ip.push(1);
    return MoveAction{};
}

InstructionAction instruction_push_two(Fungespace &, InstructionPointer &ip) {
    ip.push(2);
    return MoveAction{};
}

InstructionAction instruction_push_three(Fungespace &, InstructionPointer &ip) {
    ip.push(3);
    return MoveAction{};
}

InstructionAction instruction_push_four(Fungespace &, InstructionPointer &ip) {
    ip.push(4);
    return MoveAction{};
}

InstructionAction instruction_push_five(Fungespace &, InstructionPointer &ip) {
    ip.push(5);
    return MoveAction{};
}

InstructionAction instruction_push_six(Fungespace &, InstructionPointer &ip) {
    ip.push(6);
    return MoveAction{};
}

InstructionAction instruction_push_seven(Fungespace &, InstructionPointer &ip) {
    ip.push(7);
    return MoveAction{};
}

InstructionAction instruction_push_eight(Fungespace &, InstructionPointer &ip) {
    ip.push(8);
    return MoveAction{};
}

InstructionAction instruction_push_niner(Fungespace &, InstructionPointer &ip) {
    ip.push(9);
    return MoveAction{};
}

InstructionAction instruction_duplicate(Fungespace &, InstructionPointer &ip) {
    const auto v = ip.pop();
    ip.push(v);
    ip.push(v);
    return MoveAction{};
}

InstructionAction instruction_jump_over(Fungespace &, InstructionPointer &) { std::unreachable(); }

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
        ip.delta = SOUTH;
        break;
    case 1:
        ip.delta = EAST;
        break;
    case 2:
        ip.delta = NORTH;
        break;
    case 3:
        ip.delta = WEST;
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
    if (ip.switch_mode) fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::TurnRight));
    ip.turn_left();
    return MoveAction{};
}

InstructionAction instruction_swap(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(b);
    ip.push(a);
    return MoveAction{};
}

InstructionAction instruction_turn_right(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switch_mode) fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::TurnLeft));
    ip.turn_right();
    return MoveAction{};
}

InstructionAction instruction_go_north(Fungespace &, InstructionPointer &ip) {
    ip.go_north();
    return MoveAction{};
}

InstructionAction instruction_east_west_if(Fungespace &, InstructionPointer &ip) {
    if (const auto v = ip.pop(); v == 0) ip.go_east();
    else ip.go_west();
    return MoveAction{};
}

InstructionAction instruction_greater_than(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a > b ? 1 : 0);
    return MoveAction{};
}

InstructionAction instruction_push_ten(Fungespace &, InstructionPointer &ip) {
    ip.push(10);
    return MoveAction{};
}

InstructionAction instruction_push_eleven(Fungespace &, InstructionPointer &ip) {
    ip.push(11);
    return MoveAction{};
}

InstructionAction instruction_push_twelve(Fungespace &, InstructionPointer &ip) {
    ip.push(12);
    return MoveAction{};
}

InstructionAction instruction_push_thirteen(Fungespace &, InstructionPointer &ip) {
    ip.push(13);
    return MoveAction{};
}

InstructionAction instruction_push_fourteen(Fungespace &, InstructionPointer &ip) {
    ip.push(14);
    return MoveAction{};
}

InstructionAction instruction_push_fifteen(Fungespace &, InstructionPointer &ip) {
    ip.push(15);
    return MoveAction{};
}

InstructionAction instruction_get(const Fungespace &fungespace, InstructionPointer &ip) {
    const auto v = ip.pop_offset_vec();
    ip.push(fungespace.get(v.x, v.y));
    return MoveAction{};
}

InstructionAction instruction_go_high(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_input_file(Fungespace &fungespace, InstructionPointer &ip) {
    const auto filename = ip.stack.pop_0gnirts();
    const auto flags = ip.pop();
    const auto v = ip.pop_offset_vec();

    if (Vec size; fungespace.input_file(filename, flags, v.x, v.y, size)) {
        ip.push_vec(size);
        ip.push_vec(v);
    } else {
        ip.reflect();
    }

    return MoveAction{};
}

InstructionAction instruction_jump_forward(Fungespace &fungespace, InstructionPointer &ip) {
    auto n = ip.pop();

    ip.save_delta();

    if (n < 0) {
        ip.reflect();
        n = std::abs(n);
    }
    for (Index i = 0; i < n; ++i) ip.step_wrap(fungespace);

    ip.restore_delta();

    return MoveAction{};
}

InstructionAction instruction_iterate(Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.pop();

    ip.save_pos();
    ip.step_to_next_instruction(fungespace, '\0', false);

    if (n == 0) return MoveAction{};

    const auto iter_ins = fungespace.get(ip.pos.x, ip.pos.y);
    ip.restore_pos();

    std::vector<InstructionAction> ret{};
    for (Index i = 0; i < n; ++i)
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
    const auto flags = ip.pop();
    const auto v = ip.pop_offset_vec();
    const auto h = ip.pop();
    const auto w = ip.pop();

    if (!fungespace.output_file(filename, flags, v.x, v.y, w, h)) ip.reflect();

    return MoveAction{};
}

InstructionAction instruction_put(Fungespace &fungespace, InstructionPointer &ip) {
    const auto p = ip.pop_offset_vec();
    const auto v = ip.pop();
    fungespace.put(p.x, p.y, v);
    return MoveAction{};
}

InstructionAction instruction_quit(Fungespace &, InstructionPointer &ip) {
    return QuitAction{static_cast<int>(ip.pop())};
}

InstructionAction instruction_reflect(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}

InstructionAction instruction_store_character(Fungespace &fungespace, InstructionPointer &ip) {
    const auto v = ip.pop();
    ip.step_wrap(fungespace);
    fungespace.put(ip.pos.x, ip.pos.y, v);
    return MoveAction{};
}

InstructionAction instruction_split(Fungespace &, InstructionPointer &) { return SplitAction{}; }

InstructionAction instruction_stack_under_stack(Fungespace &, InstructionPointer &ip) {
    ip.stack_under_stack();
    return MoveAction{};
}

InstructionAction instruction_go_south(Fungespace &, InstructionPointer &ip) {
    ip.go_south();
    return MoveAction{};
}

InstructionAction instruction_compare(Fungespace &fungespace, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    if (a > b) return ip.instruction_stack.perform(Instruction::TurnRight, fungespace, ip);
    if (b > a) return ip.instruction_stack.perform(Instruction::TurnLeft, fungespace, ip);
    return MoveAction{};
}

InstructionAction instruction_absolute_delta(Fungespace &, InstructionPointer &ip) {
    ip.delta = ip.pop_vec();
    return MoveAction{};
}

InstructionAction instruction_get_sysinfo(const Fungespace &fungespace, InstructionPointer &ip) {
    static std::stack<Cell> buf{};

    // Clear before starting
    while (!buf.empty()) buf.pop();

    const auto n = ip.pop();

    // 0x01: high if t is implemented
    // 0x02: high if i is implemented
    // 0x04: high if o is implemented
    // 0x08: high if = is implemented
    // 0x10: high if unbuffered stdio
    buf.push(0b00111);

    // number of bytes per cell
    buf.push(8);

    // implementation's handprint ("NITA")
    buf.push(0x4e495441);

    // implementation's version number (1.0.0)
    buf.push(100);

    // id code for the operating paradigm
    // 0 = unavailable
    // 1 = equivalent to C-language `system()` call behavior
    // 2 = equivalent to interpretation by a specific shell of program (document)
    // 3 = equivalent to interpretation by the same shell that started this Funge interpreter
    buf.push(0);

    // path separator character
    buf.push('/');

    // number of scalars per vector (1 for une, 2 for be, 3 for trefunge)
    buf.push(2);

    // unique ID for current IP
    buf.push(ip.id);

    // unique team number for current IP -- always 0, we don't use this
    buf.push(0);

    // fungespace position of current IP
    buf.push(ip.pos.y);
    buf.push(ip.pos.x);

    // fungespace delta of current IP
    buf.push(ip.delta.y);
    buf.push(ip.delta.x);

    // fungespace storage offset of current IP
    buf.push(ip.storage_offset.y);
    buf.push(ip.storage_offset.x);

    // least point which contains a non-space cell
    buf.push(fungespace.min_coord.y);
    buf.push(fungespace.min_coord.x);

    // greatest point which contains a non-space cell relative to the least
    buf.push(fungespace.max_coord.y - 1 + std::abs(fungespace.min_coord.y));
    buf.push(fungespace.max_coord.x - 1 + std::abs(fungespace.min_coord.x));

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
    buf.push(
            (static_cast<long long>(year) - 1900) * 256 * 256 + static_cast<long long>(month) * 256 +
            static_cast<long long>(day));

    // current (hour * 256 * 256) + (minute * 256) + (second)
    buf.push(hour * 256 * 256 + minute * 256 + second);

    // number of stacks in use by IP
    buf.push(static_cast<Cell>(ip.stack.count()));

    // size of each stack in stackstack (from TOSS to BOSS)
    const auto sizes = ip.stack.sizes();
    for (const auto &size: sizes) buf.push(static_cast<Cell>(size));

    // command line arguments followed by double null
    for (const auto &arg: ip.cli_args->args) {
        for (const auto &c: arg) buf.push(c);
        buf.push('\0');
    }
    buf.push('\0');
    buf.push('\0');

    // env variables followed by null
    for (char **current = environ; *current; ++current) {
        for (char *c = *current; *c; ++c) buf.push(*c);
        buf.push('\0');
    }
    buf.push('\0');

    if (n <= 0) {
        while (!buf.empty()) {
            ip.push(buf.top());
            buf.pop();
        }
    } else if (static_cast<std::size_t>(n) <= buf.size()) {
        while (buf.size() > n) buf.pop();
        ip.push(buf.top());
    } else {
        ip.push(ip.stack.pick(n - buf.size()));
    }

    return MoveAction{};
}

InstructionAction instruction_no_operation(Fungespace &, InstructionPointer &) { return MoveAction{}; }

InstructionAction instruction_begin_block(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switch_mode) fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::EndBlock));
    ip.begin_block();
    return MoveAction{};
}

InstructionAction instruction_north_south_if(Fungespace &, InstructionPointer &ip) {
    if (const auto v = ip.pop(); v == 0) ip.go_south();
    else ip.go_north();
    return MoveAction{};
}

InstructionAction instruction_end_block(Fungespace &fungespace, InstructionPointer &ip) {
    if (ip.switch_mode) fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::BeginBlock));
    ip.end_block();
    return MoveAction{};
}

InstructionAction instruction_input_character(Fungespace &, InstructionPointer &ip) {
    if (int i = std::getchar(); i == EOF) ip.reflect();
    else ip.push(i);
    return MoveAction{};
}
