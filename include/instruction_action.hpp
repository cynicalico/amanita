#ifndef AMANITA_INSTRUCTION_ACTION_HPP
#define AMANITA_INSTRUCTION_ACTION_HPP

#include <variant>
#include <vector>

struct IterAction;

struct KillAction {};

struct MoveAction {};

struct SplitAction {};

struct QuitAction {
    int exit_code;
};

using InstructionAction = std::variant<IterAction, KillAction, MoveAction, SplitAction, QuitAction>;

struct IterAction {
    std::vector<InstructionAction> actions;
};

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

#endif // AMANITA_INSTRUCTION_ACTION_HPP
