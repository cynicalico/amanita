#pragma once

namespace amanita {
class InstructionPointer;

enum class ActionType { Split };

struct Action {
    ActionType type;
    InstructionPointer *ip;
};
} // namespace amanita
