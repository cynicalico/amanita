#include "fingerprints/rcs/date.hpp"
#include <chrono>
#include "instruction_pointer.hpp"

InstructionAction date::add_days(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto n_days = ip.pop();
    const auto d = ip.pop();
    const auto m = ip.pop();
    const auto y = ip.pop();

    if (y <= 0 || m <= 0 || d <= 0) {
        ip.reflect();
        return MoveAction{};
    }

    auto tp = sys_days{
            year{static_cast<int>(y)} / month{static_cast<unsigned int>(m)} / day{static_cast<unsigned int>(d)}};
    if (n_days > 0) tp -= days{static_cast<unsigned int>(std::abs(n_days))};
    else tp += days{static_cast<unsigned int>(n_days)};

    year_month_day ymd{round<days>(tp)};

    ip.push(static_cast<int>(ymd.year()));
    ip.push(static_cast<unsigned int>(ymd.month()));
    ip.push(static_cast<unsigned int>(ymd.day()));

    return MoveAction{};
}

InstructionAction date::julian_to_calendar(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto J = ip.pop();

    system_clock::time_point tp;
    if (J > 0) tp = sys_days{November / 24 / -4713};
    else tp = sys_days{November / 24 / -4714};
    tp += days{static_cast<int>(J)};
    year_month_day ymd{round<days>(tp)};

    ip.push(static_cast<int>(ymd.year()));
    ip.push(static_cast<unsigned int>(ymd.month()));
    ip.push(static_cast<unsigned int>(ymd.day()));

    return MoveAction{};
}

InstructionAction date::days_difference(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto d2 = ip.pop();
    const auto m2 = ip.pop();
    const auto y2 = ip.pop();
    const auto d1 = ip.pop();
    const auto m1 = ip.pop();
    const auto y1 = ip.pop();

    if (y1 <= 0 || y2 <= 0 || m1 <= 0 || d1 <= 0 || m2 <= 0 || d2 <= 0) {
        ip.reflect();
        return MoveAction{};
    }

    const auto tp1 = sys_days{
            year{static_cast<int>(y1)} / month{static_cast<unsigned int>(m1)} / day{static_cast<unsigned int>(d1)}};
    const auto tp2 = sys_days{
            year{static_cast<int>(y2)} / month{static_cast<unsigned int>(m2)} / day{static_cast<unsigned int>(d2)}};
    const auto diff = tp1 - tp2;

    ip.push(duration_cast<days>(diff).count());

    return MoveAction{};
}

InstructionAction date::calendar_to_julian(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto d = ip.pop();
    const auto m = ip.pop();
    const auto y = ip.pop();

    if (m <= 0 || d <= 0) {
        ip.reflect();
        return MoveAction{};
    }

    system_clock::time_point epoch;
    if (y < 0) epoch = sys_days{November / 24 / -4714};
    else epoch = sys_days{November / 24 / -4713};
    year_month_day ymd{
            year{static_cast<int>(y)}, month{static_cast<unsigned int>(m)}, day{static_cast<unsigned int>(d)}};
    const auto tp = sys_days{ymd};
    const auto julian_day = duration_cast<days>(tp - epoch).count();
    ip.push(julian_day);

    return MoveAction{};
}

InstructionAction date::yd_to_ymd(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto d = ip.pop();
    const auto y = ip.pop();

    auto tp = sys_days{year{static_cast<int>(y)} / 1 / 1};
    tp += days{static_cast<int>(d)};
    year_month_day ymd{round<days>(tp)};

    if (static_cast<int>(ymd.year()) != static_cast<int>(y)) {
        ip.reflect();
        return MoveAction{};
    }

    ip.push(static_cast<int>(ymd.year()));
    ip.push(static_cast<unsigned int>(ymd.month()));
    ip.push(static_cast<unsigned int>(ymd.day()));

    return MoveAction{};
}

InstructionAction date::day_of_week(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto d = ip.pop();
    const auto m = ip.pop();
    const auto y = ip.pop();

    const year_month_day ymd{
            year{static_cast<int>(y)}, month{static_cast<unsigned int>(m)}, day{static_cast<unsigned int>(d)}};
    if (y == 0 || !ymd.ok()) ip.reflect();
    else if (const auto wd = weekday{ymd}.c_encoding(); wd == 0) ip.push(6);
    else ip.push(wd - 1);

    return MoveAction{};
}

InstructionAction date::day_of_year(Fungespace &, InstructionPointer &ip) {
    using namespace std;
    using namespace chrono;

    const auto d = ip.pop();
    const auto m = ip.pop();
    const auto y = ip.pop();

    const auto ymd =
            year{static_cast<int>(y)} / month{static_cast<unsigned int>(m)} / day{static_cast<unsigned int>(d)};
    if (y == 0 || !ymd.ok()) {
        ip.reflect();
    } else {
        const auto diff = sys_days{ymd} - sys_days{year{static_cast<int>(y)} / 1 / 1};
        ip.push(duration_cast<days>(diff).count());
    }

    return MoveAction{};
}
