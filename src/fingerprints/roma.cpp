#include "fingerprints/roma.hpp"
#include "instruction_pointer.hpp"

InstructionAction roma::push_100(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(100);
    return MoveAction{};
}

InstructionAction roma::push_500(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(500);
    return MoveAction{};
}

InstructionAction roma::push_1(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(1);
    return MoveAction{};
}

InstructionAction roma::push_50(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(50);
    return MoveAction{};
}

InstructionAction roma::push_1000(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(1000);
    return MoveAction{};
}

InstructionAction roma::push_5(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(5);
    return MoveAction{};
}

InstructionAction roma::push_10(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(10);
    return MoveAction{};
}
