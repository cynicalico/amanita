#ifndef AMANITA_INSTRUCTION_POINTER_HPP
#define AMANITA_INSTRUCTION_POINTER_HPP

#include "common.hpp"
#include "instruction_stack.hpp"
#include "stackstack.hpp"

Cell next_ip_id();

class InstructionPointer {
public:
    Cell id{next_ip_id()};

    bool alive{true};
    Vec pos{ZERO};
    Vec delta{EAST};

    bool string_mode{false};
    Cell cache_ins{'\0'};

    StackStack stack{};
    Vec storage_offset{ZERO};

    InstructionStack instruction_stack{};

    // MODE
    bool hover_mode{false};
    bool switch_mode{false};

    // SUBR
    bool relative_mode{false};
    std::vector<Cell> call_stack{};

    InstructionPointer() = default;
    ~InstructionPointer() = default;

    InstructionPointer(const InstructionPointer &other);
    InstructionPointer &operator=(const InstructionPointer &other) = default;

    InstructionPointer(InstructionPointer &&other) = default;
    InstructionPointer &operator=(InstructionPointer &&other) = default;

    void step();
    void step_wrap(const Fungespace &fungespace);
    void step_to_next_instruction(const Fungespace &fungespace, Cell prev_ins, bool start_skipping);

    void go_south();
    void go_east();
    void go_north();
    void go_west();
    void turn_left();
    void turn_right();
    void reflect();

    void save_pos();
    void save_delta();
    void restore_pos();
    void restore_delta();

    Cell pop();
    Vec pop_vec();
    Vec pop_offset_vec();
    std::string pop_0gnirts();
    void push_0gnirts(const std::string &s);
    void push(Cell v);
    void push_vec(Vec v);

    void begin_block();
    void end_block();
    void stack_under_stack();

private:
    Vec saved_pos_{ZERO};
    Vec saved_delta_{ZERO};
};

#endif // AMANITA_INSTRUCTION_POINTER_HPP
