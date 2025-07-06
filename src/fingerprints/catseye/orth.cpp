#include "fingerprints/catseye/orth.hpp"
#include <fmt/format.h>
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

InstructionAction orth::bitwise_and(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a & b);
    return MoveAction{};
}

InstructionAction orth::bitwise_or(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a | b);
    return MoveAction{};
}

InstructionAction orth::bitwise_exor(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a ^ b);
    return MoveAction{};
}

InstructionAction orth::change_x(Fungespace &, InstructionPointer &ip) {
    ip.pos.x = ip.pop();
    return MoveAction{};
}

InstructionAction orth::change_y(Fungespace &, InstructionPointer &ip) {
    ip.pos.y = ip.pop();
    return MoveAction{};
}

InstructionAction orth::change_dx(Fungespace &, InstructionPointer &ip) {
    ip.delta.x = ip.pop();
    return MoveAction{};
}

InstructionAction orth::change_dy(Fungespace &, InstructionPointer &ip) {
    ip.delta.y = ip.pop();
    return MoveAction{};
}

InstructionAction orth::ortho_get(Fungespace &fungespace, InstructionPointer &ip) {
    const auto pos = ip.pop_offset_vec();
    ip.push(fungespace.get(pos.y, pos.x));
    return MoveAction{};
}

InstructionAction orth::ortho_put(Fungespace &fungespace, InstructionPointer &ip) {
    const auto pos = ip.pop_offset_vec();
    const auto v = ip.pop();
    fungespace.put(pos.y, pos.x, v);
    return MoveAction{};
}

InstructionAction orth::ramp_if_zero(Fungespace &, InstructionPointer &ip) {
    if (ip.pop() == 0) ip.step();
    return MoveAction{};
}

InstructionAction orth::output_string(Fungespace &, InstructionPointer &ip) {
    Cell c = 0;
    do {
        c = ip.pop();
        if (c != 0) fmt::print("{}", static_cast<char>(c));
    } while (c != 0);
    return MoveAction{};
}
