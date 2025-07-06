#include "fingerprints/rcs/fing.hpp"
#include <fmt/format.h>
#include <utility>
#include "instruction_pointer.hpp"

#define INVALID_SEM(sem) (!(sem >= 'A' && sem <= 'Z'))

InstructionAction fing::swap(Fungespace &, InstructionPointer &ip) {
    auto sem_a = ip.pop();
    sem_a = sem_a <= 25 ? sem_a + 'A' : sem_a;

    auto sem_b = ip.pop();
    sem_b = sem_b <= 25 ? sem_b + 'A' : sem_b;

    if (INVALID_SEM(sem_a) || INVALID_SEM(sem_b)) {
        ip.reflect();
    } else {
        InstructionFunc tmp_a = ip.instruction_stack.pop(static_cast<Instruction>(sem_a));
        InstructionFunc tmp_b = ip.instruction_stack.pop(static_cast<Instruction>(sem_b));
        ip.instruction_stack.push(static_cast<Instruction>(sem_a), std::move(tmp_b));
        ip.instruction_stack.push(static_cast<Instruction>(sem_b), std::move(tmp_a));
    }

    return MoveAction{};
}

InstructionAction fing::pop(Fungespace &, InstructionPointer &ip) {
    auto sem = ip.pop();
    sem = sem <= 25 ? sem + 'A' : sem;

    if (INVALID_SEM(sem)) ip.reflect();
    else ip.instruction_stack.pop(static_cast<Instruction>(sem));

    return MoveAction{};
}

InstructionAction fing::push(Fungespace &, InstructionPointer &ip) {
    auto sem_dst = ip.pop();
    sem_dst = sem_dst <= 25 ? sem_dst + 'A' : sem_dst;

    auto sem_src = ip.pop();
    sem_src = sem_src <= 25 ? sem_src + 'A' : sem_src;

    if (INVALID_SEM(sem_dst) || INVALID_SEM(sem_src)) {
        ip.reflect();
    } else {
        InstructionFunc tmp = ip.instruction_stack.peek(static_cast<Instruction>(sem_src));
        ip.instruction_stack.push(static_cast<Instruction>(sem_dst), std::move(tmp));
    }

    return MoveAction{};
}
