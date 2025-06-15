#include <fmt/format.h>
#include <utility>
#include "fungespace.hpp"
#include "instruction_action.hpp"
#include "instruction_pointer.hpp"
#include "instructions.hpp"

void run(const std::filesystem::path &path);
InstructionAction perform_instruction(Instruction ins, Fungespace &fungespace, InstructionPointer &ip);
void step_wrap(const Fungespace &fungespace, InstructionPointer &ip);
void step_to_next_instruction(const Fungespace &fungespace, InstructionPointer &ip, Cell prev_ins, bool start_skipping);

int main() {
    try {
        run("programs/mycology.b98");
    } catch (std::runtime_error e) {
        fmt::println("Exception: {}", e.what());
        return 1;
    }

    return 0;
}

void run(const std::filesystem::path &path) {
    auto fungespace = Fungespace(path);
    auto ip = InstructionPointer();

    bool running = true;
    while (running) {
        Cell ins;
        do {
            ins = fungespace.get(ip.pos[0], ip.pos[1]);
            if (!ip.stringmode && (ins == Instruction::Space || ins == Instruction::JumpOver))
                step_to_next_instruction(fungespace, ip, '\0', ins == Instruction::JumpOver);
            else
                break;
        } while (true);
        ip.cache_ins = ins;

        if (ip.stringmode) {
            if (ins != Instruction::ToggleStringmode) {
                ip.stack.push(ins);
                step_to_next_instruction(fungespace, ip, ip.cache_ins, false);
                continue;
            }
        }

        auto action = perform_instruction(static_cast<Instruction>(ins), fungespace, ip);
        std::visit(
                overloaded{
                        [&](IterAction a) {
                            if (!ip.alive)
                                running = false;
                            else
                                step_to_next_instruction(fungespace, ip, ip.cache_ins, false);
                        },
                        [&](KillAction a) { running = false; },
                        [&](MoveAction a) { step_to_next_instruction(fungespace, ip, ip.cache_ins, false); },
                        [](SplitAction a) { /* TODO */ },
                        [&](QuitAction a) { running = false; }},
                action);
    }
}

