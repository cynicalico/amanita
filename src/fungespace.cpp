#include "fungespace.hpp"
#include <fmt/format.h>
#include <fmt/std.h>
#include <fstream>

Fungespace::Fungespace(const std::filesystem::path &path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error(fmt::format("Failed to open file: '{}'", path));

    std::string line;
    while (std::getline(file, line)) {
        auto ret = std::ranges::remove_if(line, [](const char c) {
            return c == '\n' || c == '\r' || c == '\f';
        });
        line.erase(ret.begin(), ret.end());

        px_py_.emplace_back();
        px_py_.reserve(line.size());
        for (const auto &c: line)
            px_py_.back().push_back(static_cast<unsigned char>(c));

        max_coord[0] = std::max(max_coord[0], static_cast<std::int64_t>(line.size()));
        max_coord[1]++;
    }
}

Cell Fungespace::get(std::int64_t x, std::int64_t y) const {
    if (!in_bounds(x, y))
        return EMPTY;

    const auto coord = make_fixed_coord_(x, y);
    if (coord.y >= coord.quadrant.size())
        return EMPTY;
    if (coord.x >= coord.quadrant[coord.y].size())
        return EMPTY;

    return coord.quadrant[coord.y][coord.x];
}

void Fungespace::put(std::int64_t x, std::int64_t y, Cell v) {
    if (v != EMPTY) {
        min_coord[0] = std::min(min_coord[0], x);
        min_coord[1] = std::min(min_coord[1], y);
        max_coord[0] = std::max(max_coord[0], x + 1);
        max_coord[1] = std::max(max_coord[1], y + 1);
    }

    const auto coord = make_fixed_coord_(x, y);
    check_resize_(coord);
    coord.quadrant[coord.y][coord.x] = v;

    if (v == EMPTY)
        check_shrink_bounds_(x, y);
}

bool Fungespace::in_bounds(std::int64_t x, std::int64_t y) const {
    return x >= min_coord[0] && y >= min_coord[1] && x < max_coord[0] && y < max_coord[1];
}

void Fungespace::print() const {
    for (std::int64_t y = min_coord[1]; y < max_coord[1]; ++y) {
        for (std::int64_t x = min_coord[0]; x < max_coord[0]; ++x) {
            auto c = static_cast<char>(get(x, y));
            fmt::print("{}", c);
        }
        fmt::println("");
    }
}

Fungespace::FixedCoord_ Fungespace::make_fixed_coord_(std::int64_t x, std::int64_t y) const {
    if (x < 0) {
        if (y < 0) {
            return {.x = static_cast<std::size_t>(-x - 1),
                    .y = static_cast<std::size_t>(-y - 1),
                    .quadrant = const_cast<std::vector<std::vector<Cell>> &>(nx_ny_)};
        }
        return {.x = static_cast<std::size_t>(-x - 1),
                .y = static_cast<std::size_t>(y),
                .quadrant = const_cast<std::vector<std::vector<Cell>> &>(nx_py_)};
    }
    if (y < 0) {
        return {.x = static_cast<std::size_t>(x),
                .y = static_cast<std::size_t>(-y - 1),
                .quadrant = const_cast<std::vector<std::vector<Cell>> &>(px_ny_)};
    }
    return {.x = static_cast<std::size_t>(x),
            .y = static_cast<std::size_t>(y),
            .quadrant = const_cast<std::vector<std::vector<Cell>> &>(px_py_)};
}

void Fungespace::check_resize_(const FixedCoord_ &coord) {
    if (coord.y >= coord.quadrant.size())
        coord.quadrant.resize(coord.y + 1);
    if (coord.x >= coord.quadrant[coord.y].size())
        coord.quadrant[coord.y].resize(coord.x + 1, EMPTY);
}

void Fungespace::check_shrink_bounds_(std::int64_t x, std::int64_t y) {
    // TODO: This is more or less the most naive possible way to implement this
    //       May want to research some way to store some additional data to speed this up

    if (y == min_coord[1]) {
        bool all_empty = true;
        while (min_coord[1] < max_coord[1] && all_empty) {
            for (std::int64_t cx = min_coord[0]; cx < max_coord[0]; ++cx) {
                if (get(cx, min_coord[1]) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                min_coord[1]++;
        }
    }

    if (x == min_coord[0]) {
        bool all_empty = true;
        while (min_coord[0] < max_coord[0] && all_empty) {
            for (std::int64_t cy = min_coord[1]; cy < max_coord[1]; ++cy) {
                if (get(min_coord[0], cy) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                min_coord[0]++;
        }
    }

    if (y == max_coord[1] - 1) {
        bool all_empty = true;
        while (max_coord[1] >= min_coord[1] && all_empty) {
            for (std::int64_t cx = min_coord[0]; cx < max_coord[0]; ++cx) {
                if (get(cx, max_coord[1] - 1) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                max_coord[1]--;
        }
    }

    if (x == max_coord[0] - 1) {
        bool all_empty = true;
        while (max_coord[0] >= min_coord[0] && all_empty) {
            for (std::int64_t cy = min_coord[1]; cy < max_coord[1]; ++cy) {
                if (get(max_coord[0] - 1, cy) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                max_coord[0]--;
        }
    }
}
