#include "fingerprints.hpp"
#include <ranges>
#include <unordered_map>
#include "instruction_stack.hpp"

#include "fingerprints/catseye/hrti.hpp"
#include "fingerprints/catseye/mode.hpp"
#include "fingerprints/catseye/modu.hpp"
#include "fingerprints/catseye/null.hpp"
#include "fingerprints/catseye/orth.hpp"
#include "fingerprints/catseye/perl.hpp"
#include "fingerprints/catseye/refc.hpp"
#include "fingerprints/catseye/roma.hpp"
#include "fingerprints/catseye/toys.hpp"
#include "fingerprints/rcs/dirf.hpp"
#include "fingerprints/rcs/evar.hpp"
#include "fingerprints/rcs/file.hpp"

const std::unordered_map<std::int64_t, const Fingerprint &> &registry() {
    static std::unordered_map<std::int64_t, const Fingerprint &> registry{
            // Cat's Eye
            {hrti::FINGERPRINT.id, hrti::FINGERPRINT},
            {mode::FINGERPRINT.id, mode::FINGERPRINT},
            {modu::FINGERPRINT.id, modu::FINGERPRINT},
            {null::FINGERPRINT.id, null::FINGERPRINT},
            {orth::FINGERPRINT.id, orth::FINGERPRINT},
            {perl::FINGERPRINT.id, perl::FINGERPRINT},
            {refc::FINGERPRINT.id, refc::FINGERPRINT},
            {roma::FINGERPRINT.id, roma::FINGERPRINT},
            {toys::FINGERPRINT.id, toys::FINGERPRINT},
            // RCS
            {dirf::FINGERPRINT.id, dirf::FINGERPRINT},
            {evar::FINGERPRINT.id, evar::FINGERPRINT},
            {file::FINGERPRINT.id, file::FINGERPRINT},
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
