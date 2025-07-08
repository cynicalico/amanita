#include "fingerprints/rcs/fpsp.hpp"
#include <fmt/format.h>
#include "instruction_pointer.hpp"

namespace fingerprints::fpsp {
union SpUnion {
    float f;
    std::int32_t i;
};
static_assert(sizeof(SpUnion) == sizeof(float), "float/std::int32_t union must be same byte size");

SpUnion pop(InstructionPointer &ip) {
    SpUnion u;
    u.i = static_cast<std::int32_t>(ip.pop());
    return u;
}

void push(InstructionPointer &ip, SpUnion u) { ip.push(u.i); }
} // namespace fingerprints::fpsp

InstructionAction fingerprints::fpsp::add(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a + b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::sin(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::sin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::cos(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::cos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::div(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a / b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::asin(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::asin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::itof(Fungespace &, InstructionPointer &ip) {
    const auto i = static_cast<std::int32_t>(ip.pop());

    SpUnion u;
    u.f = static_cast<float>(i);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::atan(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::atan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::acos(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::acos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::ftoi(Fungespace &, InstructionPointer &ip) {
    const auto u = pop(ip);
    ip.push(static_cast<std::int32_t>(std::round(u.f)));

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::ln(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::log(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::log10(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::log10(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::mul(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a * b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::neg(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = -a;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::print(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    fmt::print("{:.6f} ", a);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::sqrt(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::sqrt(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::parse(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    try {
        SpUnion u;
        u.f = std::stof(s);
        push(ip, u);
    } catch (const std::exception &) { ip.reflect(); }

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::sub(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a - b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::tan(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::tan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::abs(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::abs(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::exp(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::exp(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::pow(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = std::pow(a, b);
    push(ip, u);

    return MoveAction{};
}
