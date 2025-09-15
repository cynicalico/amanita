#pragma once

#include "fingerprint.hpp"

namespace amanita::file {
void semantic_close(State *, InstructionPointer *, std::vector<Action> &);
void semantic_delete(State *, InstructionPointer *, std::vector<Action> &);
void semantic_read_string(State *, InstructionPointer *, std::vector<Action> &);
void semantic_location(State *, InstructionPointer *, std::vector<Action> &);
void semantic_open(State *, InstructionPointer *, std::vector<Action> &);
void semantic_write_string(State *, InstructionPointer *, std::vector<Action> &);
void semantic_read_bytes(State *, InstructionPointer *, std::vector<Action> &);
void semantic_seek(State *, InstructionPointer *, std::vector<Action> &);
void semantic_write_bytes(State *, InstructionPointer *, std::vector<Action> &);

const Fingerprint FINGERPRINT(
        "FILE",
        {
                {Instruction::C, semantic_close},
                {Instruction::D, semantic_delete},
                {Instruction::G, semantic_read_string},
                {Instruction::L, semantic_location},
                {Instruction::O, semantic_open},
                {Instruction::P, semantic_write_string},
                {Instruction::R, semantic_read_bytes},
                {Instruction::S, semantic_seek},
                {Instruction::W, semantic_write_bytes},
        });
} // namespace amanita::file
