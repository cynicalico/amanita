#ifndef AMANITA_INSTRUCTION_POINTER_HPP
#define AMANITA_INSTRUCTION_POINTER_HPP

#include "common.hpp"
#include "fungespace.hpp"
#include "instruction_stack.hpp"
#include "stackstack.hpp"

std::int64_t next_ip_id();

class InstructionPointer {
public:
    std::int64_t id{next_ip_id()};
    bool alive{true};
    std::int64_t pos[2]{0, 0};
    std::int64_t delta[2]{EAST[0], EAST[1]};
    bool stringmode{false};
    Cell cache_ins{'\0'};
    StackStack stack{};
    std::int64_t storage_offset[2]{0, 0};
    InstructionStack instruction_stack{};

    InstructionPointer() = default;
    ~InstructionPointer() = default;

    InstructionPointer(const InstructionPointer &other);
    InstructionPointer &operator=(const InstructionPointer &other) = default;

    InstructionPointer(InstructionPointer &&other) = default;
    InstructionPointer &operator=(InstructionPointer &&other) = default;

    void step();
    void step_wrap(Fungespace &fungespace);
    void step_to_next_instruction(Fungespace &fungespace, Cell prev_ins, bool start_skipping);

    void turn_left();
    void turn_right();
    void reflect();

    void begin_block();
    void end_block();
    void stack_under_stack();

    void save_pos();
    void save_delta();
    void restore_pos();
    void restore_delta();

private:
    std::int64_t saved_pos[2]{0, 0};
    std::int64_t saved_delta[2]{0, 0};
};

#endif // AMANITA_INSTRUCTION_POINTER_HPP
