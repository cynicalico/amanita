#include "fingerprints/catseye/hrti.hpp"
#include <chrono>
#include <unordered_map>
#include "instruction_pointer.hpp"

using namespace std::chrono;
using Clock = steady_clock;

std::unordered_map<std::int64_t, Clock::time_point> &marks();

InstructionAction hrti::granularity(Fungespace &, InstructionPointer &ip) {
    ip.push(1);
    return MoveAction{};
}

InstructionAction hrti::mark(Fungespace &, InstructionPointer &ip) {
    marks()[ip.id] = Clock::now();
    return MoveAction{};
}

InstructionAction hrti::timer(Fungespace &, InstructionPointer &ip) {
    auto m = marks();
    if (const auto it = m.find(ip.id); it != m.end()) {
        const auto elapsed = Clock::now() - it->second;
        ip.push(duration_cast<microseconds>(elapsed).count());
    } else {
        ip.reflect();
    }
    return MoveAction{};
}

InstructionAction hrti::erase_mark(Fungespace &, InstructionPointer &ip) {
    marks().erase(ip.id);
    return MoveAction{};
}

InstructionAction hrti::second(Fungespace &, InstructionPointer &ip) {
    const auto now = Clock::now();
    const auto last_second = std::chrono::floor<seconds>(now);
    const auto elapsed = now - last_second;
    ip.push(duration_cast<microseconds>(elapsed).count());
    return MoveAction{};
}

std::unordered_map<std::int64_t, Clock::time_point> &marks() {
    static std::unordered_map<std::int64_t, Clock::time_point> marks{};
    return marks;
}
