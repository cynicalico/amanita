#pragma once

#include <cstdint>

namespace amanita {
struct Vec {
    const static Vec ZERO;
    const static Vec NORTH;
    const static Vec SOUTH;
    const static Vec EAST;
    const static Vec WEST;

    std::int64_t x;
    std::int64_t y;

    constexpr Vec()
        : x{0},
          y{0} {}

    constexpr Vec(std::int64_t x, std::int64_t y)
        : x(x),
          y(y) {}

    friend bool operator==(const Vec &lhs, const Vec &rhs);
    friend bool operator!=(const Vec &lhs, const Vec &rhs);

    Vec operator+(const Vec &other) const;
    void operator+=(const Vec &other);

    Vec operator-() const;
    Vec operator-(const Vec &other) const;
    void operator-=(const Vec &other);

    Vec operator*(const Vec &other) const;
    void operator*=(const Vec &other);

    Vec operator*(std::int64_t other) const;
    void operator*=(std::int64_t other);

    Vec operator/(const Vec &other) const;
    void operator/=(const Vec &other);
};

bool operator==(const Vec &lhs, const Vec &rhs);
bool operator!=(const Vec &lhs, const Vec &rhs);
} // namespace amanita
