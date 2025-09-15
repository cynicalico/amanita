#pragma once

#include "instruction.hpp"
#include "semantic.hpp"

#include <cstdint>
#include <utility>
#include <vector>

namespace amanita {
struct Fingerprint {
    const char *name;
    std::int64_t id;
    std::vector<std::pair<Instruction, Semantic>> semantics;

    Fingerprint(const char *name, std::initializer_list<std::pair<Instruction, Semantic>> semantics);
};
} // namespace amanita
