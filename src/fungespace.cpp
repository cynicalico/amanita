#include "fungespace.hpp"
#include <fmt/format.h>
#include <fmt/std.h>
#include <fstream>
#include "sops.hpp"

constexpr std::size_t CHUNK_SIZE = 1024;

Fungespace::Fungespace() = default;

Fungespace::Fungespace(const std::filesystem::path &path) {
    Vec unused{ZERO};
    if (!input_file(path.string(), 0, 0, 0, unused))
        throw std::runtime_error(fmt::format("Failed to open file: '{}'", path));
}

bool Fungespace::input_file(
        const std::string &filename, const std::int64_t flags, const std::int64_t x, const std::int64_t y, Vec &size) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    const bool binary_mode = (flags & 0b1) == 1;

    Vec input_pos(x, y);
    size.x = 0;
    size.y = 0;

    do {
        unsigned char buf[CHUNK_SIZE];
        file.read(reinterpret_cast<char *>(buf), sizeof(buf));
        for (std::size_t i = 0; i < file.gcount(); ++i) {
            if (!binary_mode && (buf[i] == CARRIAGE_RETURN || buf[i] == FORM_FEED))
                continue;

            if (!binary_mode && buf[i] == NEWLINE) {
                size.x = std::max(size.x, input_pos.x - x);
                input_pos.x = x;

                size.y++;
                input_pos.y++;

                continue;
            }

            if (buf[i] != EMPTY)
                put(input_pos.x, input_pos.y, buf[i]);
            input_pos.x++;
        }
    } while (file.gcount() == CHUNK_SIZE);

    return true;
}

bool Fungespace::output_file(
        const std::string &filename,
        const std::int64_t flags,
        const std::int64_t x,
        const std::int64_t y,
        const std::int64_t w,
        const std::int64_t h) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    const bool linear_mode = (flags & 0b1) == 1;

    for (std::int64_t oy = y; oy < y + h; ++oy) {
        std::string line;

        for (std::int64_t ox = x; ox < x + w; ++ox)
            line += static_cast<unsigned char>(get(ox, oy));

        if (linear_mode) {
            rtrim(line);
            if (oy < y + h - 1)
                line += static_cast<unsigned char>(NEWLINE);
        } else {
            line += static_cast<unsigned char>(NEWLINE);
        }

        file << line;
    }

    return true;
}

void Fungespace::save_bak() {
    min_coord_bak_ = min_coord;
    max_coord_bak_ = max_coord;
    px_py_bak_ = px_py_;
    // Negative quadrants can't be saved, runtime only
}

void Fungespace::reset() {
    px_py_ = px_py_bak_;
    px_ny_.clear();
    nx_py_.clear();
    nx_ny_.clear();
    min_coord = min_coord_bak_;
    max_coord = max_coord_bak_;
}

Cell Fungespace::get(Index x, Index y) const {
    if (!in_bounds(x, y))
        return EMPTY;

    const auto coord = make_fixed_coord_(x, y);
    if (coord.y >= coord.quadrant.size())
        return EMPTY;
    if (coord.x >= coord.quadrant[coord.y].size())
        return EMPTY;

    return coord.quadrant[coord.y][coord.x];
}

void Fungespace::put(Index x, Index y, Cell v) {
    if (v != EMPTY) {
        min_coord.x = std::min(min_coord.x, x);
        min_coord.y = std::min(min_coord.y, y);
        max_coord.x = std::max(max_coord.x, x + 1);
        max_coord.y = std::max(max_coord.y, y + 1);
    }

    const auto coord = make_fixed_coord_(x, y);
    check_resize_(coord);
    coord.quadrant[coord.y][coord.x] = v;

    if (v == EMPTY)
        check_shrink_bounds_(x, y);
}

bool Fungespace::in_bounds(Index x, Index y) const {
    return x >= min_coord.x && y >= min_coord.y && x < max_coord.x && y < max_coord.y;
}

void Fungespace::print() const {
    for (Cell y = min_coord.y; y < max_coord.y; ++y) {
        for (Cell x = min_coord.x; x < max_coord.x; ++x) {
            auto c = static_cast<char>(get(static_cast<Index>(x), static_cast<Index>(y)));
            fmt::print("{}", c);
        }
        fmt::println("");
    }
}

Fungespace::FixedCoord_ Fungespace::make_fixed_coord_(Index x, Index y) const {
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

void Fungespace::check_shrink_bounds_(Index x, Index y) {
    // TODO: This is more or less the most naive possible way to implement this
    //       May want to research some way to store some additional data to speed this up

    if (y == min_coord.y) {
        bool all_empty = true;
        while (min_coord.y < max_coord.y && all_empty) {
            for (std::int64_t cx = min_coord.x; cx < max_coord.x; ++cx) {
                if (get(cx, min_coord.y) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                min_coord.y++;
        }
    }

    if (x == min_coord.x) {
        bool all_empty = true;
        while (min_coord.x < max_coord.x && all_empty) {
            for (std::int64_t cy = min_coord.y; cy < max_coord.y; ++cy) {
                if (get(min_coord.x, cy) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                min_coord.x++;
        }
    }

    if (y == max_coord.y - 1) {
        bool all_empty = true;
        while (max_coord.y >= min_coord.y && all_empty) {
            for (std::int64_t cx = min_coord.x; cx < max_coord.x; ++cx) {
                if (get(cx, max_coord.y - 1) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                max_coord.y--;
        }
    }

    if (x == max_coord.x - 1) {
        bool all_empty = true;
        while (max_coord.x >= min_coord.x && all_empty) {
            for (std::int64_t cy = min_coord.y; cy < max_coord.y; ++cy) {
                if (get(max_coord.x - 1, cy) != EMPTY) {
                    all_empty = false;
                    break;
                }
            }
            if (all_empty)
                max_coord.x--;
        }
    }
}
