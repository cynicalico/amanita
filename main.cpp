#include "editor.hpp"
#include "vm.hpp"

#include <fmt/format.h>
#include "thirdparty/argparse.hpp"

#include <memory>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("amanita", "1.0.0");

    argparse::ArgumentParser run_command("run");
    run_command.add_description("Run Funge-98 program");
    run_command.add_argument("program").help("Funge-98 program to run").required();
    run_command.add_argument("-I", "--include")
            .help("Additional paths to search for `i`")
            .default_value<std::vector<std::string>>({"."})
            .append();
    run_command.add_argument("-t", "--time").help("Time execution").default_value(false).flag();
    run_command.add_argument("args").help("Arguments passed to program").remaining();

    argparse::ArgumentParser edit_command("edit");
    edit_command.add_description("Edit Funge-98 program");
    edit_command.add_argument("-p", "--program").help("Funge-98 program to edit");

    program.add_subparser(run_command);
    program.add_subparser(edit_command);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &e) {
        fmt::println(stderr, "{}", e.what());
        fmt::println("");
        fmt::print(stderr, "{}", program.help().str());
        return 1;
    }

    if (program.is_subcommand_used("run")) {
        std::vector args{run_command.get<std::string>("program")};
        try {
            args.insert_range(args.end(), run_command.get<std::vector<std::string>>("args"));
        } catch (std::logic_error &) {
            // we didn't get any args
        }

        std::vector include_paths = {std::filesystem::current_path()};

        std::vector<std::string> buf;
        try {
            buf = run_command.get<std::vector<std::string>>("--include");
        } catch (std::logic_error &) {
            // we didn't get any additional include paths
        }
        for (const auto &path: buf)
            include_paths.emplace_back(path);

        const auto vm = std::make_unique<amanita::VM>(args[0], args, include_paths);

        const auto t1 = std::chrono::steady_clock::now().time_since_epoch().count();
        vm->run();
        const auto t2 = std::chrono::steady_clock::now().time_since_epoch().count();

        if (run_command.get<bool>("time"))
            fmt::println("\nExecution time: {:.2f}ms", (static_cast<double>(t2) - static_cast<double>(t1)) / 1'000'000);

        return vm->state->exit_code;
    }

    if (program.is_subcommand_used("edit")) {
        std::unique_ptr<amanita::VM> vm;
        try {
            std::vector args = {edit_command.get<std::string>("--program")};
            std::vector include_paths = {std::filesystem::current_path()};
            vm = std::make_unique<amanita::VM>(args[0], args, include_paths);
        } catch (std::logic_error &) {
            vm = std::make_unique<amanita::VM>();
        }

        return std::make_unique<amanita::Editor>(std::move(vm))->mainloop();
    }

    return 0;
}
