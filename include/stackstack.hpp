#ifndef AMANITA_STACKSTACK_HPP
#define AMANITA_STACKSTACK_HPP

#include <cstdint>
#include <vector>

using Stack = std::vector<std::int64_t>;

class StackStack {
public:
    StackStack();

    void push(std::int64_t value);

    std::int64_t peek() const;

    std::int64_t pop();

private:
    std::vector<Stack> stacks_;
};

#endif // AMANITA_STACKSTACK_HPP
