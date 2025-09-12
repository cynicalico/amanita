#pragma once

#include <string>
#include <vector>

namespace amanita {
class Fungespace;
class InstructionPointer;

enum class Status { Running, Stopped };

struct State {
    Status status;
    int exit_code;
    std::vector<std::string> args;

    Fungespace *fungespace;
    std::vector<InstructionPointer *> ips;
};
} // namespace amanita
