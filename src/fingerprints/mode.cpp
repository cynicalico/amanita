#include "fingerprints/mode.hpp"
#include "instruction_pointer.hpp"

InstructionAction mode::toggle_hovermode(Fungespace &, InstructionPointer &ip) {
    ip.hovermode = !ip.hovermode;
    return MoveAction{};
}

InstructionAction mode::toggle_invertmode(Fungespace &, InstructionPointer &ip) {
    ip.stack.invertmode = !ip.stack.invertmode;
    return MoveAction{};
}

InstructionAction mode::toggle_queuemode(Fungespace &, InstructionPointer &ip) {
    ip.stack.queuemode = !ip.stack.queuemode;
    return MoveAction{};
}

InstructionAction mode::toggle_switchmode(Fungespace &, InstructionPointer &ip) {
    ip.switchmode = !ip.switchmode;
    return MoveAction{};
}
