#include "fingerprints/catseye/roma.hpp"
#include "instruction_pointer.hpp"

InstructionAction fingerprints::roma::push_100(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(100);
    return MoveAction{};
}

InstructionAction fingerprints::roma::push_500(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(500);
    return MoveAction{};
}

InstructionAction fingerprints::roma::push_1(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(1);
    return MoveAction{};
}

InstructionAction fingerprints::roma::push_50(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(50);
    return MoveAction{};
}

InstructionAction fingerprints::roma::push_1000(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(1000);
    return MoveAction{};
}

InstructionAction fingerprints::roma::push_5(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(5);
    return MoveAction{};
}

InstructionAction fingerprints::roma::push_10(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(10);
    return MoveAction{};
}
