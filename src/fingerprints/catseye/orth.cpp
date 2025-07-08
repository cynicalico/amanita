#include "fingerprints/catseye/orth.hpp"
#include <fmt/format.h>
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

InstructionAction fingerprints::orth::bitwise_and(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a & b);
    return MoveAction{};
}

InstructionAction fingerprints::orth::bitwise_or(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a | b);
    return MoveAction{};
}

InstructionAction fingerprints::orth::bitwise_exor(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a ^ b);
    return MoveAction{};
}

InstructionAction fingerprints::orth::change_x(State &, Fungespace &, InstructionPointer &ip) {
    ip.pos.x = ip.pop();
    return MoveAction{};
}

InstructionAction fingerprints::orth::change_y(State &, Fungespace &, InstructionPointer &ip) {
    ip.pos.y = ip.pop();
    return MoveAction{};
}

InstructionAction fingerprints::orth::change_dx(State &, Fungespace &, InstructionPointer &ip) {
    ip.delta.x = ip.pop();
    return MoveAction{};
}

InstructionAction fingerprints::orth::change_dy(State &, Fungespace &, InstructionPointer &ip) {
    ip.delta.y = ip.pop();
    return MoveAction{};
}

InstructionAction fingerprints::orth::ortho_get(State &, Fungespace &fungespace, InstructionPointer &ip) {
    const auto pos = ip.pop_offset_vec();
    ip.push(fungespace.get(pos.y, pos.x));
    return MoveAction{};
}

InstructionAction fingerprints::orth::ortho_put(State &, Fungespace &fungespace, InstructionPointer &ip) {
    const auto pos = ip.pop_offset_vec();
    const auto v = ip.pop();
    fungespace.put(pos.y, pos.x, v);
    return MoveAction{};
}

InstructionAction fingerprints::orth::ramp_if_zero(State &, Fungespace &, InstructionPointer &ip) {
    if (ip.pop() == 0) ip.step();
    return MoveAction{};
}

InstructionAction fingerprints::orth::output_string(State &, Fungespace &, InstructionPointer &ip) {
    Cell c = 0;
    do {
        c = ip.pop();
        if (c != 0) fmt::print("{}", static_cast<char>(c));
    } while (c != 0);
    return MoveAction{};
}
