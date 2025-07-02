#include "common.hpp"
#include "instruction_pointer.hpp"

InstructionAction null_all(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}
