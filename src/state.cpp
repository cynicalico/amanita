#include "state.hpp"

amanita::State::State(std::vector<std::string> args, std::vector<std::filesystem::path> include_paths)
    : status(Status::Running),
      exit_code(0),
      args(std::move(args)),
      include_paths(std::move(include_paths)),
      fungespace(std::make_unique<Fungespace>()) {
    pcg_extras::pcg128_t seed_vals[4];
    auto seed_seq = pcg_extras::seed_seq_from<std::random_device>();
    pcg_extras::generate_to<2>(seed_seq, seed_vals);

    pcg_seed_data.seed = seed_vals[0];
    pcg_seed_data.stream = seed_vals[1];

    pcg_gen = pcg64(pcg_seed_data.seed, pcg_seed_data.stream);
}
