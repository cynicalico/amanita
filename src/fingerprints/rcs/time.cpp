#include "fingerprints/rcs/time.hpp"
#include <chrono>
#include <fmt/format.h>
#include "instruction_pointer.hpp"

auto now(State &state) {
    using namespace std::chrono;
    if (state.time.utc) return zoned_time{"GMT", system_clock::now()}.get_sys_time();
    return system_clock::time_point{current_zone()->to_local(system_clock::now()).time_since_epoch()};
}

auto ymd(State &state) {
    using namespace std::chrono;
    return year_month_day{floor<days>(now(state))};
}

auto hms(State &state) {
    using namespace std::chrono;
    const auto tp = now(state);
    return hh_mm_ss{tp - floor<days>(tp)};
}

InstructionAction fingerprints::time::day(State &state, Fungespace &, InstructionPointer &ip) {
    ip.stack.push(static_cast<unsigned int>(ymd(state).day()));
    return MoveAction{};
}

InstructionAction fingerprints::time::day_of_year(State &state, Fungespace &, InstructionPointer &ip) {
    using namespace std::chrono;
    ip.stack.push(duration_cast<days>(now(state) - sys_days{ymd(state).year() / 1 / 1}).count() + 1);
    return MoveAction{};
}

InstructionAction fingerprints::time::set_gmt(State &state, Fungespace &, InstructionPointer &) {
    state.time.utc = true;
    return MoveAction{};
}

InstructionAction fingerprints::time::hours(State &state, Fungespace &, InstructionPointer &ip) {
    ip.stack.push(hms(state).hours().count());
    return MoveAction{};
}

InstructionAction fingerprints::time::set_local(State &state, Fungespace &, InstructionPointer &) {
    state.time.utc = false;
    return MoveAction{};
}

InstructionAction fingerprints::time::minutes(State &state, Fungespace &, InstructionPointer &ip) {
    ip.stack.push(hms(state).minutes().count());
    return MoveAction{};
}

InstructionAction fingerprints::time::month(State &state, Fungespace &, InstructionPointer &ip) {
    ip.stack.push(static_cast<unsigned int>(ymd(state).month()));
    return MoveAction{};
}

InstructionAction fingerprints::time::seconds(State &state, Fungespace &, InstructionPointer &ip) {
    ip.stack.push(hms(state).seconds().count());
    return MoveAction{};
}

InstructionAction fingerprints::time::day_of_week(State &state, Fungespace &, InstructionPointer &ip) {
    using namespace std::chrono;
    ip.stack.push(weekday{ymd(state)}.c_encoding() + 1);
    return MoveAction{};
}

InstructionAction fingerprints::time::year(State &state, Fungespace &, InstructionPointer &ip) {
    ip.stack.push(static_cast<int>(ymd(state).year()));
    return MoveAction{};
}
