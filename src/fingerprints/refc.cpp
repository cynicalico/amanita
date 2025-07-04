#include "fingerprints/refc.hpp"
#include <array>
#include <vector>
#include "instruction_pointer.hpp"

std::vector<std::array<std::int64_t, 2>> &references();

InstructionAction refc::reference(Fungespace &, InstructionPointer &ip) {
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();

    auto &r = references();
    r.push_back({x, y});
    ip.stack.push(r.size() - 1);

    return MoveAction{};
}

InstructionAction refc::dereference(Fungespace &, InstructionPointer &ip) {
    if (const auto i = ip.stack.pop(); i < 0) {
        ip.reflect();
    } else if (const auto &r = references(); r.size() <= i) {
        ip.reflect();
    } else {
        ip.stack.push(r[static_cast<std::size_t>(i)][0]);
        ip.stack.push(r[static_cast<std::size_t>(i)][1]);
    }
    return MoveAction{};
}

std::vector<std::array<std::int64_t, 2>> &references() {
    static std::vector<std::array<std::int64_t, 2>> references{};
    return references;
}
