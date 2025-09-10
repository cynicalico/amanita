#pragma once

#include <variant>
#include <vector>

namespace amanita {
class InstructionPointer;

struct ActionIter;

struct ActionKill {
    InstructionPointer *ip;
};

struct ActionMove {
    InstructionPointer *ip;
};

struct ActionSplit {
    InstructionPointer *ip;
};

struct ActionQuit {
    int exit_code;
};

using Action = std::variant<ActionIter, ActionKill, ActionMove, ActionSplit, ActionQuit>;

struct ActionIter {
    std::vector<Action> actions;
};

/**********
 * HELPER *
 **********/

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
} // namespace amanita
