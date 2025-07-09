#include "stackstack.hpp"

StackStack::StackStack()
    : stacks(1), toss(0), soss(0) {}

std::size_t StackStack::count() const { return stacks.size(); }

std::vector<std::size_t> StackStack::sizes() const {
    std::vector<std::size_t> sizes{};
    for (const auto &stack: stacks) sizes.emplace_back(stack.size());
    return sizes;
}

void StackStack::push(Cell value) { push_(value, toss); }

Cell StackStack::peek() const {
    if (stacks[toss].empty()) return 0;
    if (queuemode) return stacks[toss].front();
    return stacks[toss].back();
}

Cell StackStack::pop() { return pop_(toss); }

std::size_t StackStack::size() const { return stacks[toss].size(); }

void StackStack::clear() { stacks[toss].clear(); }

Cell StackStack::pick(Cell n) const {
    n = stacks[toss].size() - n;
    if (n >= 0) return stacks[toss][static_cast<std::size_t>(n)];
    return 0;
}

void StackStack::begin_block(const Vec &storage_offset) {
    auto n = pop();

    stacks.emplace_back();
    toss++;
    soss = toss - 1;

    if (n > 0) {
        const auto soss_len = static_cast<Cell>(stacks[soss].size());
        const auto zero_fill = n - soss_len;
        if (zero_fill > 0) {
            for (Cell i = 0; i < zero_fill; i++) push(0);
            n -= zero_fill;
        }
        std::vector<Cell> buffer{};
        buffer.reserve(n);
        for (Cell i = 0; i < n; i++) buffer.push_back(pop_(soss));
        for (std::size_t i = 0; i < buffer.size(); i++) push(buffer[buffer.size() - 1 - i]);
    } else {
        for (Cell i = 0; i < std::abs(n); i++) push_(0, soss);
    }

    push_(storage_offset.x, soss);
    push_(storage_offset.y, soss);
}

bool StackStack::end_block(Vec &storage_offset) {
    if (toss == soss) return false;

    const auto n = pop();
    storage_offset.y = pop_(soss);
    storage_offset.x = pop_(soss);

    if (n > 0) {
        std::vector<Cell> buffer{};
        buffer.reserve(n);
        for (Cell i = 0; i < n && size() > 0; i++) buffer.push_back(pop());
        for (std::size_t i = 0; i < buffer.size(); i++) push_(buffer[buffer.size() - 1 - i], soss);
    } else {
        for (Cell i = 0; i < std::abs(n); i++) pop_(soss);
    }

    stacks.pop_back();
    toss--;
    soss = toss > 0 ? toss - 1 : toss;

    return true;
}

bool StackStack::stack_under_stack() {
    if (toss == soss) return false;

    const auto n = pop();
    const auto src = n > 0 ? soss : toss;
    const auto dst = n > 0 ? toss : soss;

    for (Cell i = 0; i < std::abs(n); i++) push_(pop_(src), dst);

    return true;
}

void StackStack::push_(Cell value, std::size_t stack_idx) {
    if (invertmode) stacks[stack_idx].push_front(value);
    else stacks[stack_idx].push_back(value);
}

Cell StackStack::pop_(std::size_t stack_idx) {
    if (stacks[stack_idx].empty()) return 0;

    Cell v;
    if (queuemode) v = stacks[stack_idx].pop_front();
    else v = stacks[stack_idx].pop_back();
    return v;
}
