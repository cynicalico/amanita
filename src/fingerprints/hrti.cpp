#include "fingerprints/hrti.hpp"
#include <chrono>
#include <unordered_map>
#include "instruction_pointer.hpp"

using namespace std::chrono;
using Clock = steady_clock;

std::unordered_map<std::int64_t, Clock::time_point> &marks() {
    static std::unordered_map<std::int64_t, Clock::time_point> marks{};
    return marks;
}

InstructionAction hrti_granularity(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(1);
    return MoveAction{};
}

InstructionAction hrti_mark(Fungespace &, InstructionPointer &ip) {
    marks()[ip.id] = Clock::now();
    return MoveAction{};
}

InstructionAction hrti_timer(Fungespace &, InstructionPointer &ip) {
    auto m = marks();
    if (const auto it = m.find(ip.id); it != m.end()) {
        const auto elapsed = Clock::now() - it->second;
        ip.stack.push(duration_cast<microseconds>(elapsed).count());
    } else {
        ip.reflect();
    }
    return MoveAction{};
}

InstructionAction hrti_erase_mark(Fungespace &, InstructionPointer &ip) {
    marks().erase(ip.id);
    return MoveAction{};
}

InstructionAction hrti_second(Fungespace &, InstructionPointer &ip) {
    const auto now = Clock::now();
    const auto last_second = std::chrono::floor<seconds>(now);
    const auto elapsed = now - last_second;
    ip.stack.push(duration_cast<microseconds>(elapsed).count());
    return MoveAction{};
}
