#include "fingerprints/rcs/time.hpp"
#include <chrono>
#include <fmt/format.h>
#include "instruction_pointer.hpp"

bool &utc() {
    static bool utc = false;
    return utc;
}

auto now() {
    using namespace std::chrono;
    if (utc()) return zoned_time{"GMT", system_clock::now()}.get_sys_time();
    return system_clock::time_point{current_zone()->to_local(system_clock::now()).time_since_epoch()};
}

auto ymd() {
    using namespace std::chrono;
    return year_month_day{floor<days>(now())};
}

auto hms() {
    using namespace std::chrono;
    const auto tp = now();
    return hh_mm_ss{tp - floor<days>(tp)};
}

InstructionAction fingerprints::time::day(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(static_cast<unsigned int>(ymd().day()));
    return MoveAction{};
}

InstructionAction fingerprints::time::day_of_year(Fungespace &, InstructionPointer &ip) {
    using namespace std::chrono;
    ip.stack.push(duration_cast<days>(now() - sys_days{ymd().year() / 1 / 1}).count() + 1);
    return MoveAction{};
}

InstructionAction fingerprints::time::set_gmt(Fungespace &, InstructionPointer &) {
    utc() = true;
    return MoveAction{};
}

InstructionAction fingerprints::time::hours(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(hms().hours().count());
    return MoveAction{};
}

InstructionAction fingerprints::time::set_local(Fungespace &, InstructionPointer &) {
    utc() = false;
    return MoveAction{};
}

InstructionAction fingerprints::time::minutes(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(hms().minutes().count());
    return MoveAction{};
}

InstructionAction fingerprints::time::month(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(static_cast<unsigned int>(ymd().month()));
    return MoveAction{};
}

InstructionAction fingerprints::time::seconds(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(hms().seconds().count());
    return MoveAction{};
}

InstructionAction fingerprints::time::day_of_week(Fungespace &, InstructionPointer &ip) {
    using namespace std::chrono;
    ip.stack.push(weekday{ymd()}.c_encoding() + 1);
    return MoveAction{};
}

InstructionAction fingerprints::time::year(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(static_cast<int>(ymd().year()));
    return MoveAction{};
}
