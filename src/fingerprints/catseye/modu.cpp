#include "fingerprints/catseye/modu.hpp"
#include "instruction_pointer.hpp"

InstructionAction fingerprints::modu::signed_result_modulo(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    if (b == 0) {
        ip.push(0);
    } else {
        auto c = a / b;
        if (c < 0) c -= 1;
        const auto v = a - c * b;
        ip.push(v);
    }
    return MoveAction{};
}

InstructionAction fingerprints::modu::sam_holden_unsigned_result_modulo(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = std::abs(ip.pop());
    const auto a = std::abs(ip.pop());
    ip.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}

InstructionAction fingerprints::modu::c_language_integer_remainder(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(b == 0 ? 0 : a % b);
    return MoveAction{};
}
