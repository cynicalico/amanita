#include "vm.hpp"

#include "action.hpp"

amanita::VM::VM()
    : src_path(""),
      state(std::make_unique<State>(
              Status::Running,
              0,
              std::vector<std::string>(),
              std::make_unique<Fungespace>(),
              std::vector<std::unique_ptr<InstructionPointer>>())) {
    state->ips.push_back(std::make_unique<InstructionPointer>());
}

amanita::VM::VM(std::filesystem::path src_path, std::vector<std::string> args)
    : src_path(std::move(src_path)),
      state(std::make_unique<State>(
              Status::Running,
              0,
              std::move(args),
              std::make_unique<Fungespace>(this->src_path),
              std::vector<std::unique_ptr<InstructionPointer>>())) {
    state->ips.push_back(std::make_unique<InstructionPointer>());
}

void amanita::VM::step() {
    next_ips_buf_.clear();

    for (auto &ip: state->ips) {
        ip->check_step_to_next_instruction(state.get());

        actions_buf_.clear();
        ip->perform(state.get(), actions_buf_);

        if (state->status == Status::Stopped)
            return;

        if (!ip->alive)
            continue;

        for (const auto &action: actions_buf_) {
            switch (action.type) {
            case ActionType::Split: next_ips_buf_.emplace_back(std::make_unique<InstructionPointer>(*action.ip)); break;
            }
        }

        next_ips_buf_.emplace_back(std::move(ip));
    }

    if (next_ips_buf_.empty()) {
        state->status = Status::Stopped;
        return;
    }

    std::swap(state->ips, next_ips_buf_);
    for (const auto &ip: state->ips) {
        ip->prev_ins = ip->curr_ins;
        ip->step_to_next_instruction(state.get());
    }
}

void amanita::VM::run() {
    while (state->status == Status::Running)
        step();
}
