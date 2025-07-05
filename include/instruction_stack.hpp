#ifndef AMANITA_INSTRUCTION_STACK_HPP
#define AMANITA_INSTRUCTION_STACK_HPP

#include <vector>
#include "common.hpp"

class InstructionStack {
public:
    std::vector<std::vector<InstructionFunc>> fns;
    std::vector<const char *> loaded_fingerprints[26];

    InstructionStack();

    InstructionAction perform(Instruction ins, Fungespace &fungespace, InstructionPointer &ip);

    bool load_fingerprint(std::int64_t fingerprint);

    bool unload_fingerprint(std::int64_t fingerprint);

private:
    void populate_default_fns_();
};

#endif // AMANITA_INSTRUCTION_STACK_HPP
