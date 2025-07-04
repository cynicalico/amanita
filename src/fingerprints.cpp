#include "fingerprints.hpp"
#include <ranges>
#include <unordered_map>
#include "instruction_stack.hpp"

#include "fingerprints/dirf.hpp"
#include "fingerprints/evar.hpp"
#include "fingerprints/file.hpp"
#include "fingerprints/hrti.hpp"
#include "fingerprints/mode.hpp"
#include "fingerprints/modu.hpp"
#include "fingerprints/null.hpp"
#include "fingerprints/orth.hpp"
#include "fingerprints/refc.hpp"
#include "fingerprints/roma.hpp"
#include "fingerprints/toys.hpp"

const std::unordered_map<std::int64_t, const Fingerprint &> &registry() {
    static std::unordered_map<std::int64_t, const Fingerprint &> registry{
            {dirf::FINGERPRINT.id, dirf::FINGERPRINT},
            {evar::FINGERPRINT.id, evar::FINGERPRINT},
            {file::FINGERPRINT.id, file::FINGERPRINT},
            {hrti::FINGERPRINT.id, hrti::FINGERPRINT},
            {mode::FINGERPRINT.id, mode::FINGERPRINT},
            {modu::FINGERPRINT.id, modu::FINGERPRINT},
            {null::FINGERPRINT.id, null::FINGERPRINT},
            {orth::FINGERPRINT.id, orth::FINGERPRINT},
            {refc::FINGERPRINT.id, refc::FINGERPRINT},
            {roma::FINGERPRINT.id, roma::FINGERPRINT},
            {toys::FINGERPRINT.id, toys::FINGERPRINT},
    };
    return registry;
}

bool load_fingerprint(InstructionStack &instruction_stack, std::int64_t fingerprint) {
    const auto &r = registry();
    if (const auto it = r.find(fingerprint); it != r.end()) {
        for (const auto &[ins, fn]: it->second.fns) {
            instruction_stack.fns[static_cast<std::int64_t>(ins)].push_back(fn);
            instruction_stack.loaded_fingerprints[static_cast<std::size_t>(ins) - 65].push_back(it->second.name);
        }
        return true;
    }

    return false;
}

bool unload_fingerprint(InstructionStack &instruction_stack, std::int64_t fingerprint) {
    const auto &r = registry();
    if (const auto it = r.find(fingerprint); it != r.end()) {
        for (const auto &ins: it->second.fns | std::views::keys) {
            instruction_stack.fns[static_cast<std::int64_t>(ins)].pop_back();
            instruction_stack.loaded_fingerprints[static_cast<std::size_t>(ins) - 65].pop_back();
        }
        return true;
    }

    return false;
}
