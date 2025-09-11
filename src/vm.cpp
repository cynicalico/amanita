#include "vm.hpp"

#include "action.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

amanita::VM::VM()
    : src_path(""),
      state(new State{
              Status::Running, std::vector<std::string>(), new Fungespace(), std::vector<InstructionPointer *>()}) {
    reset();
}

amanita::VM::VM(std::filesystem::path src_path, std::vector<std::string> args)
    : src_path(std::move(src_path)),
      state(new State{
              Status::Running, std::move(args), new Fungespace(this->src_path), std::vector<InstructionPointer *>()}) {
    reset();
}

void amanita::VM::reset() {
    state->status = Status::Running;

    state->ips.clear();
    state->ips.push_back(new InstructionPointer());
    state->ips.back()->curr_ins = state->fungespace->get_ins(state->ips.back()->pos);
}

void amanita::VM::step() {
    std::vector<Action> actions{};
    for (const auto ip: state->ips) {
        ip->check_step_to_next_instruction(state);
        ip->perform(state, actions);
    }
    state->ips.clear();

    for (const auto &action: actions) {
        std::visit(
                overloaded{
                        [&](const ActionIter &a) {
                            bool bail = false;
                            for (const auto &iter_action: a.actions) {
                                // TODO
                            }
                        },
                        [&](const ActionKill &a) {
                            delete a.ip;
                        },
                        [&](const ActionMove &a) {
                            state->ips.push_back(a.ip);
                        },
                        [&](const ActionSplit &) {},
                        [&](const ActionQuit &a) {
                            exit_code = a.exit_code;
                            state->status = Status::Stopped;
                        }},
                action);

        if (state->status == Status::Stopped)
            return;
    }

    if (state->ips.empty()) {
        state->status = Status::Stopped;
        return;
    }

    for (auto ip: state->ips) {
        ip->prev_ins = ip->curr_ins;
        ip->step_to_next_instruction(state);
    }
}

void amanita::VM::run() {
    while (state->status == Status::Running)
        step();
}
