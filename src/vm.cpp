#include "vm.hpp"

#include "action.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

amanita::VM::VM()
    : src_path(""),
      state(new State{
              Status::Running, 0, std::vector<std::string>(), new Fungespace(), std::vector<InstructionPointer *>()}) {
    reset();
}

amanita::VM::VM(std::filesystem::path src_path, std::vector<std::string> args)
    : src_path(std::move(src_path)),
      state(new State{
              Status::Running,
              0,
              std::move(args),
              new Fungespace(this->src_path),
              std::vector<InstructionPointer *>()}) {
    reset();
}

void amanita::VM::reset() {
    state->status = Status::Running;

    state->ips.clear();
    state->ips.push_back(new InstructionPointer());
    state->ips.back()->curr_ins = state->fungespace->get_ins(state->ips.back()->pos);
}

void amanita::VM::step() {
    next_ips_buf_.clear();

    for (const auto ip: state->ips) {
        ip->check_step_to_next_instruction(state);

        actions_buf_.clear();
        ip->perform(state, actions_buf_);

        if (state->status == Status::Stopped)
            return;

        if (!ip->alive)
            continue;

        for (const auto &action: actions_buf_) {
            switch (action.type) {
            case ActionType::Split: /* TODO */ break;
            }
        }

        next_ips_buf_.push_back(ip);
    }

    if (next_ips_buf_.empty()) {
        state->status = Status::Stopped;
        return;
    }

    std::swap(state->ips, next_ips_buf_);
    for (const auto ip: state->ips) {
        ip->prev_ins = ip->curr_ins;
        ip->step_to_next_instruction(state);
    }
}

void amanita::VM::run() {
    while (state->status == Status::Running)
        step();
}
