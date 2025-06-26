#include "fungespace.hpp"
#include "sops.hpp"
#include <fmt/format.h>
#include <fmt/std.h>
#include <fstream>

constexpr std::size_t CHUNK_SIZE = 1024;

Fungespace::Fungespace(const std::filesystem::path &path) {
    std::int64_t unused[2];
    input_file(path.string(), 0, 0, 0, unused);
}

bool Fungespace::input_file(const std::string &filename, const std::int64_t flags, const std::int64_t x,
                            const std::int64_t y,
                            std::int64_t size[2]) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    const bool binary_mode = (flags & 0b1) == 1;

    std::int64_t input_pos[2] = {x, y};
    size[0] = 0;
    size[1] = 0;

    do {
        unsigned char buf[CHUNK_SIZE];
        file.read(reinterpret_cast<char *>(buf), sizeof(buf));
        for (std::size_t i = 0; i < file.gcount(); ++i) {
            if (!binary_mode && (buf[i] == '\r' || buf[i] == '\f'))
                continue;

            if (!binary_mode && buf[i] == '\n') {
                size[0] = std::max(size[0], input_pos[0] - x);
                input_pos[0] = x;

                size[1]++;
                input_pos[1]++;

                continue;
            }

            if (buf[i] != EMPTY)
                put(input_pos[0], input_pos[1], buf[i]);
            input_pos[0]++;
        }
    } while (file.gcount() == CHUNK_SIZE);

    return true;
}

bool Fungespace::output_file(const std::string &filename, const std::int64_t flags, const std::int64_t x,
                             const std::int64_t y,
                             const std::int64_t w, const std::int64_t h) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    const bool linear_mode = (flags & 0b1) == 1;

    for (std::int64_t oy = y; oy < y + h; ++oy) {
        std::string line;

        for (std::int64_t ox = x; ox < x + w; ++ox) {
            line += static_cast<unsigned char>(get(ox, oy));
        }

        if (linear_mode) {
            rtrim(line);
            if (oy < y + h - 1)
                line += "\n";
        } else
            line += "\n";

        file << line;
    }

    return true;
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
            return {
                .x = static_cast<std::size_t>(-x - 1),
                .y = static_cast<std::size_t>(-y - 1),
                .quadrant = const_cast<std::vector<std::vector<Cell> > &>(nx_ny_)
            };
        }
        return {
            .x = static_cast<std::size_t>(-x - 1),
            .y = static_cast<std::size_t>(y),
            .quadrant = const_cast<std::vector<std::vector<Cell> > &>(nx_py_)
        };
    }
    if (y < 0) {
        return {
            .x = static_cast<std::size_t>(x),
            .y = static_cast<std::size_t>(-y - 1),
            .quadrant = const_cast<std::vector<std::vector<Cell> > &>(px_ny_)
        };
    }
    return {
        .x = static_cast<std::size_t>(x),
        .y = static_cast<std::size_t>(y),
        .quadrant = const_cast<std::vector<std::vector<Cell> > &>(px_py_)
    };
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
