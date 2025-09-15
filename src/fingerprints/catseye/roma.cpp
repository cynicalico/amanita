#include "fingerprints/catseye/roma.hpp"

#include "instruction_pointer.hpp"

void amanita::roma::semantic_c(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(100);
}

void amanita::roma::semantic_d(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(500);
}

void amanita::roma::semantic_i(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(1);
}

void amanita::roma::semantic_l(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(50);
}

void amanita::roma::semantic_m(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(1000);
}

void amanita::roma::semantic_v(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(5);
}

void amanita::roma::semantic_x(State *, InstructionPointer *ip, std::vector<Action> &) {
    ip->stack_push(10);
}
