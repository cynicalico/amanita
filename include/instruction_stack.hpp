#ifndef AMANITA_INSTRUCTION_STACK_HPP
#define AMANITA_INSTRUCTION_STACK_HPP

#include <functional>
#include <vector>
#include "common.hpp"
#include "fungespace.hpp"
#include "instructions.hpp"

class InstructionPointer;

using InstructionFunc = std::function<InstructionAction(Fungespace &fungespace, InstructionPointer &)>;

class InstructionStack {
public:
    std::vector<std::vector<InstructionFunc>> fns;
    std::vector<const char *> loaded_fingerprints[26];

    InstructionStack();

    InstructionAction perform(Instruction ins, Fungespace &fungespace, InstructionPointer &ip);

private:
    void populate_default_fns_();
};

#endif // AMANITA_INSTRUCTION_STACK_HPP
