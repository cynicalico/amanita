#include "interpreter.hpp"
#include <utility>
#include "fmt/format.h"
#include "mizu/util/rng.hpp"

Interpreter::Interpreter(const std::filesystem::path &path)
    : fungespace(path) {}

void Interpreter::run() {
    active_list.emplace_back();

    while (!active_list.empty()) {
        inactive_list.clear();

        for (auto &ip: active_list) {
            Cell ins;
            do {
                ins = fungespace.get(ip.pos[0], ip.pos[1]);
                if (!ip.stringmode && (ins == Instruction::Space || ins == Instruction::JumpOver))
                    step_to_next_instruction(ip, '\0', ins == Instruction::JumpOver);
                else
                    break;
            } while (true);
            ip.cache_ins = ins;

            auto action = perform_instruction(static_cast<Instruction>(ins), ip);
            std::visit(
                    overloaded{
                            [&](const IterAction &a) {
                                if (!ip.alive)
                                    return;

                                for (const auto &sub_action: a.actions) {
                                    if (std::holds_alternative<SplitAction>(sub_action)) {
                                        auto new_ip = InstructionPointer(ip);
                                        new_ip.reflect();

                                        inactive_list.push_back(std::move(new_ip));
                                    } else if (std::holds_alternative<QuitAction>(sub_action)) {
                                        std::exit(std::get<QuitAction>(sub_action).exit_code);
                                    }
                                }

                                inactive_list.push_back(std::move(ip));
                            },
                            [&](const KillAction &) {
                                /* do nothing, ip does not live on */
                            },
                            [&](const MoveAction &) {
                                inactive_list.push_back(std::move(ip));
                            },
                            [&](const SplitAction &) {
                                auto new_ip = InstructionPointer(ip);
                                new_ip.reflect();

                                inactive_list.push_back(std::move(new_ip));
                                inactive_list.push_back(std::move(ip));
                            },
                            [&](const QuitAction &a) {
                                std::exit(a.exit_code);
                            }},
                    action);
        }

        std::swap(active_list, inactive_list);
        for (auto &ip: active_list)
            step_to_next_instruction(ip, ip.cache_ins, false);
    }
}

