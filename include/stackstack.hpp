#ifndef AMANITA_STACKSTACK_HPP
#define AMANITA_STACKSTACK_HPP

#include <cstdint>
#include <deque>
#include <string>
#include <vector>

using Stack = std::deque<std::int64_t>;

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

    void push(std::int64_t value);
    std::int64_t peek() const;
    std::int64_t pop();
    std::string pop_0gnirts();

    std::size_t size() const;
    void clear();

    std::int64_t pick(std::int64_t n) const;

    void begin_block(std::int64_t storage_offset[2]);
    bool end_block(std::int64_t out_storage_offset[2]);

    bool stack_under_stack();

private:
    void push_(std::int64_t value, std::size_t stack_idx);
    std::int64_t pop_(std::size_t stack_idx);
};

#endif // AMANITA_STACKSTACK_HPP
