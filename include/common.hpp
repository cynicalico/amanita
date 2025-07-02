#ifndef AMANITA_COMMON_HPP
#define AMANITA_COMMON_HPP

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <variant>
#include "instructions.hpp"

constexpr std::int64_t SOUTH[2] = {0, 1};
constexpr std::int64_t EAST[2] = {1, 0};
constexpr std::int64_t NORTH[2] = {0, -1};
constexpr std::int64_t WEST[2] = {-1, 0};

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

class Fungespace;
class InstructionPointer;
using InstructionFunc = std::function<InstructionAction(Fungespace &fungespace, InstructionPointer &)>;

struct Fingerprint {
    std::int64_t id;
    std::unordered_map<Instruction, InstructionFunc> fns;
};

#endif // AMANITA_COMMON_HPP
