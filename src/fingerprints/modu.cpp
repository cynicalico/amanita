#include "fingerprints/modu.hpp"
#include "instruction_pointer.hpp"

InstructionAction modu_m(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    if (b == 0) {
        ip.stack.push(0);
    } else {
        auto c = a / b;
        if (c < 0)
            c -= 1;
        const auto v = a - c * b;
        ip.stack.push(v);
    }
    return MoveAction{};
}

InstructionAction modu_u(Fungespace &, InstructionPointer &ip) {
    const auto b = std::abs(ip.stack.pop());
    const auto a = std::abs(ip.stack.pop());
    ip.stack.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}

InstructionAction modu_r(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}
