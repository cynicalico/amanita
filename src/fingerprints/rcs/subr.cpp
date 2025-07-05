#include "fingerprints/rcs/subr.hpp"
#include "instruction_pointer.hpp"

InstructionAction subr::set_absolute_mode(Fungespace &, InstructionPointer &ip) {
    ip.subr_relative_mode = false;
    return MoveAction{};
}

InstructionAction subr::call(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.stack.pop();
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();

    std::vector<std::int64_t> saved{};
    saved.reserve(n);
    for (std::int64_t i = 0; i < n; ++i)
        saved.push_back(ip.stack.pop());

    ip.stack.push(ip.pos[0]);
    ip.stack.push(ip.pos[1]);
    ip.stack.push(ip.delta[0]);
    ip.stack.push(ip.delta[1]);
    for (std::size_t i = 0; i < saved.size(); ++i)
        ip.stack.push(saved[saved.size() - 1 - i]);

    if (ip.subr_relative_mode) {
        ip.pos[0] = x + ip.storage_offset[0];
        ip.pos[1] = y + ip.storage_offset[1];
    } else {
        ip.pos[0] = x;
        ip.pos[1] = y;
    }
    ip.delta[0] = EAST[0];
    ip.delta[1] = EAST[1];

    return MoveAction{};
}

InstructionAction subr::jump(Fungespace &, InstructionPointer &ip) {
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();

    if (ip.subr_relative_mode) {
        ip.pos[0] = x + ip.storage_offset[0];
        ip.pos[1] = y + ip.storage_offset[1];
    } else {
        ip.pos[0] = x;
        ip.pos[1] = y;
    }
    ip.delta[0] = EAST[0];
    ip.delta[1] = EAST[1];

    return MoveAction{};
}

InstructionAction subr::set_relative_mode(Fungespace &, InstructionPointer &ip) {
    ip.subr_relative_mode = true;
    return MoveAction{};
}

InstructionAction subr::ret(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.stack.pop();

    std::vector<std::int64_t> saved{};
    saved.reserve(n);
    for (std::int64_t i = 0; i < n; ++i)
        saved.push_back(ip.stack.pop());

    const auto dy = ip.stack.pop();
    const auto dx = ip.stack.pop();
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();
    for (std::size_t i = 0; i < saved.size(); ++i)
        ip.stack.push(saved[saved.size() - 1 - i]);

    ip.pos[0] = x;
    ip.pos[1] = y;
    ip.delta[0] = dx;
    ip.delta[1] = dy;

    return MoveAction{};
}
