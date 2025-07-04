#include "fingerprints/rcs/evar.hpp"
#include <cstdlib>
#include "instruction_pointer.hpp"

extern char **environ;

InstructionAction evar::get(Fungespace &, InstructionPointer &ip) {
    const auto name = ip.stack.pop_0gnirts();

    for (char **current = environ; *current; ++current) {
        char *c = *current;
        std::size_t i = 0;
        // Compare to name
        for (; *c && i < name.size(); ++i, ++c)
            if (*c != name[i])
                break;

        // Didn't match, move on
        if (i != name.size() || (*c && *c != '='))
            continue;
        c++; // Move past = sign

        // Read the value backwards
        const std::size_t start = strlen(c);
        for (i = start; i-- > 0;)
            ip.stack.push(c[i]);

        return MoveAction{};
    }

    ip.reflect();
    return MoveAction{};
}

InstructionAction evar::count(Fungespace &, InstructionPointer &ip) {
    std::int64_t n = 0;
    for (char **current = environ; *current; ++current)
        n++;
    ip.stack.push(n);
    return MoveAction{};
}

InstructionAction evar::put(Fungespace &, InstructionPointer &ip) {
    const auto keyval = ip.stack.pop_0gnirts();
    if (_putenv(keyval.c_str()) == -1)
        ip.reflect();
    return MoveAction{};
}

InstructionAction evar::get_nth(Fungespace &, InstructionPointer &ip) {
    const auto nth = ip.stack.pop();

    std::int64_t n = 0;
    for (char **current = environ; *current; ++current, ++n) {
        if (n == nth) {
            char *c = *current;
            // Skip past the key
            for (; *c && *c != '='; ++c)
                ;
            c++; // Move past = sign

            // Read the value backwards
            const std::size_t start = strlen(c);
            for (std::size_t i = start; i-- > 0;)
                ip.stack.push(c[i]);

            return MoveAction{};
        }
    }

    ip.reflect();
    return MoveAction{};
}
