#include "fingerprints.hpp"
#include <unordered_map>
#include "instruction_stack.hpp"

#include "fingerprints/modu.hpp"
#include "fingerprints/null.hpp"
#include "fingerprints/roma.hpp"

const std::unordered_map<std::int64_t, const Fingerprint &> &registry() {
    static std::unordered_map<std::int64_t, const Fingerprint &> registry{
            {FNG_MODU.id, FNG_MODU},
            {FNG_NULL.id, FNG_NULL},
            {FNG_ROMA.id, FNG_ROMA},
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
        for (const auto &[ins, _]: it->second.fns)
            instruction_stack.fns[static_cast<std::int64_t>(ins)].pop_back();
        return true;
    }

    return false;
}
