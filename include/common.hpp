#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "instructions.hpp"
#include "mizu/util/platform.hpp"

#if defined(MIZU_PLATFORM_WINDOWS)
#include <winsock2.h>
#endif

/*********
 * TYPES *
 *********/

using Index = std::int64_t;
using Cell = std::int64_t;
using Id = std::int64_t;

/*******
 * VEC *
 *******/

struct Vec {
    Cell x;
    Cell y;

    constexpr Vec()
        : x{0}, y{0} {}

    constexpr Vec(const Cell x, const Cell y)
        : x(x), y(y) {}

    Vec operator+(const Vec &other) const { return {x + other.x, y + other.y}; }
    Vec operator-(const Vec &other) const { return {x - other.x, y - other.y}; }
    Vec operator*(const Vec &other) const { return {x * other.x, y * other.y}; }
    Vec operator*(const Cell other) const { return {x * other, y * other}; }
    Vec operator/(const Vec &other) const { return {x / other.x, y / other.y}; }

    void operator+=(const Vec &other) {
        x += other.x;
        y += other.y;
    }
    void operator-=(const Vec &other) {
        x -= other.x;
        y -= other.y;
    }
    void operator*=(const Vec &other) {
        x *= other.x;
        y *= other.y;
    }
    void operator*=(const Cell other) {
        x *= other;
        y *= other;
    }
    void operator/=(const Vec &other) {
        x /= other.x;
        y /= other.y;
    }
};

/*************
 * CONSTANTS *
 *************/

constexpr Cell CARRIAGE_RETURN = '\r';
constexpr Cell NEWLINE = '\n';
constexpr Cell FORM_FEED = '\f';
constexpr Cell EMPTY = 32;

constexpr auto ZERO = Vec(0, 0);

constexpr auto SOUTH = Vec(0, 1);
constexpr auto EAST = Vec(1, 0);
constexpr auto NORTH = Vec(0, -1);
constexpr auto WEST = Vec(-1, 0);

/************
 * CLI ARGS *
 ************/

struct CliArgs {
    std::vector<std::string> args;

    explicit CliArgs(std::vector<std::string> args)
        : args(std::move(args)) {}
};

/*********
 * STATE *
 *********/

using Clock = std::chrono::steady_clock;

struct State {
    std::unique_ptr<CliArgs> cli_args{nullptr};

    struct {
        std::unordered_map<Id, Clock::time_point> marks{};
    } hrti;

    struct {
        std::vector<Vec> references{};
    } refc;

    struct File { // For FILE
        Vec io_buffer_pos{ZERO};
        FILE *f{nullptr};
    };

    struct {
        std::unordered_map<Cell, File> open_files{};
    } file;

    struct {
        bool utc{false};
    } time;

    struct {
#if defined(MIZU_PLATFORM_WINDOWS)
        bool initialized{false};
        WSADATA wsa_data{};
        std::unordered_map<Cell, SOCKET> sockets{};
#else
        std::unordered_map<Cell, int> sockets{};
#endif
    } sock;
};

/***********************
 * INSTRUCTION ACTIONS *
 ***********************/

struct IterAction;

struct KillAction {};

struct MoveAction {};

struct SplitAction {};

struct QuitAction {
    int exit_code;
};

using InstructionAction = std::variant<IterAction, KillAction, MoveAction, SplitAction, QuitAction>;

struct IterAction {
    std::vector<InstructionAction> actions;
};

/****************
 * FINGERPRINTS *
 ****************/

class Fungespace;
class InstructionPointer;

using InstructionFunc = std::function<InstructionAction(State &, Fungespace &, InstructionPointer &)>;
using InstructionMapping = std::unordered_map<Instruction, InstructionFunc>;

struct Fingerprint {
    const char *name;
    std::int64_t id;
    InstructionMapping fns;
};

/***********
 * HELPERS *
 ***********/

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
