#pragma once

#include "vec.hpp"

#include <deque>
#include <vector>

namespace amanita {
using Stack = std::deque<std::int64_t>;

class StackStack {
public:
    StackStack();

    void clear();

    void push(std::int64_t value);
    std::int64_t peek() const;
    std::int64_t pop();

    void begin_block(const Vec &storage_offset);
    bool end_block(Vec &storage_offset);
    bool stack_under_stack();

private:
    std::vector<Stack> stacks_;
    std::size_t toss_;
    std::size_t soss_;

    void push_(std::size_t stack_idx, std::int64_t value);
    std::int64_t pop_(std::size_t stack_idx);
};
} // namespace amanita
