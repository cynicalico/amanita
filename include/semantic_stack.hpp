#pragma once

#include "instruction.hpp"
#include "semantic.hpp"

#include <array>
#include <vector>

namespace amanita {
class SemanticStack {
public:
    SemanticStack();

    void perform(Instruction ins, State *state, InstructionPointer *ip, std::vector<Action> &actions);

private:
    std::array<std::vector<Semantic>, 127> semantics_{};

    void populate_default_fns_();
};
} // namespace amanita
