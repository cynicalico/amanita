#ifndef AMANITA_FUNGESPACE_HPP
#define AMANITA_FUNGESPACE_HPP

#include <filesystem>
#include <vector>

/*       ^ -y
 *       |
 * <----------->
 * -x    |    +x
 *       v +y
 */

using Cell = std::int64_t;
constexpr Cell EMPTY = 32;

class Fungespace {
public:
    explicit Fungespace(const std::filesystem::path &path);

    Cell get(std::int64_t x, std::int64_t y) const;
    void put(std::int64_t x, std::int64_t y, Cell v);

    bool in_bounds(std::int64_t x, std::int64_t y) const;

    void print() const;

private:
    struct FixedCoord_ {
        std::size_t x;
        std::size_t y;
        std::vector<std::vector<Cell>> &quadrant;
    };

    std::vector<std::vector<Cell>> px_py_{};
    std::vector<std::vector<Cell>> px_ny_{};
    std::vector<std::vector<Cell>> nx_py_{};
    std::vector<std::vector<Cell>> nx_ny_{};

    std::int64_t min_coord_[2]{0, 0};
    std::int64_t max_coord_[2]{0, 0};

    FixedCoord_ make_fixed_coord_(std::int64_t x, std::int64_t y) const;
    void check_resize_(const FixedCoord_ &coord);
};

#endif // AMANITA_FUNGESPACE_HPP
