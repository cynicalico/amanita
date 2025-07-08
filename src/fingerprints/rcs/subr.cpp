#include "fingerprints/rcs/subr.hpp"
#include "instruction_pointer.hpp"

Vec pop_offset_vec(InstructionPointer &ip) {
    if (ip.relative_mode) return ip.pop_offset_vec();
    return ip.pop_vec();
}

InstructionAction fingerprints::subr::set_absolute_mode(Fungespace &, InstructionPointer &ip) {
    ip.relative_mode = false;
    return MoveAction{};
}

InstructionAction fingerprints::subr::call(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto dst = pop_offset_vec(ip);

    for (Index i = 0; i < n; ++i) ip.call_stack.push_back(ip.pop());

    ip.push_vec(ip.pos);
    ip.push_vec(ip.delta);
    for (Index i = 0; i < n; ++i) {
        ip.push(ip.call_stack.back());
        ip.call_stack.pop_back();
    }

    ip.pos = dst;
    ip.delta = EAST;

    return MoveAction{};
}

InstructionAction fingerprints::subr::jump(Fungespace &, InstructionPointer &ip) {
    ip.pos = pop_offset_vec(ip);
    ip.delta = EAST;
    return MoveAction{};
}

InstructionAction fingerprints::subr::set_relative_mode(Fungespace &, InstructionPointer &ip) {
    ip.relative_mode = true;
    return MoveAction{};
}

InstructionAction fingerprints::subr::ret(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();

    for (Index i = 0; i < n; ++i) ip.call_stack.push_back(ip.pop());

    ip.delta = ip.pop_vec();
    ip.pos = ip.pop_vec();

    for (Index i = 0; i < n; ++i) {
        ip.push(ip.call_stack.back());
        ip.call_stack.pop_back();
    }

    return MoveAction{};
}
