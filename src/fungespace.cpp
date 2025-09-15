#include "fungespace.hpp"

#include "sops.hpp"

#include <fmt/format.h>
#include <fmt/std.h>

#include <fstream>
#include <ranges>

constexpr std::size_t CHUNK_SIZE = 1024;

bool amanita::Fungespace::input_file(
        const std::string &filename,
        const std::vector<std::filesystem::path> &include_paths,
        const std::int64_t flags,
        const Vec &origin,
        Vec &size) {
    std::ifstream file;
    for (const auto &base_path: include_paths) {
        file.open(base_path / filename, std::ios::binary);
        if (file.is_open())
            break;
        file.clear();
    }
    if (!file.is_open())
        return false;

    const bool binary_mode = (flags & 0b1) == 1;

    Vec curr_pos = origin;
    size.x = 0;
    size.y = 0;

    do {
        unsigned char buf[CHUNK_SIZE];
        file.read(reinterpret_cast<char *>(buf), sizeof(buf));
        for (std::size_t i = 0; i < file.gcount(); ++i) {
            if (!binary_mode && (buf[i] == CARRIAGE_RETURN || buf[i] == FORM_FEED))
                continue;

            if (!binary_mode && buf[i] == NEWLINE) {
                size.x = std::max(size.x, curr_pos.x - origin.x);
                curr_pos.x = origin.x;

                size.y++;
                curr_pos.y++;

                continue;
            }

            if (buf[i] != EMPTY)
                put(curr_pos, buf[i]);
            curr_pos.x++;
        }
    } while (file.gcount() == CHUNK_SIZE);

    return true;
}

bool amanita::Fungespace::output_file(
        const std::string &filename, const std::int64_t flags, const Vec &origin, const Vec &size) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    const bool linear_mode = (flags & 0b1) == 1;

    for (std::int64_t y = origin.y; y < origin.y + size.y; ++y) {
        std::string line;

        for (std::int64_t x = origin.x; x < origin.x + size.x; ++x)
            line += static_cast<unsigned char>(get({x, y}) & 0xff);

        if (linear_mode) {
            rtrim(line);
            if (y < origin.y + size.y - 1)
                line += NEWLINE;
        } else {
            line += NEWLINE;
        }

        file << line;
    }

    return true;
}

bool amanita::Fungespace::is_in_bounds(const Vec &v) const {
    return v.x >= min_coord_.x && v.y >= min_coord_.y && v.x < max_coord_.x && v.y < max_coord_.y;
}

amanita::Vec amanita::Fungespace::min_coord() const {
    return min_coord_;
}

amanita::Vec amanita::Fungespace::max_coord() const {
    return max_coord_;
}

std::int64_t amanita::Fungespace::get(const Vec &v) const {
    if (!is_in_bounds(v))
        return EMPTY;

    const auto [quadrant, x, y] = get_fixed_coord_(v);
    if (y >= quadrant.size())
        return EMPTY;
    if (x >= quadrant[y].size())
        return EMPTY;

    return quadrant[y][x];
}

amanita::Instruction amanita::Fungespace::get_ins(const Vec &v) const {
    return static_cast<Instruction>(get(v));
}

void amanita::Fungespace::put(const Vec &v, std::int64_t value) {
    const auto coord = get_fixed_coord_(v);
    check_resize_(coord);

    if (value == EMPTY && coord.quadrant[coord.y][coord.x] != EMPTY)
        check_shrink_bounds_(v);
    else if (value != EMPTY && coord.quadrant[coord.y][coord.x] == EMPTY)
        check_expand_bounds_(v);

    coord.quadrant[coord.y][coord.x] = value;
}

amanita::Fungespace::FixedCoord_ amanita::Fungespace::get_fixed_coord_(const Vec &v) const {
    if (v.x < 0) {
        if (v.y < 0) {
            return {.quadrant = const_cast<Quadrant &>(neg_x_neg_y_),
                    .x = static_cast<std::size_t>(-v.x - 1),
                    .y = static_cast<std::size_t>(-v.y - 1)};
        }
        return {.quadrant = const_cast<Quadrant &>(neg_x_pos_y_),
                .x = static_cast<std::size_t>(-v.x - 1),
                .y = static_cast<std::size_t>(v.y)};
    }
    if (v.y < 0) {
        return {.quadrant = const_cast<Quadrant &>(pos_x_neg_y_),
                .x = static_cast<std::size_t>(v.x),
                .y = static_cast<std::size_t>(-v.y - 1)};
    }
    return {.quadrant = const_cast<Quadrant &>(pos_x_pos_y_),
            .x = static_cast<std::size_t>(v.x),
            .y = static_cast<std::size_t>(v.y)};
}

void amanita::Fungespace::check_resize_(const FixedCoord_ &coord) {
    if (coord.y >= coord.quadrant.size())
        coord.quadrant.resize(coord.y + 1);
    if (coord.x >= coord.quadrant[coord.y].size())
        coord.quadrant[coord.y].resize(coord.x + 1, EMPTY);
}

void amanita::Fungespace::check_shrink_bounds_(const Vec &v) {
#define FIND_SHRINK_MIN(counts, coord)                                                                                 \
    do {                                                                                                               \
        auto valid_coords = counts | std::views::filter([](const auto &x) {                                            \
                                return x.second != 0;                                                                  \
                            });                                                                                        \
        const auto it = std::ranges::min_element(valid_coords, CmpKeyLess);                                            \
        coord = it == valid_coords.end() ? 0 : it->first;                                                              \
    } while (false)

#define FIND_SHRINK_MAX(counts, coord)                                                                                 \
    do {                                                                                                               \
        auto valid_coords = counts | std::views::filter([](const auto &x) {                                            \
                                return x.second != 0;                                                                  \
                            });                                                                                        \
        const auto it = std::ranges::max_element(valid_coords, CmpKeyLess);                                            \
        coord = it == valid_coords.end() ? 0 : it->first + 1;                                                          \
    } while (false)

    x_counts_[v.x]--;
    y_counts_[v.y]--;

    if (min_coord_.x == v.x && x_counts_[v.x] == 0)
        FIND_SHRINK_MIN(x_counts_, min_coord_.x);
    if (min_coord_.y == v.y && y_counts_[v.y] == 0)
        FIND_SHRINK_MIN(y_counts_, min_coord_.y);
    if (max_coord_.x == v.x + 1 && x_counts_[v.x] == 0)
        FIND_SHRINK_MAX(x_counts_, max_coord_.x);
    if (max_coord_.y == v.y + 1 && y_counts_[v.y] == 0)
        FIND_SHRINK_MAX(y_counts_, max_coord_.y);
}

void amanita::Fungespace::check_expand_bounds_(const Vec &v) {
    x_counts_[v.x]++;
    y_counts_[v.y]++;

    min_coord_.x = std::min(min_coord_.x, v.x);
    min_coord_.y = std::min(min_coord_.y, v.y);
    max_coord_.x = std::max(max_coord_.x, v.x + 1);
    max_coord_.y = std::max(max_coord_.y, v.y + 1);
}
