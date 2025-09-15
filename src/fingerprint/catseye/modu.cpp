#include "fingerprint/catseye/modu.hpp"

#include "instruction_pointer.hpp"

void amanita::modu::semantic_signed_result_modulo(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    if (b == 0) {
        ip->stack_push(0);
    } else {
        auto c = a / b;
        if (c < 0)
            c -= 1;
        const auto v = a - c * b;
        ip->stack_push(v);
    }
}

void amanita::modu::semantic_sam_holden_unsigned_result_modulo(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = std::abs(ip->stack_pop());
    const auto a = std::abs(ip->stack_pop());
    ip->stack_push(b == 0 ? 0 : a % b);
}

void amanita::modu::semantic_c_language_integer_remainder(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto b = ip->stack_pop();
    const auto a = ip->stack_pop();
    ip->stack_push(b == 0 ? 0 : a % b);
}
