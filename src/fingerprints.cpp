#include "fingerprints.hpp"
#include <unordered_map>
#include "fingerprints/modu.hpp"
#include "fingerprints/roma.hpp"
#include "instruction_stack.hpp"

const std::unordered_map<std::int64_t, const Fingerprint &> &registry() {
    static std::unordered_map<std::int64_t, const Fingerprint &> registry{
            {MODU.id, MODU},
            {ROMA.id, ROMA},
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
