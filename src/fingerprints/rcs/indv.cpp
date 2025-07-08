#include "fingerprints/rcs/indv.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

Vec pop_pointer(Fungespace &fungespace, InstructionPointer &ip) {
    Vec p;

    auto vp = ip.pop_offset_vec();
    p.y = fungespace.get(vp.x++, vp.y);
    p.x = fungespace.get(vp.x++, vp.y);
    p += ip.storage_offset;

    return p;
}

InstructionAction fingerprints::indv::get_number(State &, Fungespace &fungespace, InstructionPointer &ip) {
    const auto p = pop_pointer(fungespace, ip);

    ip.push(fungespace.get(p.x, p.y));

    return MoveAction{};
}

InstructionAction fingerprints::indv::put_number(State &, Fungespace &fungespace, InstructionPointer &ip) {
    const auto p = pop_pointer(fungespace, ip);
    const auto n = ip.pop();

    fungespace.put(p.x, p.y, n);

    return MoveAction{};
}

InstructionAction fingerprints::indv::get_vector(State &, Fungespace &fungespace, InstructionPointer &ip) {
    auto p = pop_pointer(fungespace, ip);

    p.x += 1;
    ip.push(fungespace.get(p.x--, p.y));
    ip.push(fungespace.get(p.x--, p.y));

    return MoveAction{};
}

InstructionAction fingerprints::indv::put_vector(State &, Fungespace &fungespace, InstructionPointer &ip) {
    auto p = pop_pointer(fungespace, ip);
    const auto v = ip.pop_vec();

    fungespace.put(p.x++, p.y, v.y);
    fungespace.put(p.x++, p.y, v.x);

    return MoveAction{};
}
