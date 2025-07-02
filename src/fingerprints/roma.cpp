#include "fingerprints/roma.hpp"
#include "instruction_pointer.hpp"

InstructionAction roma_c(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(100);
    return MoveAction{};
}

InstructionAction roma_d(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(500);
    return MoveAction{};
}

InstructionAction roma_i(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(1);
    return MoveAction{};
}

InstructionAction roma_l(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(50);
    return MoveAction{};
}

InstructionAction roma_m(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(1000);
    return MoveAction{};
}

InstructionAction roma_v(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(5);
    return MoveAction{};
}

InstructionAction roma_x(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(10);
    return MoveAction{};
}
