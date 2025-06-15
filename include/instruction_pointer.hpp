#ifndef AMANITA_INSTRUCTION_POINTER_HPP
#define AMANITA_INSTRUCTION_POINTER_HPP

#include <cstdint>
#include "fungespace.hpp"
#include "stackstack.hpp"

constexpr std::int64_t SOUTH[2] = {0, 1};
constexpr std::int64_t EAST[2] = {1, 0};
constexpr std::int64_t NORTH[2] = {0, -1};
constexpr std::int64_t WEST[2] = {-1, 0};

class InstructionPointer {
public:
    bool alive{true};
    std::int64_t pos[2]{0, 0};
    std::int64_t delta[2]{EAST[0], EAST[1]};
    bool stringmode{false};
    Cell cache_ins{'\0'};
    StackStack stack{};

    void step();

    void reflect();
};

#endif // AMANITA_INSTRUCTION_POINTER_HPP
