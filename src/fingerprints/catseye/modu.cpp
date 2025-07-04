#include "fingerprints/catseye/modu.hpp"
#include "instruction_pointer.hpp"

InstructionAction modu::signed_result_modulo(Fungespace &, InstructionPointer &ip) {
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

InstructionAction modu::sam_holden_unsigned_result_modulo(Fungespace &, InstructionPointer &ip) {
    const auto b = std::abs(ip.stack.pop());
    const auto a = std::abs(ip.stack.pop());
    ip.stack.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}

InstructionAction modu::c_language_integer_remainder(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}
