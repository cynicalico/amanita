#pragma once

#include "action.hpp"
#include "state.hpp"

#include <filesystem>
#include <memory>

namespace amanita {
class VM {
public:
    std::filesystem::path src_path;
    std::unique_ptr<State> state;
    int exit_code{0};

    VM();
    VM(std::filesystem::path src_path, std::vector<std::string> args, std::vector<std::filesystem::path> include_paths);

    void step();
    void run();

private:
    std::vector<std::unique_ptr<InstructionPointer>> next_ips_buf_{};
    std::vector<Action> actions_buf_{};
};
} // namespace amanita
