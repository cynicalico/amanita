#pragma once

#include "instruction.hpp"
#include "semantic.hpp"

#include <vector>

namespace amanita {
class SemanticStack {
public:
    SemanticStack();

    void perform(Instruction ins, State *state, InstructionPointer *ip, std::vector<Action> &actions);

private:
    std::vector<std::vector<Semantic>> semantics_{};

    void populate_default_fns_();
};
} // namespace amanita
