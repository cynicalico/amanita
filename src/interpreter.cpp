#include "interpreter.hpp"
#include <utility>

Interpreter::Interpreter() = default;

Interpreter::Interpreter(const std::filesystem::path &path)
    : fungespace(path) {}

void Interpreter::run(std::vector<std::string> args) {
    this->args = std::move(args);

    std::vector<InstructionPointer> active_list{};
    std::vector<InstructionPointer> inactive_list{};

    active_list.emplace_back(this);

    while (!active_list.empty()) {
        inactive_list.clear();

        for (auto &ip: active_list) {
            Cell ins;
            do {
                ins = fungespace.get(ip.pos.x, ip.pos.y);
                if (!ip.string_mode && (ins == Instruction::Space || ins == Instruction::JumpOver))
                    ip.step_to_next_instruction(fungespace, '\0', ins == Instruction::JumpOver);
                else
                    break;
            } while (true);
            ip.cache_ins = ins;

            auto action = ip.instruction_stack.perform(static_cast<Instruction>(ins), fungespace, ip);
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
            ip.step_to_next_instruction(fungespace, ip.cache_ins, false);
    }
}
