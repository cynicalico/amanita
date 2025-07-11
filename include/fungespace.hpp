#ifndef AMANITA_FUNGESPACE_HPP
#define AMANITA_FUNGESPACE_HPP

#include <cstdint>
#include <filesystem>
#include <vector>

/*       ^ -y
 *       |
 * <----------->
 * -x    |    +x
 *       v +y
 */

using Cell = std::int64_t;

constexpr Cell CARRIAGE_RETURN = '\r';
constexpr Cell NEWLINE = '\n';
constexpr Cell FORM_FEED = '\f';
constexpr Cell EMPTY = 32;

class Fungespace {
public:
    std::int64_t min_coord[2]{0, 0};
    std::int64_t max_coord[2]{0, 0};

    explicit Fungespace(const std::filesystem::path &path);

    bool
    input_file(const std::string &filename, std::int64_t flags, std::int64_t x, std::int64_t y, std::int64_t size[2]);

    bool output_file(
            const std::string &filename,
            std::int64_t flags,
            std::int64_t x,
            std::int64_t y,
            std::int64_t w,
            std::int64_t h);

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

    FixedCoord_ make_fixed_coord_(std::int64_t x, std::int64_t y) const;
    void check_resize_(const FixedCoord_ &coord);
    void check_shrink_bounds_(std::int64_t x, std::int64_t y);
};

#endif // AMANITA_FUNGESPACE_HPP
