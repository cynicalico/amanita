#include "fingerprints/rcs/dirf.hpp"
#include <filesystem>
#include "instruction_pointer.hpp"

InstructionAction fingerprints::dirf::cd(State &, Fungespace &, InstructionPointer &ip) {
    const auto dirname = ip.pop_0gnirts();
    std::error_code ec;
    std::filesystem::current_path(dirname, ec);
    if (ec) ip.reflect();
    return MoveAction{};
}

InstructionAction fingerprints::dirf::mkdir(State &, Fungespace &, InstructionPointer &ip) {
    const auto dirname = ip.pop_0gnirts();
    if (std::error_code ec; !std::filesystem::create_directory(dirname, ec) || ec) ip.reflect();
    return MoveAction{};
}

InstructionAction fingerprints::dirf::rmdir(State &, Fungespace &, InstructionPointer &ip) {
    const auto dirname = ip.pop_0gnirts();
    if (std::error_code ec; !std::filesystem::remove(dirname, ec) || ec) ip.reflect();
    return MoveAction{};
}
