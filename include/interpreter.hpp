#ifndef AMANITA_INTERPRETER_HPP
#define AMANITA_INTERPRETER_HPP

#include "fungespace.hpp"
#include "instruction_pointer.hpp"

class Interpreter {
public:
    Fungespace fungespace;
    std::vector<std::string> args{};
    std::vector<InstructionPointer> active_list{};
    std::vector<InstructionPointer> inactive_list{};

    Interpreter();
    explicit Interpreter(const std::filesystem::path &path);

    void run(std::vector<std::string> args);
};

#endif // AMANITA_INTERPRETER_HPP
