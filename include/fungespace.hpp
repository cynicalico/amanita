#ifndef AMANITA_FUNGESPACE_HPP
#define AMANITA_FUNGESPACE_HPP

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>
#include "common.hpp"

/*       ^ -y
 *       |
 * <----------->
 * -x    |    +x
 *       v +y
 */

class Fungespace {
public:
    Vec min_coord{ZERO};
    Vec max_coord{ZERO};

    Fungespace();
    explicit Fungespace(const std::filesystem::path &path);

    bool input_file(const std::string &filename, std::int64_t flags, std::int64_t x, std::int64_t y, Vec &size);

    bool output_file(
            const std::string &filename,
            std::int64_t flags,
            std::int64_t x,
            std::int64_t y,
            std::int64_t w,
            std::int64_t h);

    void save_bak();
    void reset();

    Cell get(Index x, Index y) const;
    void put(Index x, Index y, Cell v);

    bool in_bounds(Index x, Index y) const;

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

    Vec min_coord_bak_{ZERO};
    Vec max_coord_bak_{ZERO};
    std::vector<std::vector<Cell>> px_py_bak_{};

    FixedCoord_ make_fixed_coord_(Index x, Index y) const;
    void check_resize_(const FixedCoord_ &coord);
    void check_shrink_bounds_(Index x, Index y);
};

#endif // AMANITA_FUNGESPACE_HPP
