#include "fingerprints/rcs/subr.hpp"
#include "instruction_pointer.hpp"

Vec pop_offset_vec(InstructionPointer &ip) {
    if (ip.subr_relative_mode)
        return ip.pop_offset_vec();
    return ip.pop_vec();
}

InstructionAction subr::set_absolute_mode(Fungespace &, InstructionPointer &ip) {
    ip.subr_relative_mode = false;
    return MoveAction{};
}

InstructionAction subr::call(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto dst = pop_offset_vec(ip);

    std::vector<std::int64_t> saved{};
    saved.reserve(n);
    for (std::int64_t i = 0; i < n; ++i)
        saved.push_back(ip.pop());

    ip.push_vec(ip.pos);
    ip.push_vec(ip.delta);
    for (std::size_t i = 0; i < saved.size(); ++i)
        ip.push(saved[saved.size() - 1 - i]);

    ip.pos = dst;
    ip.delta = EAST;

    return MoveAction{};
}

InstructionAction subr::jump(Fungespace &, InstructionPointer &ip) {
    ip.pos = pop_offset_vec(ip);
    ip.delta = EAST;
    return MoveAction{};
}

InstructionAction subr::set_relative_mode(Fungespace &, InstructionPointer &ip) {
    ip.subr_relative_mode = true;
    return MoveAction{};
}

InstructionAction subr::ret(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();

    std::vector<std::int64_t> saved{};
    saved.reserve(n);
    for (std::int64_t i = 0; i < n; ++i)
        saved.push_back(ip.pop());

    ip.delta = ip.pop_vec();
    ip.pos = ip.pop_vec();

    for (std::size_t i = 0; i < saved.size(); ++i)
        ip.push(saved[saved.size() - 1 - i]);

    return MoveAction{};
}
