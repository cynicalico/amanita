#include "stackstack.hpp"

amanita::StackStack::StackStack()
    : toss_(0),
      soss_(0) {
    stacks_.emplace_back();
}

void amanita::StackStack::clear() {
    stacks_[toss_].clear();
}

void amanita::StackStack::push(const std::int64_t value) {
    push_(toss_, value);
}

std::int64_t amanita::StackStack::peek() const {
    if (stacks_[toss_].empty())
        return 0;

    return stacks_[toss_].back();
}

std::int64_t amanita::StackStack::pop() {
    return pop_(toss_);
}

void amanita::StackStack::push_(const std::size_t stack_idx, const std::int64_t value) {
    stacks_[stack_idx].push_back(value);
}

std::int64_t amanita::StackStack::pop_(const std::size_t stack_idx) {
    if (stacks_[stack_idx].empty())
        return 0;

    auto value = stacks_[stack_idx].back();
    stacks_[stack_idx].pop_back();
    return value;
}
