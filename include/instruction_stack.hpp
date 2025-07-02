#ifndef AMANITA_INSTRUCTION_STACK_HPP
#define AMANITA_INSTRUCTION_STACK_HPP

#include <functional>
#include "instruction_action.hpp"
#include "instructions.hpp"
#include "fungespace.hpp"
#include <vector>

class InstructionPointer;

using InstructionFunc = std::function<InstructionAction(Fungespace &fungespace, InstructionPointer &)>;

class InstructionStack {
public:
    InstructionStack();

    InstructionAction perform(Instruction ins, Fungespace &fungespace, InstructionPointer &ip);

private:
    std::vector<std::vector<InstructionFunc> > fns_;

    void populate_default_fns_();
};

#endif // AMANITA_INSTRUCTION_STACK_HPP
