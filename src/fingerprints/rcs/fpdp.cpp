#include "fingerprints/rcs/fpdp.hpp"
#include <fmt/format.h>
#include "instruction_pointer.hpp"

namespace fingerprints::fpdp {
union Union {
    double d;
    Cell i;
};
static_assert(sizeof(Union) == sizeof(double), "double/Cell union must be same byte size");

Union pop(InstructionPointer &ip) {
    Union u;
    u.i = ip.pop();
    return u;
}

void push(InstructionPointer &ip, Union u) { ip.push(u.i); }
} // namespace fingerprints::fpdp

InstructionAction fingerprints::fpdp::add(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a + b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::sin(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::sin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::cos(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::cos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::div(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a / b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::asin(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::asin(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::itof(State &, Fungespace &, InstructionPointer &ip) {
    const auto i = ip.pop();

    Union u;
    u.d = static_cast<double>(i);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::atan(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::atan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::acos(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::acos(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::ftoi(State &, Fungespace &, InstructionPointer &ip) {
    const auto u = pop(ip);
    ip.push(static_cast<Cell>(std::round(u.d)));

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::ln(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::log(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::log10(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::log10(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::mul(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a * b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::neg(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = -a;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::print(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    fmt::print("{:.6f} ", a);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::sqrt(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::sqrt(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::parse(State &, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    try {
        Union u;
        u.d = std::stod(s);
        push(ip, u);
    } catch (const std::exception &) { ip.reflect(); }

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::sub(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = a - b;
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::tan(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::tan(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::abs(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::abs(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::exp(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double a = u.d;

    u.d = std::exp(a);
    push(ip, u);

    return MoveAction{};
}

InstructionAction fingerprints::fpdp::pow(State &, Fungespace &, InstructionPointer &ip) {
    auto u = pop(ip);
    const double b = u.d;
    u = pop(ip);
    const double a = u.d;

    u.d = std::pow(a, b);
    push(ip, u);

    return MoveAction{};
}
