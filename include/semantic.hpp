#pragma once

#include "action.hpp"

#include <functional>
#include <vector>

namespace amanita {
struct State;
class InstructionPointer;

using Semantic = std::function<void(State *, InstructionPointer *, std::vector<Action> &)>;
} // namespace amanita
