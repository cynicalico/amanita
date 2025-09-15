#include "fingerprint.hpp"

#include <cstring>

amanita::Fingerprint::Fingerprint(
        const char *name, const std::initializer_list<std::pair<Instruction, Semantic>> semantics)
    : name(name),
      id(0),
      semantics(semantics) {
    const auto len = strlen(name);
    for (std::size_t i = 0; i < len; i++)
        id = id * 256 + name[i];
}
