#include "vec.hpp"

const amanita::Vec amanita::Vec::ZERO = Vec(0, 0);
const amanita::Vec amanita::Vec::SOUTH = Vec(0, 1);
const amanita::Vec amanita::Vec::NORTH = Vec(0, -1);
const amanita::Vec amanita::Vec::EAST = Vec(1, 0);
const amanita::Vec amanita::Vec::WEST = Vec(-1, 0);

amanita::Vec amanita::Vec::operator+(const Vec &other) const {
    return {x + other.x, y + other.y};
}

void amanita::Vec::operator+=(const Vec &other) {
    x += other.x;
    y += other.y;
}

amanita::Vec amanita::Vec::operator-() const {
    return {-x, -y};
}

amanita::Vec amanita::Vec::operator-(const Vec &other) const {
    return {x - other.x, y - other.y};
}

void amanita::Vec::operator-=(const Vec &other) {
    x -= other.x;
    y -= other.y;
}

amanita::Vec amanita::Vec::operator*(const Vec &other) const {
    return {x * other.x, y * other.y};
}

void amanita::Vec::operator*=(const Vec &other) {
    x *= other.x;
    y *= other.y;
}

amanita::Vec amanita::Vec::operator*(const std::int64_t other) const {
    return {x * other, y * other};
}

void amanita::Vec::operator*=(const std::int64_t other) {
    x *= other;
    y *= other;
}

amanita::Vec amanita::Vec::operator/(const Vec &other) const {
    return {x / other.x, y / other.y};
}

void amanita::Vec::operator/=(const Vec &other) {
    x /= other.x;
    y /= other.y;
}

bool amanita::operator==(const Vec &lhs, const Vec &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool amanita::operator!=(const Vec &lhs, const Vec &rhs) {
    return !(lhs == rhs);
}
