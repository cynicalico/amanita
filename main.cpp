#include <fmt/format.h>
#include "argparse.hpp"
#include "editor.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

void run(std::unique_ptr<CliArgs> cli_args);

int main(const int argc, char *argv[]) {
    argparse::ArgumentParser program("amanita", "1.0.0");

    program.add_argument("program").help("Funge-98 program to run");

    program.add_argument("--gui").help("Open GUI debugger").flag();

    program.add_argument("--skip")
            .help("Skip forward n ticks at start")
            .default_value(static_cast<std::int64_t>(0))
            .scan<'i', std::int64_t>();

    program.add_argument("args").help("Arguments passed to program").remaining();

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &e) {
        fmt::println(stderr, "{}", e.what());
        fmt::println("");
        fmt::print(stderr, "{}", program.help().str());
        return EXIT_FAILURE;
    }

    std::vector args{program.get<std::string>("program")};
    try {
        args.insert_range(args.end(), program.get<std::vector<std::string>>("args"));
    } catch (std::logic_error &e) {
        // no args
    }
    auto cli_args = std::make_unique<CliArgs>(args);

    if (program["--gui"] == true) {
        mizu::Engine("amanita", {500, 500}, [](auto &) {
        }).mainloop<Editor>(args[0], std::move(cli_args), program.get<std::int64_t>("--skip"));
    } else {
        try {
            run(std::move(cli_args));
        } catch (const std::exception &e) {
            fmt::println(stderr, "Exception during execution: {}", e.what());
            return 1;
        }
    }

    return EXIT_SUCCESS;
}

void run(std::unique_ptr<CliArgs> cli_args) {
    State state{std::move(cli_args)};
    Fungespace fungespace(state.cli_args->args[0]);

    std::vector<InstructionPointer> active_list{};
    std::vector<InstructionPointer> inactive_list{};

    active_list.emplace_back();

    while (!active_list.empty()) {
        inactive_list.clear();

        for (auto &ip: active_list) {
            Cell ins;
            do {
                ins = fungespace.get(ip.pos.x, ip.pos.y);
                if (!ip.string_mode && (ins == Instruction::Space || ins == Instruction::JumpOver))
                    ip.step_to_next_instruction(fungespace, '\0', ins == Instruction::JumpOver);
                else break;
            } while (true);
            ip.cache_ins = ins;

            auto action = ip.instruction_stack.perform(static_cast<Instruction>(ins), state, fungespace, ip);
            std::visit(
                    overloaded{
                            [&](const IterAction &a) {
                                if (!ip.alive) return;

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
        for (auto &ip: active_list) ip.step_to_next_instruction(fungespace, ip.cache_ins, false);
    }

#if defined(MIZU_PLATFORM_WINDOWS)
    if (state.sock.initialized) WSACleanup();
#endif
}
