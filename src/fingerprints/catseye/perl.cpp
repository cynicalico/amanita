#include "fingerprints/catseye/perl.hpp"
#include <iomanip>
#include <ranges>
#include <sstream>
#include <string>
#include "instruction_pointer.hpp"
#include "subprocess.h"

InstructionAction perl::shelled(Fungespace &, InstructionPointer &ip) {
    ip.push(1);
    return MoveAction{};
}

InstructionAction perl::eval(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.stack.pop_0gnirts();

    std::stringstream ss2;
    ss2 << "print eval(" << std::quoted(s) << ")";
    const auto user_code = ss2.str();

    const char *cmd[5] = {"perl", "-e", user_code.c_str(), nullptr};
    subprocess_s subp{};
    if (subprocess_create(
                cmd,
                subprocess_option_no_window | subprocess_option_search_user_path |
                        subprocess_option_combined_stdout_stderr,
                &subp) != 0) {
        ip.reflect();
        return MoveAction{};
    }
    if (subprocess_join(&subp, nullptr) != 0) {
        subprocess_destroy(&subp);
        ip.reflect();
        return MoveAction{};
    }

    std::string out;
    char buf[1024];
    FILE *fp = subprocess_stdout(&subp);
    while (const auto *l = fgets(buf, sizeof(buf), fp)) out += l;

    subprocess_destroy(&subp);

    ip.push('\0');
    for (const auto &c: out | std::views::reverse) ip.push(c);

    return MoveAction{};
}

InstructionAction perl::int_eval(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.stack.pop_0gnirts();

    std::stringstream ss2;
    ss2 << "print eval(" << std::quoted(s) << ")";
    const auto user_code = ss2.str();

    const char *cmd[5] = {"perl", "-e", user_code.c_str(), nullptr};
    subprocess_s subp{};
    if (subprocess_create(
                cmd,
                subprocess_option_no_window | subprocess_option_search_user_path |
                        subprocess_option_combined_stdout_stderr,
                &subp) != 0) {
        ip.reflect();
        return MoveAction{};
    }
    if (subprocess_join(&subp, nullptr) != 0) {
        subprocess_destroy(&subp);
        ip.reflect();
        return MoveAction{};
    }

    std::string out;
    char buf[1024];
    FILE *fp = subprocess_stdout(&subp);
    while (const auto *l = fgets(buf, sizeof(buf), fp)) out += l;

    subprocess_destroy(&subp);

    try {
        const auto i = std::stoi(out);
        ip.push(i);
    } catch (const std::exception &) { ip.reflect(); }

    return MoveAction{};
}
