#include "fingerprints/rcs/frth.hpp"
#include "instruction_pointer.hpp"

InstructionAction fingerprints::frth::depth(State &, Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction fingerprints::frth::roll(State &, Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction fingerprints::frth::over(State &, Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction fingerprints::frth::pick(State &, Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}

InstructionAction fingerprints::frth::rot(State &, Fungespace &, InstructionPointer &ip) {
    ip.reflect(); // TODO
    return MoveAction{};
}
