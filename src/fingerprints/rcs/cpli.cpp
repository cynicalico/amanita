#include "fingerprints/rcs/cpli.hpp"
#include <cmath>
#include <fmt/format.h>
#include "instruction_pointer.hpp"

InstructionAction fingerprints::cpli::add(Fungespace &, InstructionPointer &ip) {
    const auto bi = ip.pop();
    const auto br = ip.pop();
    const auto ai = ip.pop();
    const auto ar = ip.pop();
    ip.push(ar + br);
    ip.push(ai + bi);
    return MoveAction{};
}

InstructionAction fingerprints::cpli::div(Fungespace &, InstructionPointer &ip) {
    const auto bi = ip.pop();
    const auto br = ip.pop();
    const auto ai = ip.pop();
    const auto ar = ip.pop();
    const auto denom = br * br + bi * bi;
    ip.push((ar * br + ai * bi) / denom);
    ip.push((ai * br - ar * bi) / denom);
    return MoveAction{};
}

InstructionAction fingerprints::cpli::mul(Fungespace &, InstructionPointer &ip) {
    const auto bi = ip.pop();
    const auto br = ip.pop();
    const auto ai = ip.pop();
    const auto ar = ip.pop();
    ip.push(ar * br - ai * bi);
    ip.push(ar * bi + ai * br);
    return MoveAction{};
}

InstructionAction fingerprints::cpli::print(Fungespace &, InstructionPointer &ip) {
    const auto i = ip.pop();
    const auto r = ip.pop();
    fmt::print("{}{}{}i ", r, i < 0 ? "-" : "+", std::abs(i));
    return MoveAction{};
}

InstructionAction fingerprints::cpli::sub(Fungespace &, InstructionPointer &ip) {
    const auto bi = ip.pop();
    const auto br = ip.pop();
    const auto ai = ip.pop();
    const auto ar = ip.pop();
    ip.push(ar - br);
    ip.push(ai - bi);
    return MoveAction{};
}

InstructionAction fingerprints::cpli::abs(Fungespace &, InstructionPointer &ip) {
    const auto i = ip.pop();
    const auto r = ip.pop();
    ip.push(std::sqrt(r * r + i * i));
    return MoveAction{};
}
