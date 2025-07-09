#pragma once

#include <vector>
#include "common.hpp"

class InstructionStack {
public:
    std::vector<std::vector<InstructionFunc>> fns;
    std::vector<const char *> loaded_fingerprints[26];

    InstructionStack();

    InstructionAction perform(Instruction ins, State &state, Fungespace &fungespace, InstructionPointer &ip);

    bool load_fingerprint(std::int64_t fingerprint);
    bool unload_fingerprint(std::int64_t fingerprint);

    void push(Instruction ins, InstructionFunc f);
    InstructionFunc pop(Instruction ins);
    InstructionFunc peek(Instruction ins);

private:
    void populate_default_fns_();
};
