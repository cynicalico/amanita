#pragma once

#include "instruction.hpp"
#include "vec.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace amanita {
constexpr std::int64_t CARRIAGE_RETURN = '\r';
constexpr std::int64_t NEWLINE = '\n';
constexpr std::int64_t FORM_FEED = '\f';
constexpr std::int64_t EMPTY = 32;

/*       ^ -y
 *       |
 * <----------->
 * -x    |    +x
 *       v +y
 */

class Fungespace {
    using Quadrant = std::vector<std::vector<std::int64_t>>;

    using CoordCounts = std::unordered_map<std::int64_t, std::size_t>;
    static constexpr auto CmpKeyLess = [](const CoordCounts::value_type &a, const CoordCounts::value_type &b) {
        return a.first < b.first;
    };

public:
    Fungespace();
    explicit Fungespace(const std::filesystem::path &path);

    bool input_file(const std::string &filename, std::int64_t flags, const Vec &origin, Vec &size);
    bool output_file(const std::string &filename, std::int64_t flags, const Vec &origin, const Vec &size) const;

    bool is_in_bounds(const Vec &v) const;

    Vec min_coord() const;
    Vec max_coord() const;

    std::int64_t get(const Vec &v) const;
    Instruction get_ins(const Vec &v) const;
    void put(const Vec &v, std::int64_t value);

private:
    Quadrant pos_x_pos_y_{};
    Quadrant pos_x_neg_y_{};
    Quadrant neg_x_pos_y_{};
    Quadrant neg_x_neg_y_{};

    struct FixedCoord_ {
        Quadrant &quadrant;
        std::size_t x{}, y{};
    };
    FixedCoord_ get_fixed_coord_(const Vec &v) const;
    void check_resize_(const FixedCoord_ &coord);

    CoordCounts x_counts_{}, y_counts_{};
    Vec min_coord_{}, max_coord_{};
    void check_shrink_bounds_(const Vec &v);
    void check_expand_bounds_(const Vec &v);
};
} // namespace amanita
