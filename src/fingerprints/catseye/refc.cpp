#include "fingerprints/catseye/refc.hpp"
#include <array>
#include <vector>
#include "instruction_pointer.hpp"

std::vector<Vec> &references();

InstructionAction refc::reference(Fungespace &, InstructionPointer &ip) {
    auto &r = references();
    r.push_back(ip.pop_vec());
    ip.push(r.size() - 1);
    return MoveAction{};
}

InstructionAction refc::dereference(Fungespace &, InstructionPointer &ip) {
    if (const auto i = ip.pop(); i < 0)
        ip.reflect();
    else if (const auto &r = references(); r.size() <= i)
        ip.reflect();
    else
        ip.push_vec(r[static_cast<std::size_t>(i)]);
    return MoveAction{};
}

std::vector<Vec> &references() {
    static std::vector<Vec> references{};
    return references;
}
