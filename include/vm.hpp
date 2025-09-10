#pragma once

#include "state.hpp"

#include <filesystem>

namespace amanita {
class VM {
public:
    std::filesystem::path src_path;
    State *state;
    int exit_code{0};

    VM();
    VM(std::filesystem::path src_path, std::vector<std::string> args);

    void reset();
    void step();
    void run();
};
} // namespace amanita
