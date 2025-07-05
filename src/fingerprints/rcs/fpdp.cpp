#include "fingerprints/rcs/fpdp.hpp"
#include <fmt/format.h>
#include "instruction_pointer.hpp"

union DpUnion {
    double d;
    std::int64_t i;
};
static_assert(sizeof(DpUnion) == sizeof(double), "double/std::int64_t union must be same byte size");

DpUnion pop(InstructionPointer &ip) {
    DpUnion u;
    u.i = ip.pop();
    return u;
}

void push(InstructionPointer &ip, DpUnion u) { ip.push(u.i); }

InstructionAction fpdp::add(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a + b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::sin(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::sin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::cos(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::cos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::div(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a / b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::asin(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::asin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::itof(Fungespace &, InstructionPointer &ip) {
    const auto i = ip.pop();

    DpUnion u;
    u.d = static_cast<double>(i);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::atan(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::atan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::acos(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::acos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::ftoi(Fungespace &, InstructionPointer &ip) {
    const auto u = pop(ip);
    ip.push(static_cast<std::int64_t>(std::round(u.d)));

    return MoveAction{};
}

InstructionAction fpdp::ln(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::log(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::log10(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::log10(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::mul(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a * b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::neg(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = -a;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::print(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    fmt::print("{:.6f} ", a);

    return MoveAction{};
}

InstructionAction fpdp::sqrt(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::sqrt(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::parse(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.stack.pop_0gnirts();

    try {
        DpUnion u;
        u.d = std::stod(s);
        push(ip, u);
    } catch (const std::exception &) { ip.reflect(); }

    return MoveAction{};
}

InstructionAction fpdp::sub(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a - b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::tan(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::tan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::abs(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::abs(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::exp(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::exp(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fpdp::pow(Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = std::pow(a, b);
    push(ip, u);

    return MoveAction{};
}
