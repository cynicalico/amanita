#ifndef AMANITA_INSTRUCTION_POINTER_HPP
#define AMANITA_INSTRUCTION_POINTER_HPP

#include <cstdint>
#include "fungespace.hpp"
#include "stackstack.hpp"

constexpr std::int64_t SOUTH[2] = {0, 1};
constexpr std::int64_t EAST[2] = {1, 0};
constexpr std::int64_t NORTH[2] = {0, -1};
constexpr std::int64_t WEST[2] = {-1, 0};

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

    InstructionPointer() = default;
    ~InstructionPointer() = default;

    InstructionPointer(const InstructionPointer &other);
    InstructionPointer &operator=(const InstructionPointer &other) = default;

    InstructionPointer(InstructionPointer &&other) = default;
    InstructionPointer &operator=(InstructionPointer &&other) = default;

    void step();

    void reflect();

    void begin_block();
    void end_block();

    void stack_under_stack();
};

#endif // AMANITA_INSTRUCTION_POINTER_HPP
