#ifndef AMANITA_STACKSTACK_HPP
#define AMANITA_STACKSTACK_HPP

#include <cstdint>
#include <deque>
#include <string>
#include <vector>
#include "common.hpp"

using Stack = std::deque<Cell>;

class StackStack {
public:
    std::vector<Stack> stacks;
    std::size_t toss;
    std::size_t soss;

    bool invertmode{false};
    bool queuemode{false};

    StackStack();

    std::size_t count() const;
    std::vector<std::size_t> sizes() const;

    void push(Cell value);
    Cell peek() const;
    Cell pop();
    std::string pop_0gnirts();

    std::size_t size() const;
    void clear();

    Cell pick(Cell n) const;

    void begin_block(const Vec &storage_offset);
    bool end_block(Vec &storage_offset);

    bool stack_under_stack();

private:
    void push_(Cell value, std::size_t stack_idx);
    Cell pop_(std::size_t stack_idx);
};

#endif // AMANITA_STACKSTACK_HPP
