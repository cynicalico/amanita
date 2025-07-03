#include <fmt/format.h>
#include "argparse.hpp"
#include "editor.hpp"
#include "interpreter.hpp"

int main(const int argc, char *argv[]) {
    argparse::ArgumentParser program("amanita", "1.0.0");

    program.add_argument("program").help("Funge-98 program to run");

    program.add_argument("--gui").help("Open GUI debugger").flag();

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

    if (program["--gui"] == true) {
        mizu::Engine("amanita", {500, 500}, [](auto &) {}).mainloop<Editor>(args[0], args);
    } else {
        try {
            auto i = Interpreter(args[0]);
            i.run(args);
        } catch (const std::exception &e) {
            fmt::println(stderr, "Exception during execution: {}", e.what());
            return 1;
        }
    }

    return EXIT_SUCCESS;
}
