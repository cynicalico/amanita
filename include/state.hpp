#pragma once

#include "fungespace.hpp"
#include "instruction_pointer.hpp"

#include <pcg_random.hpp>

#include <filesystem>
#include <memory>
#include <random>
#include <string>
#include <vector>

namespace amanita {
enum class Status { Running, Stopped };

struct State {
    Status status;
    int exit_code;
    std::vector<std::string> args;
    std::vector<std::filesystem::path> include_paths;

    std::unique_ptr<Fungespace> fungespace;
    std::vector<std::unique_ptr<InstructionPointer>> ips;

    struct {
        pcg_extras::pcg128_t seed{static_cast<pcg_extras::pcg128_t>(0)};
        pcg_extras::pcg128_t stream{static_cast<pcg_extras::pcg128_t>(0)};
    } pcg_seed_data;
    pcg64 pcg_gen;

    State(std::vector<std::string> args, std::vector<std::filesystem::path> include_paths);
};

template<typename T, typename... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

template<typename T>
using IntDist = std::uniform_int_distribution<T>;

template<typename T>
concept IntDistCompatible =
        IsAnyOf<T, short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long>;

template<IntDistCompatible T>
T get(State *state, T low, T high) {
    if (low > high)
        return IntDist<T>(high, low)(state->pcg_gen);
    return IntDist<T>(low, high)(state->pcg_gen);
}
} // namespace amanita
