#include "stackstack.hpp"

StackStack::StackStack()
    : stacks_(1), toss_(0), soss_(0) {}

std::size_t StackStack::count() const {
    return stacks_.size();
}

std::vector<std::size_t> StackStack::sizes() const {
    std::vector<std::size_t> sizes{};
    for (const auto &stack: stacks_)
        sizes.emplace_back(stack.size());
    return sizes;
}

void StackStack::push(std::int64_t value) {
    push_(value, toss_);
}

std::int64_t StackStack::peek() const {
    if (stacks_[toss_].empty())
        return 0;
    if (queuemode)
        return stacks_[toss_].front();
    return stacks_[toss_].back();
}

std::int64_t StackStack::pop() {
    return pop_(toss_);
}

std::string StackStack::pop_gnirts() {
    std::string ret;
    std::int64_t c;
    do {
        c = pop();
        if (c != 0)
            ret += static_cast<char>(c);
    } while (c != 0);
    return ret;
}

std::size_t StackStack::size() const {
    return stacks_[toss_].size();
}

void StackStack::clear() {
    stacks_[toss_].clear();
}

std::int64_t StackStack::pick(std::int64_t n) const {
    n = stacks_[toss_].size() - n;
    if (n >= 0)
        return stacks_[toss_][static_cast<std::size_t>(n)];
    return 0;
}

void StackStack::begin_block(std::int64_t storage_offset[2]) {
    auto n = pop();

    stacks_.emplace_back();
    toss_++;
    soss_ = toss_ - 1;

    if (n > 0) {
        const auto soss_len = static_cast<std::int64_t>(stacks_[soss_].size());
        const auto zero_fill = n - soss_len;
        if (zero_fill > 0) {
            for (std::int64_t i = 0; i < zero_fill; i++)
                push(0);
            n -= zero_fill;
        }
        std::vector<std::int64_t> buffer{};
        buffer.reserve(n);
        for (std::int64_t i = 0; i < n; i++)
            buffer.push_back(pop_(soss_));
        for (std::size_t i = 0; i < buffer.size(); i++)
            push(buffer[buffer.size() - 1 - i]);
    } else {
        for (std::int64_t i = 0; i < std::abs(n); i++)
            push_(0, soss_);
    }

    push_(storage_offset[0], soss_);
    push_(storage_offset[1], soss_);
}

bool StackStack::end_block(std::int64_t out_storage_offset[2]) {
    if (toss_ == soss_)
        return false;

    const auto n = pop();
    out_storage_offset[0] = pop_(soss_);
    out_storage_offset[1] = pop_(soss_);

    if (n > 0) {
        std::vector<std::int64_t> buffer{};
        buffer.reserve(n);
        for (std::int64_t i = 0; i < n && size() > 0; i++)
            buffer.push_back(pop());
        for (std::size_t i = 0; i < buffer.size(); i++)
            push_(buffer[buffer.size() - 1 - i], soss_);
    } else {
        for (std::int64_t i = 0; i < std::abs(n); i++)
            pop_(soss_);
    }

    stacks_.pop_back();
    toss_--;
    soss_ = (toss_ > 1) ? toss_ - 1 : toss_;

    return true;
}

bool StackStack::stack_under_stack() {
    if (toss_ == soss_)
        return false;

    const auto n = pop();
    const auto src = n > 0 ? soss_ : toss_;
    const auto dst = n > 0 ? toss_ : soss_;

    for (std::int64_t i = 0; i < std::abs(n); i++)
        push_(pop_(src), dst);

    return true;
}

void StackStack::push_(std::int64_t value, std::size_t stack_idx) {
    if (invertmode)
        stacks_[stack_idx].push_front(value);
    else
        stacks_[stack_idx].push_back(value);
}

std::int64_t StackStack::pop_(std::size_t stack_idx) {
    if (stacks_[stack_idx].empty())
        return 0;

    std::int64_t v;
    if (queuemode) {
        v = stacks_[stack_idx].front();
        stacks_[stack_idx].pop_front();
    } else {
        v = stacks_[stack_idx].back();
        stacks_[stack_idx].pop_back();
    }
    return v;
}
