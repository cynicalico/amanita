#ifndef AMANITA_INTERPRETER_HPP
#define AMANITA_INTERPRETER_HPP

#include "fungespace.hpp"
#include "instruction_action.hpp"
#include "instruction_pointer.hpp"
#include "instructions.hpp"

class Interpreter {
public:
    Fungespace fungespace;
    std::vector<InstructionPointer> active_list{};
    std::vector<InstructionPointer> inactive_list{};

    explicit Interpreter(const std::filesystem::path &path);

    void run();

    InstructionAction perform_instruction(Instruction ins, InstructionPointer &ip);
    void step_wrap(InstructionPointer &ip);
    void step_to_next_instruction(InstructionPointer &ip, Cell prev_ins, bool start_skipping);
};

#endif // AMANITA_INTERPRETER_HPP
