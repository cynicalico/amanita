#include "fingerprints.hpp"
#include <ranges>
#include <unordered_map>
#include "instruction_stack.hpp"

#include "fingerprints/hrti.hpp"
#include "fingerprints/modu.hpp"
#include "fingerprints/null.hpp"
#include "fingerprints/orth.hpp"
#include "fingerprints/refc.hpp"
#include "fingerprints/roma.hpp"
#include "fingerprints/toys.hpp"

const std::unordered_map<std::int64_t, const Fingerprint &> &registry() {
    static std::unordered_map<std::int64_t, const Fingerprint &> registry{
            {FNG_HRTI.id, FNG_HRTI},
            {FNG_MODU.id, FNG_MODU},
            {FNG_NULL.id, FNG_NULL},
            {FNG_ORTH.id, FNG_ORTH},
            {FNG_REFC.id, FNG_REFC},
            {FNG_ROMA.id, FNG_ROMA},
            {FNG_TOYS.id, FNG_TOYS},
    };
    return registry;
}

bool load_fingerprint(InstructionStack &instruction_stack, std::int64_t fingerprint) {
    const auto &r = registry();
    if (const auto it = r.find(fingerprint); it != r.end()) {
        for (const auto &[ins, fn]: it->second.fns)
            instruction_stack.fns[static_cast<std::int64_t>(ins)].push_back(fn);
        return true;
    }

    return false;
}

bool unload_fingerprint(InstructionStack &instruction_stack, std::int64_t fingerprint) {
    const auto &r = registry();
    if (const auto it = r.find(fingerprint); it != r.end()) {
        for (const auto &ins: it->second.fns | std::views::keys)
            instruction_stack.fns[static_cast<std::int64_t>(ins)].pop_back();
        return true;
    }

    return false;
}
