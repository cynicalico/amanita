#include <filesystem>
#include <fmt/format.h>
#include <vector>

using Cell = std::int64_t;

class Fungespace {
public:
    explicit Fungespace(const std::filesystem::path &path);

    Cell get(std::int64_t x, std::int64_t y) const;
    void put(std::int64_t x, std::int64_t y);

private:
    struct FixedCoord_ {
        std::size_t x;
        std::size_t y;
        std::vector<Cell> &quadrant;
    };

    /*          ^ -y
     *          |
     *          |
     * <------------------->
     * -x       |         +x
     *          |
     *          v +y
     */
    std::vector<Cell> px_py_{};
    std::vector<Cell> px_ny_{};
    std::vector<Cell> nx_py_{};
    std::vector<Cell> nx_ny_{};

    std::int64_t min_coord_[2]{0, 0};
    std::int64_t max_coord_[2]{0, 0};

    FixedCoord_ make_fixed_coord_(std::int64_t x, std::int64_t y) const;
    void check_resize_(const FixedCoord_ &coord);
};

Fungespace::Fungespace(const std::filesystem::path &path) {
    // TODO
}

Cell Fungespace::get(std::int64_t x, std::int64_t y) const {
    auto coord = make_fixed_coord_(x, y);
    fmt::println("{} {}", coord.x, coord.y);

    return 0;
}

void Fungespace::put(std::int64_t x, std::int64_t y) {}

Fungespace::FixedCoord_ Fungespace::make_fixed_coord_(std::int64_t x, std::int64_t y) const {
    if (x < 0) {
        if (y < 0) {
            return FixedCoord_{
                    .x = static_cast<std::size_t>(-x - 1),
                    .y = static_cast<std::size_t>(-y - 1),
                    .quadrant = const_cast<std::vector<Cell> &>(nx_ny_)};
        }
        return FixedCoord_{
                .x = static_cast<std::size_t>(-x - 1),
                .y = static_cast<std::size_t>(y),
                .quadrant = const_cast<std::vector<Cell> &>(nx_py_)};
    }
    if (y < 0) {
        return FixedCoord_{
                .x = static_cast<std::size_t>(x),
                .y = static_cast<std::size_t>(-y - 1),
                .quadrant = const_cast<std::vector<Cell> &>(px_ny_)};
    }
    return FixedCoord_{
            .x = static_cast<std::size_t>(x),
            .y = static_cast<std::size_t>(y),
            .quadrant = const_cast<std::vector<Cell> &>(px_py_)};
}

void Fungespace::check_resize_(const FixedCoord_ &coord) {}

int main() {
    auto F = Fungespace("");
    F.get(-2, -3);
}
