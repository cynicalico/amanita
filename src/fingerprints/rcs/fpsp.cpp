#include "fingerprints/rcs/fpsp.hpp"
#include <fmt/format.h>
#include "instruction_pointer.hpp"

namespace fingerprints::fpsp {
union Union {
    float f;
    std::int32_t i;
};
static_assert(sizeof(Union) == sizeof(float), "float/std::int32_t union must be same byte size");

Union pop(InstructionPointer &ip) {
    Union u;
    u.i = static_cast<std::int32_t>(ip.pop());
    return u;
}

void push(InstructionPointer &ip, Union u) { ip.push(u.i); }
} // namespace fingerprints::fpsp

InstructionAction fingerprints::fpsp::add(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a + b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::sin(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::sin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::cos(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::cos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::div(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a / b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::asin(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::asin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::itof(State &, Fungespace &, InstructionPointer &ip) {
    const auto i = static_cast<std::int32_t>(ip.pop());

    Union u;
    u.f = static_cast<float>(i);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::atan(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::atan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::acos(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::acos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::ftoi(State &, Fungespace &, InstructionPointer &ip) {
    const auto u = pop(ip);
    ip.push(static_cast<std::int32_t>(std::round(u.f)));

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::ln(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::log(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::log10(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::log10(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::mul(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a * b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::neg(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = -a;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::print(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    fmt::print("{:.6f} ", a);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::sqrt(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::sqrt(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::parse(State &, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    try {
        Union u;
        u.f = std::stof(s);
        push(ip, u);
    } catch (const std::exception &) { ip.reflect(); }

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::sub(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = a - b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::tan(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::tan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::abs(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::abs(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::exp(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float a = u.f;

    u.f = std::exp(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpsp::pow(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const float b = u.f;
    u = pop(ip);
    const float a = u.f;

    u.f = std::pow(a, b);
    push(ip, u);

    return MoveAction{};
}
