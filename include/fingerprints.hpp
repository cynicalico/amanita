#ifndef AMANITA_FINGERPRINT_HPP
#define AMANITA_FINGERPRINT_HPP

#include "common.hpp"

class InstructionStack;

bool load_fingerprint(InstructionStack &instruction_stack, std::int64_t fingerprint);

bool unload_fingerprint(InstructionStack &instruction_stack, std::int64_t fingerprint);

#endif // AMANITA_FINGERPRINT_HPP
