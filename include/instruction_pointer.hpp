#ifndef AMANITA_INSTRUCTION_POINTER_HPP
#define AMANITA_INSTRUCTION_POINTER_HPP

#include "common.hpp"
#include "fungespace.hpp"
#include "instruction_stack.hpp"
#include "stackstack.hpp"

std::int64_t next_ip_id();

class Interpreter;

class InstructionPointer {
public:
    Interpreter *interpreter{nullptr};
    std::int64_t id{next_ip_id()};

    bool alive{true};
    Vec pos{ZERO};
    Vec delta{EAST};

    bool stringmode{false};
    Cell cache_ins{'\0'};

    bool hovermode{false};
    bool switchmode{false};

    bool subr_relative_mode{false};

    StackStack stack{};
    Vec storage_offset{ZERO};

    InstructionStack instruction_stack{};

    InstructionPointer(Interpreter *interpreter);
    ~InstructionPointer() = default;

    InstructionPointer(const InstructionPointer &other);
    InstructionPointer &operator=(const InstructionPointer &other) = default;

    InstructionPointer(InstructionPointer &&other) = default;
    InstructionPointer &operator=(InstructionPointer &&other) = default;

    void step();
    void step_wrap(Fungespace &fungespace);
    void step_to_next_instruction(Fungespace &fungespace, Cell prev_ins, bool start_skipping);

    void go_south();
    void go_east();
    void go_north();
    void go_west();
    void turn_left();
    void turn_right();
    void reflect();

    std::int64_t pop();
    Vec pop_vec();
    Vec pop_offset_vec();
    void push(std::int64_t v);
    void push_vec(Vec v);

    void begin_block();
    void end_block();
    void stack_under_stack();

    void save_pos();
    void save_delta();
    void restore_pos();
    void restore_delta();

private:
    Vec saved_pos_{ZERO};
    Vec saved_delta_{ZERO};
};

#endif // AMANITA_INSTRUCTION_POINTER_HPP
