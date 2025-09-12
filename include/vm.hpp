#pragma once

#include "action.hpp"
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

private:
    std::vector<InstructionPointer *> next_ips_buf_{};
    std::vector<Action> actions_buf_{};
};
} // namespace amanita
