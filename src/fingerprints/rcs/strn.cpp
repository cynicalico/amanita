#include "fingerprints/rcs/strn.hpp"
#include <fmt/format.h>
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

InstructionAction fingerprints::strn::append(State &, Fungespace &, InstructionPointer &ip) {
    const auto s2 = ip.pop_0gnirts();
    const auto s1 = ip.pop_0gnirts();

    ip.push_0gnirts(s2 + s1);

    return MoveAction{};
}

InstructionAction fingerprints::strn::compare(State &, Fungespace &, InstructionPointer &ip) {
    const auto s2 = ip.pop_0gnirts();
    const auto s1 = ip.pop_0gnirts();

    ip.push(s2.compare(s1));

    return MoveAction{};
}

InstructionAction fingerprints::strn::display(State &, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    fmt::print("{}", s);

    return MoveAction{};
}

InstructionAction fingerprints::strn::search(State &, Fungespace &, InstructionPointer &ip) {
    const auto s2 = ip.pop_0gnirts();
    const auto s1 = ip.pop_0gnirts();

    if (const auto start = s2.find(s1); start != std::string::npos) ip.push_0gnirts(s2.substr(start));
    else ip.push('\0');

    return MoveAction{};
}

InstructionAction fingerprints::strn::get(State &, Fungespace &fungespace, InstructionPointer &ip) {
    auto va = ip.pop_offset_vec();

    std::string s;
    Cell c;
    do {
        c = fungespace.get(va.x, va.y);
        va += EAST;
        if (c != '\0') s += static_cast<char>(c);
    } while (c != '\0');

    ip.push_0gnirts(s);

    return MoveAction{};
}

InstructionAction fingerprints::strn::input(State &, Fungespace &, InstructionPointer &ip) {
    std::string s;
    int c;
    do {
        c = std::getchar();
        if (c != '\n' && c != EOF) s += static_cast<char>(c);
    } while (c != '\n' && c != EOF);

    ip.push_0gnirts(s);

    return MoveAction{};
}

InstructionAction fingerprints::strn::leftmost(State &, Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto s = ip.pop_0gnirts();

    if (n < 0) ip.reflect();
    else if (n == 0) ip.push('\0');
    else ip.push_0gnirts(s.substr(0, n));

    return MoveAction{};
}

InstructionAction fingerprints::strn::substr(State &, Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto start = ip.pop();
    const auto s = ip.pop_0gnirts();

    if (n < 0 || start < 0 || start >= s.size()) ip.reflect();
    else if (n == 0) ip.push('\0');
    else if (start + n > s.size()) ip.push_0gnirts(s.substr(start));
    else ip.push_0gnirts(s.substr(start, n));

    return MoveAction{};
}

InstructionAction fingerprints::strn::length(State &, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    ip.push_0gnirts(s);
    ip.push(s.size());

    return MoveAction{};
}

InstructionAction fingerprints::strn::put(State &, Fungespace &fungespace, InstructionPointer &ip) {
    auto va = ip.pop_offset_vec();
    const auto s = ip.pop_0gnirts();

    for (const auto &c: s) {
        fungespace.put(va.x, va.y, c);
        va += EAST;
    }
    fungespace.put(va.x, va.y, '\0');

    return MoveAction{};
}

InstructionAction fingerprints::strn::rightmost(State &, Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto s = ip.pop_0gnirts();

    if (n < 0) ip.reflect();
    else if (n == 0) ip.push('\0');
    else if (n > s.size()) ip.push_0gnirts(s);
    else ip.push_0gnirts(s.substr(s.size() - n));

    return MoveAction{};
}

InstructionAction fingerprints::strn::itoa(State &, Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();

    ip.push_0gnirts(std::to_string(n));

    return MoveAction{};
}

InstructionAction fingerprints::strn::atoi(State &, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    try {
        ip.push(std::stoll(s));
    } catch (const std::exception &) { ip.push(0); }

    return MoveAction{};
}
