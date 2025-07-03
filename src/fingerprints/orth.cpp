#include "fingerprints/orth.hpp"
#include <fmt/format.h>
#include "instruction_pointer.hpp"

InstructionAction orth_bitwise_and(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a & b);
    return MoveAction{};
}

InstructionAction orth_bitwise_or(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a | b);
    return MoveAction{};
}

InstructionAction orth_bitwise_exor(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    ip.stack.push(a ^ b);
    return MoveAction{};
}

InstructionAction orth_change_x(Fungespace &, InstructionPointer &ip) {
    ip.pos[0] = ip.stack.pop();
    return MoveAction{};
}

InstructionAction orth_change_y(Fungespace &, InstructionPointer &ip) {
    ip.pos[1] = ip.stack.pop();
    return MoveAction{};
}

InstructionAction orth_change_dx(Fungespace &, InstructionPointer &ip) {
    ip.delta[0] = ip.stack.pop();
    return MoveAction{};
}

InstructionAction orth_change_dy(Fungespace &, InstructionPointer &ip) {
    ip.delta[1] = ip.stack.pop();
    return MoveAction{};
}

InstructionAction orth_ortho_get(Fungespace &fungespace, InstructionPointer &ip) {
    const auto x = ip.stack.pop();
    const auto y = ip.stack.pop();
    ip.stack.push(fungespace.get(x, y));
    return MoveAction{};
}

InstructionAction orth_ortho_put(Fungespace &fungespace, InstructionPointer &ip) {
    const auto x = ip.stack.pop();
    const auto y = ip.stack.pop();
    const auto v = ip.stack.pop();
    fungespace.put(x, y, v);
    return MoveAction{};
}

InstructionAction orth_ramp_if_zero(Fungespace &, InstructionPointer &ip) {
    if (ip.stack.pop() == 0)
        ip.step();
    return MoveAction{};
}

InstructionAction orth_output_string(Fungespace &, InstructionPointer &ip) {
    Cell c = 0;
    do {
        c = ip.stack.pop();
        if (c != 0)
            fmt::print("{}", static_cast<char>(c));
    } while (c != 0);
    return MoveAction{};
}