InstructionAction perform_instruction(Instruction ins, Fungespace &fungespace, InstructionPointer &ip) {
    switch (ins) {
    case Instruction::Space: std::unreachable();
    case Instruction::LogicalNot: ip.stack.push(ip.stack.pop() == 0 ? 1 : 0); return MoveAction{};
    case Instruction::ToggleStringmode: ip.stringmode = !ip.stringmode; return MoveAction{};
    case Instruction::Trampoline: step_wrap(fungespace, ip); return MoveAction{};
    case Instruction::Pop: ip.stack.pop(); return MoveAction{};
    case Instruction::Remainder: ip.reflect(); return MoveAction{};
    case Instruction::InputInteger: ip.reflect(); return MoveAction{};
    case Instruction::FetchCharacter: ip.reflect(); return MoveAction{};
    case Instruction::LoadSemantics: ip.reflect(); return MoveAction{};
    case Instruction::UnloadSemantics: ip.reflect(); return MoveAction{};
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
    case Instruction::Divide: ip.reflect(); return MoveAction{};
    case Instruction::PushZero: ip.stack.push(0); return MoveAction{};
    case Instruction::PushOne: ip.stack.push(1); return MoveAction{};
    case Instruction::PushTwo: ip.stack.push(2); return MoveAction{};
    case Instruction::PushThree: ip.stack.push(3); return MoveAction{};
    case Instruction::PushFour: ip.stack.push(4); return MoveAction{};
    case Instruction::PushFive: ip.stack.push(5); return MoveAction{};
    case Instruction::PushSix: ip.stack.push(6); return MoveAction{};
    case Instruction::PushSeven: ip.stack.push(7); return MoveAction{};
    case Instruction::PushEight: ip.stack.push(8); return MoveAction{};
    case Instruction::PushNiner: ip.stack.push(9); return MoveAction{};
    case Instruction::Duplicate: ip.stack.push(ip.stack.peek()); return MoveAction{};
    case Instruction::JumpOver: std::unreachable();
    case Instruction::GoWest: {
        ip.delta[0] = WEST[0];
        ip.delta[1] = WEST[1];
        return MoveAction{};
    }
    case Instruction::Execute: ip.reflect(); return MoveAction{};
    case Instruction::GoEast: {
        ip.delta[0] = EAST[0];
        ip.delta[1] = EAST[1];
        return MoveAction{};
    }
    case Instruction::GoAway: ip.reflect(); return MoveAction{};
    case Instruction::Stop: ip.alive = false; return KillAction{};
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
    case Instruction::Z: ip.reflect(); return MoveAction{};
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
    case Instruction::PushTen: ip.stack.push(10); return MoveAction{};
    case Instruction::PushEleven: ip.stack.push(11); return MoveAction{};
    case Instruction::PushTwelve: ip.stack.push(12); return MoveAction{};
    case Instruction::PushThirteen: ip.stack.push(13); return MoveAction{};
    case Instruction::PushFourteen: ip.stack.push(14); return MoveAction{};
    case Instruction::PushFifteen: ip.stack.push(15); return MoveAction{};
    case Instruction::Get: {
        const auto y = ip.stack.pop();
        const auto x = ip.stack.pop();
        ip.stack.push(fungespace.get(x, y));
        return MoveAction{};
    }
    case Instruction::GoHigh: ip.reflect(); return MoveAction{};
    case Instruction::InputFile: ip.reflect(); return MoveAction{};
    case Instruction::JumpForward: ip.reflect(); return MoveAction{};
    case Instruction::Iterate: {
        const auto n = ip.stack.pop();

        std::int64_t saved_pos[2] = {ip.pos[0], ip.pos[1]};
        step_to_next_instruction(fungespace, ip, '\0', false);

        if (n == 0)
            return MoveAction{};

        const auto iter_ins = fungespace.get(ip.pos[0], ip.pos[1]);
        ip.pos[0] = saved_pos[0];
        ip.pos[1] = saved_pos[1];

        std::vector<InstructionAction> ret{};
        for (std::int64_t i = 0; i < n; ++i)
            ret.emplace_back(perform_instruction(static_cast<Instruction>(iter_ins), fungespace, ip));

        return IterAction{ret};
    }
    case Instruction::GoLow: ip.reflect(); return MoveAction{};
    case Instruction::HighLow: ip.reflect(); return MoveAction{};
    case Instruction::ClearStack: ip.reflect(); return MoveAction{};
    case Instruction::OutputFile: ip.reflect(); return MoveAction{};
    case Instruction::Put: {
        const auto y = ip.stack.pop();
        const auto x = ip.stack.pop();
        const auto v = ip.stack.pop();
        fungespace.put(x, y, v);
        return MoveAction{};
    }
    case Instruction::Quit: return QuitAction{static_cast<int>(ip.stack.pop())};
    case Instruction::Reflect: ip.reflect(); return MoveAction{};
    case Instruction::StoreCharacter: ip.reflect(); return MoveAction{};
    case Instruction::Split: ip.reflect(); return MoveAction{};
    case Instruction::StackUnderStack: ip.reflect(); return MoveAction{};
    case Instruction::GoSouth: {
        ip.delta[0] = SOUTH[0];
        ip.delta[1] = SOUTH[1];
        return MoveAction{};
    }
    case Instruction::Compare: ip.reflect(); return MoveAction{};
    case Instruction::AbsoluteDelta: ip.reflect(); return MoveAction{};
    case Instruction::GetSysinfo: ip.reflect(); return MoveAction{};
    case Instruction::NoOperation: ip.reflect(); return MoveAction{};
    case Instruction::BeginBlock: ip.reflect(); return MoveAction{};
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
    case Instruction::EndBlock: ip.reflect(); return MoveAction{};
    case Instruction::InputCharacter: ip.reflect(); return MoveAction{};
    default: {
        fmt::println("Unknown instruction: {}/{}, reflecting", static_cast<std::int64_t>(ins), static_cast<char>(ins));
        ip.reflect();
        return MoveAction{};
    }
    }
    std::unreachable();
}

void step_wrap(const Fungespace &fungespace, InstructionPointer &ip) {
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

void step_to_next_instruction(
        const Fungespace &fungespace, InstructionPointer &ip, const Cell prev_ins, bool start_skipping) {
    bool skipping = start_skipping;
    do {
        step_wrap(fungespace, ip);
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
