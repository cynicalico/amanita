#include "fingerprints/catseye/hrti.hpp"
#include <chrono>
#include <unordered_map>
#include "instruction_pointer.hpp"

InstructionAction fingerprints::hrti::granularity(State &, Fungespace &, InstructionPointer &ip) {
    ip.push(1);
    return MoveAction{};
}

InstructionAction fingerprints::hrti::mark(State &state, Fungespace &, InstructionPointer &ip) {
    state.hrti.marks[ip.id] = Clock::now();
    return MoveAction{};
}

InstructionAction fingerprints::hrti::timer(State &state, Fungespace &, InstructionPointer &ip) {
    using namespace std::chrono;

    if (const auto it = state.hrti.marks.find(ip.id); it != state.hrti.marks.end()) {
        const auto elapsed = Clock::now() - it->second;
        ip.push(duration_cast<microseconds>(elapsed).count());
    } else {
        ip.reflect();
    }
    return MoveAction{};
}

InstructionAction fingerprints::hrti::erase_mark(State &state, Fungespace &, InstructionPointer &ip) {
    state.hrti.marks.erase(ip.id);
    return MoveAction{};
}

InstructionAction fingerprints::hrti::second(State &, Fungespace &, InstructionPointer &ip) {
    using namespace std::chrono;

    const auto now = Clock::now();
    const auto last_second = std::chrono::floor<seconds>(now);
    const auto elapsed = now - last_second;
    ip.push(duration_cast<microseconds>(elapsed).count());
    return MoveAction{};
}
