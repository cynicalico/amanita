#include <fmt/format.h>
#include "argparse.hpp"
#include "interpreter.hpp"

int main(const int argc, char *argv[]) {
    argparse::ArgumentParser program("amanita", "1.0.0");

    program.add_argument("program").help("Funge-98 program to run");
    program.add_argument("--gui").help("Open GUI debugger").flag();

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &e) {
        fmt::println(stderr, "{}", e.what());
        fmt::println("");
        fmt::print(stderr, "{}", program.help().str());
        return EXIT_FAILURE;
    }

    if (program["--gui"] == true) {
        fmt::println("GUI coming soon!");
    } else {
        try {
            auto i = Interpreter(program.get<std::string>("program"));
            i.run();
        } catch (const std::exception &e) {
            fmt::println(stderr, "Exception during execution: {}", e.what());
            return 1;
        }
    }

    return EXIT_SUCCESS;
}
