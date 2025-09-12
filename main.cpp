#include "vm.hpp"

#include "argparse.hpp"

#include <fmt/format.h>

#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("amanita", "1.0.0");

    argparse::ArgumentParser run_command("run");
    run_command.add_description("Run Funge-98 program");
    run_command.add_argument("program").help("Funge-98 program to run").required();
    run_command.add_argument("-I", "--include")
            .default_value<std::vector<std::string>>({"."})
            .append()
            .help("Additional paths to search for `i`");
    run_command.add_argument("args").help("Arguments passed to program").remaining();

    program.add_subparser(run_command);

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

        std::vector<std::string> include_paths = {"."};
        try {
            include_paths.insert_range(include_paths.end(), run_command.get<std::vector<std::string>>("--include"));
        } catch (std::logic_error &) {
            // we didn't get any additional include paths
        }

        const auto vm = new amanita::VM(args[0], args);
        vm->run();

        return vm->state->exit_code;
    }

    return 0;
}
