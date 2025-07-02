#include "fingerprints/null.hpp"
#include "instruction_pointer.hpp"

InstructionAction null_reflect(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}