InstructionAction Interpreter::perform_instruction(Instruction ins, InstructionPointer &ip) {
    if (ip.stringmode) {
        if (ins != Instruction::ToggleStringmode) {
            ip.stack.push(static_cast<std::int64_t>(ins));
            return MoveAction{};
        }
    }

    switch (ins) {
    case Instruction::Space:
        std::unreachable();

    case Instruction::LogicalNot:
        ip.stack.push(ip.stack.pop() == 0 ? 1 : 0);
        return MoveAction{};

    case Instruction::ToggleStringmode:
        ip.stringmode = !ip.stringmode;
        return MoveAction{};

    case Instruction::Trampoline:
        step_wrap(ip);
        return MoveAction{};

    case Instruction::Pop:
        ip.stack.pop();
        return MoveAction{};

    case Instruction::Remainder: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(b == 0 ? 0 : a % b);
        return MoveAction{};
    }

    case Instruction::InputInteger:
        ip.reflect(); // TODO
        return MoveAction{};

    case Instruction::FetchCharacter: {
        step_wrap(ip);
        ip.stack.push(fungespace.get(ip.pos[0], ip.pos[1]));
        return MoveAction{};
    }

    case Instruction::LoadSemantics: {
        const auto n = ip.stack.pop();

        std::int64_t fingerprint = 0;
        for (std::int64_t i = 0; i < n; i++) {
            fingerprint *= 256;
            fingerprint += ip.stack.pop();
        }
        // TODO: Try and load it
        ip.reflect();

        return MoveAction{};
    }

    case Instruction::UnloadSemantics: {
        const auto n = ip.stack.pop();

        std::int64_t fingerprint = 0;
        for (std::int64_t i = 0; i < n; i++) {
            fingerprint *= 256;
            fingerprint += ip.stack.pop();
        }
        // TODO: Try and unload it
        ip.reflect();

        return MoveAction{};
    }

    case Instruction::Multiply: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(a * b);
        return MoveAction{};
    }

    case Instruction::Add: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(a + b);
        return MoveAction{};
    }

    case Instruction::OutputCharacter: {
        const auto v = ip.stack.pop();
        fmt::print("{}", static_cast<char>(v));
        return MoveAction{};
    }

    case Instruction::Subtract: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(a - b);
        return MoveAction{};
    }

    case Instruction::OutputInteger: {
        const auto v = ip.stack.pop();
        fmt::print("{} ", v);
        return MoveAction{};
    }

    case Instruction::Divide: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(b == 0 ? 0 : a / b);
        return MoveAction{};
    }

    case Instruction::PushZero:
        ip.stack.push(0);
        return MoveAction{};

    case Instruction::PushOne:
        ip.stack.push(1);
        return MoveAction{};

    case Instruction::PushTwo:
        ip.stack.push(2);
        return MoveAction{};

    case Instruction::PushThree:
        ip.stack.push(3);
        return MoveAction{};

    case Instruction::PushFour:
        ip.stack.push(4);
        return MoveAction{};

    case Instruction::PushFive:
        ip.stack.push(5);
        return MoveAction{};

    case Instruction::PushSix:
        ip.stack.push(6);
        return MoveAction{};

    case Instruction::PushSeven:
        ip.stack.push(7);
        return MoveAction{};

    case Instruction::PushEight:
        ip.stack.push(8);
        return MoveAction{};

    case Instruction::PushNiner:
        ip.stack.push(9);
        return MoveAction{};

    case Instruction::Duplicate: {
        const auto v = ip.stack.pop();
        ip.stack.push(v);
        ip.stack.push(v);
        return MoveAction{};
    }

    case Instruction::JumpOver:
        std::unreachable();

    case Instruction::GoWest: {
        ip.delta[0] = WEST[0];
        ip.delta[1] = WEST[1];
        return MoveAction{};
    }

    case Instruction::Execute:
        ip.reflect(); // TODO
        return MoveAction{};

    case Instruction::GoEast: {
        ip.delta[0] = EAST[0];
        ip.delta[1] = EAST[1];
        return MoveAction{};
    }

    case Instruction::GoAway: {
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

    case Instruction::Stop:
        ip.alive = false;
        return KillAction{};

    case Instruction::A:
    case Instruction::B:
    case Instruction::C:
    case Instruction::D:
    case Instruction::E:
    case Instruction::F:
    case Instruction::G:
    case Instruction::H:
    case Instruction::I:
    case Instruction::J:
    case Instruction::K:
    case Instruction::L:
    case Instruction::M:
    case Instruction::N:
    case Instruction::O:
    case Instruction::P:
    case Instruction::Q:
    case Instruction::R:
    case Instruction::S:
    case Instruction::T:
    case Instruction::U:
    case Instruction::V:
    case Instruction::W:
    case Instruction::X:
    case Instruction::Y:
    case Instruction::Z:
        ip.reflect();
        return MoveAction{};

    case Instruction::TurnLeft: {
        const auto tmp = ip.delta[0];
        ip.delta[0] = ip.delta[1];
        ip.delta[1] = -tmp;
        return MoveAction{};
    }

    case Instruction::Swap: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(b);
        ip.stack.push(a);
        return MoveAction{};
    }

    case Instruction::TurnRight: {
        const auto tmp = ip.delta[0];
        ip.delta[0] = -ip.delta[1];
        ip.delta[1] = tmp;
        return MoveAction{};
    }

    case Instruction::GoNorth: {
        ip.delta[0] = NORTH[0];
        ip.delta[1] = NORTH[1];
        return MoveAction{};
    }

    case Instruction::EastWestIf: {
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

    case Instruction::GreaterThan: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        ip.stack.push(a > b ? 1 : 0);
        return MoveAction{};
    }

    case Instruction::PushTen:
        ip.stack.push(10);
        return MoveAction{};

    case Instruction::PushEleven:
        ip.stack.push(11);
        return MoveAction{};

    case Instruction::PushTwelve:
        ip.stack.push(12);
        return MoveAction{};

    case Instruction::PushThirteen:
        ip.stack.push(13);
        return MoveAction{};

    case Instruction::PushFourteen:
        ip.stack.push(14);
        return MoveAction{};

    case Instruction::PushFifteen:
        ip.stack.push(15);
        return MoveAction{};

    case Instruction::Get: {
        const auto y = ip.stack.pop();
        const auto x = ip.stack.pop();
        ip.stack.push(fungespace.get(x + ip.storage_offset[0], y + ip.storage_offset[1]));
        return MoveAction{};
    }

    case Instruction::GoHigh:
        ip.reflect(); // TODO
        return MoveAction{};

    case Instruction::InputFile: {
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

    case Instruction::JumpForward: {
        auto n = ip.stack.pop();

        std::int64_t saved_delta[2] = {ip.delta[0], ip.delta[1]};

        if (n < 0) {
            ip.reflect();
            n = std::abs(n);
        }
        for (std::int64_t i = 0; i < n; ++i)
            step_wrap(ip);

        ip.delta[0] = saved_delta[0];
        ip.delta[1] = saved_delta[1];

        return MoveAction{};
    }

    case Instruction::Iterate: {
        const auto n = ip.stack.pop();

        std::int64_t saved_pos[2] = {ip.pos[0], ip.pos[1]};
        step_to_next_instruction(ip, '\0', false);

        if (n == 0)
            return MoveAction{};

        const auto iter_ins = fungespace.get(ip.pos[0], ip.pos[1]);
        ip.pos[0] = saved_pos[0];
        ip.pos[1] = saved_pos[1];

        std::vector<InstructionAction> ret{};
        for (std::int64_t i = 0; i < n; ++i)
            ret.emplace_back(perform_instruction(static_cast<Instruction>(iter_ins), ip));

        return IterAction{ret};
    }
    case Instruction::GoLow:
        ip.reflect(); // TODO
        return MoveAction{};

    case Instruction::HighLowIf:
        ip.reflect(); // TODO
        return MoveAction{};

    case Instruction::ClearStack:
        ip.stack.clear();
        return MoveAction{};

    case Instruction::OutputFile: {
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

    case Instruction::Put: {
        const auto y = ip.stack.pop();
        const auto x = ip.stack.pop();
        const auto v = ip.stack.pop();
        fungespace.put(x + ip.storage_offset[0], y + ip.storage_offset[1], v);
        return MoveAction{};
    }
    case Instruction::Quit:
        return QuitAction{static_cast<int>(ip.stack.pop())};

    case Instruction::Reflect:
        ip.reflect();
        return MoveAction{};

    case Instruction::StoreCharacter: {
        const auto v = ip.stack.pop();
        step_wrap(ip);
        fungespace.put(ip.pos[0], ip.pos[1], v);
        return MoveAction{};
    }

    case Instruction::Split:
        return SplitAction{};

    case Instruction::StackUnderStack:
        ip.stack_under_stack();
        return MoveAction{};

    case Instruction::GoSouth: {
        ip.delta[0] = SOUTH[0];
        ip.delta[1] = SOUTH[1];
        return MoveAction{};
    }

    case Instruction::Compare: {
        const auto b = ip.stack.pop();
        const auto a = ip.stack.pop();
        if (a > b)
            return perform_instruction(Instruction::TurnRight, ip);
        if (b > a)
            return perform_instruction(Instruction::TurnLeft, ip);
        return MoveAction{};
    }

    case Instruction::AbsoluteDelta: {
        const auto dy = ip.stack.pop();
        const auto dx = ip.stack.pop();
        ip.delta[0] = dx;
        ip.delta[1] = dy;
        return MoveAction{};
    }

    case Instruction::GetSysinfo: {
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

    case Instruction::NoOperation:
        return MoveAction{};

    case Instruction::BeginBlock:
        ip.begin_block();
        return MoveAction{};

    case Instruction::NorthSouthIf: {
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

    case Instruction::EndBlock:
        ip.end_block();
        return MoveAction{};

    case Instruction::InputCharacter:
        ip.reflect(); // TODO
        return MoveAction{};

    default: {
        fmt::println("Unknown instruction: {}/{}, reflecting", static_cast<std::int64_t>(ins), static_cast<char>(ins));
        ip.reflect();
        return MoveAction{};
    }
    }
}

void Interpreter::step_wrap(InstructionPointer &ip) {
    ip.step();
    if (!fungespace.in_bounds(ip.pos[0], ip.pos[1])) {
        ip.reflect();
        ip.step();
        while (fungespace.in_bounds(ip.pos[0], ip.pos[1]))
            ip.step();
        ip.reflect();
        ip.step();
    }
}

void Interpreter::step_to_next_instruction(InstructionPointer &ip, Cell prev_ins, bool start_skipping) {
    bool skipping = start_skipping;
    do {
        step_wrap(ip);
        const auto ins = fungespace.get(ip.pos[0], ip.pos[1]);

        if (ip.stringmode) {
            if (!skipping) {
                // SFML spaces, start skipping any spaces after first
                if (ins == Instruction::Space && prev_ins == Instruction::Space) {
                    skipping = true;
                    continue;
                }
            } else if (ins == Instruction::Space) {
                continue;
            }
        } else if (!skipping) {
            // Start skipping comment
            if (ins == Instruction::JumpOver) {
                skipping = true;
                continue;
            }
            // Ignore spaces
            if (ins == Instruction::Space)
                continue;
        } else {
            // Stop skipping at end of comment
            if (ins == Instruction::JumpOver)
                skipping = false;
            // Need to move at least one more time even if skipping stopped
            continue;
        }

        break;
    } while (true);
}
