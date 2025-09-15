#pragma once

#include "fungespace.hpp"
#include "instruction_pointer.hpp"

#include <memory>
#include <string>
#include <vector>

namespace amanita {
enum class Status { Running, Stopped };

struct State {
    Status status;
    int exit_code;
    std::vector<std::string> args;

    std::unique_ptr<Fungespace> fungespace;
    std::vector<std::unique_ptr<InstructionPointer>> ips;
};
} // namespace amanita
