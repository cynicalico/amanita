#include "fingerprints/rcs/strn.hpp"
#include <fmt/format.h>
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

InstructionAction strn::append(Fungespace &, InstructionPointer &ip) {
    const auto s2 = ip.pop_0gnirts();
    const auto s1 = ip.pop_0gnirts();

    ip.push_0gnirts(s2 + s1);

    return MoveAction{};
}

InstructionAction strn::compare(Fungespace &, InstructionPointer &ip) {
    const auto s2 = ip.pop_0gnirts();
    const auto s1 = ip.pop_0gnirts();

    ip.push(s2.compare(s1));

    return MoveAction{};
}

InstructionAction strn::display(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    fmt::print("{}", s);

    return MoveAction{};
}

InstructionAction strn::search(Fungespace &, InstructionPointer &ip) {
    const auto s2 = ip.pop_0gnirts();
    const auto s1 = ip.pop_0gnirts();

    if (const auto start = s2.find(s1); start != std::string::npos) ip.push_0gnirts(s2.substr(start));
    else ip.push('\0');

    return MoveAction{};
}

InstructionAction strn::get(Fungespace &fungespace, InstructionPointer &ip) {
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

InstructionAction strn::input(Fungespace &, InstructionPointer &ip) {
    std::string s;
    int c;
    do {
        c = std::getchar();
        if (c != '\n' && c != EOF) s += static_cast<char>(c);
    } while (c != '\n' && c != EOF);

    ip.push_0gnirts(s);

    return MoveAction{};
}

InstructionAction strn::leftmost(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto s = ip.pop_0gnirts();

    if (n < 0) ip.reflect();
    else if (n == 0) ip.push('\0');
    else ip.push_0gnirts(s.substr(0, n));

    return MoveAction{};
}

InstructionAction strn::substr(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto start = ip.pop();
    const auto s = ip.pop_0gnirts();

    if (n < 0 || start < 0 || start >= s.size()) ip.reflect();
    else if (n == 0) ip.push('\0');
    else if (start + n > s.size()) ip.push_0gnirts(s.substr(start));
    else ip.push_0gnirts(s.substr(start, n));

    return MoveAction{};
}

InstructionAction strn::length(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    ip.push_0gnirts(s);
    ip.push(s.size());

    return MoveAction{};
}

InstructionAction strn::put(Fungespace &fungespace, InstructionPointer &ip) {
    auto va = ip.pop_offset_vec();
    const auto s = ip.pop_0gnirts();

    for (const auto &c: s) {
        fungespace.put(va.x, va.y, c);
        va += EAST;
    }
    fungespace.put(va.x, va.y, '\0');

    return MoveAction{};
}

InstructionAction strn::rightmost(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto s = ip.pop_0gnirts();

    if (n < 0) ip.reflect();
    else if (n == 0) ip.push('\0');
    else if (n > s.size()) ip.push_0gnirts(s);
    else ip.push_0gnirts(s.substr(s.size() - n));

    return MoveAction{};
}

InstructionAction strn::itoa(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();

    ip.push_0gnirts(std::to_string(n));

    return MoveAction{};
}

InstructionAction strn::atoi(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();

    try {
        ip.push(std::stoll(s));
    } catch (const std::exception &) { ip.push(0); }

    return MoveAction{};
}
