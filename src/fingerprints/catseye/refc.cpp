#include "fingerprints/catseye/refc.hpp"
#include <vector>
#include "instruction_pointer.hpp"

InstructionAction fingerprints::refc::reference(State &state, Fungespace &, InstructionPointer &ip) {
    state.refc.references.push_back(ip.pop_vec());
    ip.push(state.refc.references.size() - 1);
    return MoveAction{};
}

InstructionAction fingerprints::refc::dereference(State &state, Fungespace &, InstructionPointer &ip) {
    if (const auto i = ip.pop(); i < 0) ip.reflect();
    else if (state.refc.references.size() <= i) ip.reflect();
    else ip.push_vec(state.refc.references[static_cast<std::size_t>(i)]);
    return MoveAction{};
}
