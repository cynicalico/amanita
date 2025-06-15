#include "stackstack.hpp"

StackStack::StackStack()
    : stacks_(1) {}

void StackStack::push(std::int64_t value) {
    stacks_.back().push_back(value);
}

std::int64_t StackStack::peek() const {
    if (stacks_.back().empty())
        return 0;
    return stacks_.back().back();
}

std::int64_t StackStack::pop() {
    if (stacks_.back().empty())
        return 0;

    const auto v = stacks_.back().back();
    stacks_.back().pop_back();
    return v;
}
