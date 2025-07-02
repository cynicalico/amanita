#ifndef AMANITA_STACKSTACK_HPP
#define AMANITA_STACKSTACK_HPP

#include <cstdint>
#include <string>
#include <vector>

using Stack = std::vector<std::int64_t>;

class StackStack {
public:
    StackStack();

    std::size_t count() const;
    std::vector<std::size_t> sizes() const;

    void push(std::int64_t value);
    std::int64_t peek() const;
    std::int64_t pop();
    std::string pop_gnirts();
    std::size_t size() const;
    void clear();

    std::int64_t pick(std::int64_t n) const;

    void begin_block(std::int64_t storage_offset[2]);
    bool end_block(std::int64_t out_storage_offset[2]);

    bool stack_under_stack();

private:
    std::vector<Stack> stacks_;
    std::size_t toss_;
    std::size_t soss_;

    void push_(std::int64_t value, std::size_t stack_idx);
    std::int64_t pop_(std::size_t stack_idx);
};

#endif // AMANITA_STACKSTACK_HPP
