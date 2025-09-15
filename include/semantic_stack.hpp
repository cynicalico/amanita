#pragma once

#include "instruction.hpp"
#include "semantic.hpp"

#include <array>
#include <optional>
#include <vector>

namespace amanita {
class SemanticStack {
public:
    SemanticStack();

    Semantic operator[](Instruction ins);
    std::optional<Semantic> at(Instruction ins);

    bool load_fingerprint(std::int64_t fingerprint);
    bool unload_fingerprint(std::int64_t fingerprint);

private:
    std::array<std::vector<Semantic>, 127> semantics_{};

    void populate_default_fns_();
};
} // namespace amanita
