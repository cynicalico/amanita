#include <fmt/format.h>
#include "interpreter.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fmt::println("Usage: amanita <program>");
        return 1;
    }

    try {
        auto i = Interpreter(argv[1]);
        i.run();
    } catch (std::runtime_error &e) {
        fmt::println("Exception: {}", e.what());
        return 1;
    }

    return 0;
}
