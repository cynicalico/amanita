#include "fingerprints/rcs/fixp.hpp"
#include <numbers>
#include "instruction_pointer.hpp"
#include "mizu/util/rng.hpp"

double deg_to_rad(double v);
double rad_to_deg(double v);

InstructionAction fingerprints::fixp::and_(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a & b);
    return MoveAction{};
}

InstructionAction fingerprints::fixp::acos(State &, Fungespace &, InstructionPointer &ip) {
    const auto a = static_cast<double>(ip.pop()) / 10'000.0;
    ip.push(static_cast<Cell>(rad_to_deg(std::acos(a)) * 10'000.0));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::cos(State &, Fungespace &, InstructionPointer &ip) {
    const auto a = static_cast<double>(ip.pop()) / 10'000.0;
    ip.push(static_cast<Cell>(std::cos(deg_to_rad(a)) * 10'000.0));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::rnd(State &, Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    ip.push(mizu::rng::get<Cell>(n));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::sin(State &, Fungespace &, InstructionPointer &ip) {
    const auto a = static_cast<double>(ip.pop()) / 10'000;
    ip.push(static_cast<Cell>(std::sin(deg_to_rad(a)) * 10'000.0));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::asin(State &, Fungespace &, InstructionPointer &ip) {
    const auto a = static_cast<double>(ip.pop()) / 10'000;
    ip.push(static_cast<Cell>(rad_to_deg(std::asin(a)) * 10'000.0));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::neg(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(-ip.pop());
    return MoveAction{};
}

InstructionAction fingerprints::fixp::or_(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a | b);
    return MoveAction{};
}

InstructionAction fingerprints::fixp::mul_pi(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(ip.pop() * std::numbers::pi);
    return MoveAction{};
}

InstructionAction fingerprints::fixp::sqrt(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(std::sqrt(ip.pop()));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::pow(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(std::pow(a, b));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::sign(State &, Fungespace &, InstructionPointer &ip) {
    if (const auto a = ip.pop(); a == 0) ip.push(0);
    else ip.push(a < 0 ? -1 : 1);
    return MoveAction{};
}

InstructionAction fingerprints::fixp::tan(State &, Fungespace &, InstructionPointer &ip) {
    const auto a = static_cast<double>(ip.pop()) / 10'000.0;
    ip.push(static_cast<Cell>(std::tan(deg_to_rad(a)) * 10'000.0));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::atan(State &, Fungespace &, InstructionPointer &ip) {
    const auto a = static_cast<double>(ip.pop()) / 10'000.0;
    ip.push(static_cast<Cell>(rad_to_deg(std::atan(a)) * 10'000.0));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::abs(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(std::abs(ip.pop()));
    return MoveAction{};
}

InstructionAction fingerprints::fixp::xor_(State &, Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a ^ b);
    return MoveAction{};
}

double deg_to_rad(const double v) { return v * std::numbers::pi / 180.0; }

double rad_to_deg(const double v) { return v * 180.0 / std::numbers::pi; }
