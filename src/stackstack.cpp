#include "stackstack.hpp"

#include <cmath>

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

void amanita::StackStack::begin_block(const Vec &storage_offset) {
    auto n = pop();

    stacks_.emplace_back();
    soss_ = toss_;
    toss_++;

    if (n > 0) {
        const auto soss_len = static_cast<std::int64_t>(stacks_[soss_].size());
        const auto zero_fill = n - soss_len;
        if (zero_fill > 0) {
            for (std::int64_t i = 0; i < zero_fill; ++i)
                push(0);
            n -= zero_fill;
        }
        std::vector<std::int64_t> buf{};
        buf.reserve(n);
        for (std::int64_t i = 0; i < n; ++i)
            buf.push_back(pop_(soss_));
        for (std::int64_t i = 0; i < n; ++i)
            push(buf[n - 1 - i]);
    } else {
        for (std::int64_t i = 0; i < std::abs(n); ++i)
            push_(soss_, 0);
    }

    push_(soss_, storage_offset.x);
    push_(soss_, storage_offset.y);
}

bool amanita::StackStack::end_block(Vec &storage_offset) {
    if (toss_ == soss_)
        return false;

    const auto n = pop();
    storage_offset.y = pop_(soss_);
    storage_offset.x = pop_(soss_);

    if (n > 0) {
        std::vector<std::int64_t> buf{};
        buf.reserve(n);
        for (std::int64_t i = 0; i < n; ++i)
            buf.push_back(pop());
        for (std::int64_t i = 0; i < n; ++i)
            push_(soss_, buf[n - 1 - i]);
    } else {
        for (std::int64_t i = 0; i < std::abs(n); ++i)
            pop_(soss_);
    }

    stacks_.pop_back();
    toss_--;
    if (soss_ > 0)
        soss_--;

    return true;
}

bool amanita::StackStack::stack_under_stack() {
    if (toss_ == soss_)
        return false;

    const auto n = pop();
    const auto src = n > 0 ? soss_ : toss_;
    const auto dst = n > 0 ? toss_ : soss_;

    for (std::int64_t i = 0; i < std::abs(n); ++i)
        push_(dst, pop_(src));

    return true;
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
