#include "fingerprints/catseye/mode.hpp"
#include "instruction_pointer.hpp"

InstructionAction fingerprints::mode::toggle_hovermode(Fungespace &, InstructionPointer &ip) {
    ip.hover_mode = !ip.hover_mode;
    return MoveAction{};
}

InstructionAction fingerprints::mode::toggle_invertmode(Fungespace &, InstructionPointer &ip) {
    ip.stack.invertmode = !ip.stack.invertmode;
    return MoveAction{};
}

InstructionAction fingerprints::mode::toggle_queuemode(Fungespace &, InstructionPointer &ip) {
    ip.stack.queuemode = !ip.stack.queuemode;
    return MoveAction{};
}

InstructionAction fingerprints::mode::toggle_switchmode(Fungespace &, InstructionPointer &ip) {
    ip.switch_mode = !ip.switch_mode;
    return MoveAction{};
}
