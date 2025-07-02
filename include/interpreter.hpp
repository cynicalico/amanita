#ifndef AMANITA_INTERPRETER_HPP
#define AMANITA_INTERPRETER_HPP

#include "fungespace.hpp"
#include "instruction_pointer.hpp"

class Interpreter {
public:
    Fungespace fungespace;
    std::vector<InstructionPointer> active_list{};
    std::vector<InstructionPointer> inactive_list{};

    Interpreter();
    explicit Interpreter(const std::filesystem::path &path);

    void run();
};

#endif // AMANITA_INTERPRETER_HPP
