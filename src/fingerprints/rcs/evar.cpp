#include "fingerprints/rcs/evar.hpp"
#include <cstdlib>
#include <cstring>
#include "instruction_pointer.hpp"
#include "mizu/util/platform.hpp"

extern char **environ;

InstructionAction evar::get(Fungespace &, InstructionPointer &ip) {
    const auto name = ip.pop_0gnirts();

    for (char **current = environ; *current; ++current) {
        char *c = *current;
        std::size_t i = 0;
        // Compare to name
        for (; *c && i < name.size(); ++i, ++c)
            if (*c != name[i]) break;

        // Move to next if it didn't match, move pointer past '=' if it did
        if (i != name.size() || (*c && *c++ != '=')) continue;

        // Read the value backwards
        const std::size_t start = strlen(c);
        for (i = start; i-- > 0;) ip.push(c[i]);

        return MoveAction{};
    }

    ip.reflect();
    return MoveAction{};
}

InstructionAction evar::count(Fungespace &, InstructionPointer &ip) {
    Cell n = 0;
    for (char **current = environ; *current; ++current) n++;
    ip.push(n);
    return MoveAction{};
}

InstructionAction evar::put(Fungespace &, InstructionPointer &ip) {
    auto keyval = ip.pop_0gnirts();
#if defined(MIZU_PLATFORM_WINDOWS)
    if (_putenv(keyval.c_str()) == -1) ip.reflect();
#else
    char *val = &keyval[0];
    while (*val && *val++ != '=') {} // Skip past the key
    if (*val) {
        *(val - 1) = '\0'; // Null terminate the key
        if (setenv(keyval.c_str(), val, 1) == -1) ip.reflect();
    } else {
        ip.reflect();
    }
#endif
    return MoveAction{};
}

InstructionAction evar::get_nth(Fungespace &, InstructionPointer &ip) {
    const auto nth = ip.pop();

    Cell n = 0;
    for (char **current = environ; *current; ++current, ++n) {
        if (n == nth) {
            const char *c = *current;
            while (*c && *c++ != '=') {} // Skip past the key

            // Read the value backwards
            const std::size_t start = strlen(c);
            for (std::size_t i = start; i-- > 0;) ip.push(c[i]);

            return MoveAction{};
        }
    }

    ip.reflect();
    return MoveAction{};
}
