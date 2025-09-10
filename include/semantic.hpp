#pragma once

#include "action.hpp"
#include "state.hpp"

#include <functional>
#include <vector>

namespace amanita {
using Semantic = std::function<void(State *, InstructionPointer *, std::vector<Action> &)>;
} // namespace amanita
