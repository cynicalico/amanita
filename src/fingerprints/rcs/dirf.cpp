#include "fingerprints/rcs/dirf.hpp"
#include <filesystem>
#include "instruction_pointer.hpp"

InstructionAction dirf::cd(Fungespace &, InstructionPointer &ip) {
    const auto dirname = ip.pop_0gnirts();
    std::error_code ec;
    std::filesystem::current_path(dirname, ec);
    if (ec) ip.reflect();
    return MoveAction{};
}

InstructionAction dirf::mkdir(Fungespace &, InstructionPointer &ip) {
    const auto dirname = ip.pop_0gnirts();
    if (std::error_code ec; !std::filesystem::create_directory(dirname, ec) || ec) ip.reflect();
    return MoveAction{};
}

InstructionAction dirf::rmdir(Fungespace &, InstructionPointer &ip) {
    const auto dirname = ip.pop_0gnirts();
    if (std::error_code ec; !std::filesystem::remove(dirname, ec) || ec) ip.reflect();
    return MoveAction{};
}
