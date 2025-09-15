#include "fingerprint/rcs/file.hpp"

#include "fungespace.hpp"
#include "instruction_pointer.hpp"
#include "state.hpp"

#include <cstdio>
#include <cstring>

#define MAX_READ_SIZE 4096

const char *get_funge_file_mode(std::int64_t m);
int get_funge_seek_origin(std::int64_t m);

void amanita::file::semantic_close(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto h = ip->stack_pop();

    if (const auto it = state->open_files.find(h); it != state->open_files.end())
        if (const auto err = fclose(it->second.f); err == EOF)
            ip->reflect();
        else
            state->open_files.erase(it);
    else
        ip->reflect();
}

void amanita::file::semantic_delete(State *, InstructionPointer *ip, std::vector<Action> &) {
    const auto filepath = ip->stack_pop_0gnirts();

    if (remove(filepath.c_str()) != 0)
        ip->reflect();
}

void amanita::file::semantic_read_string(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto h = ip->stack_pop();

    if (const auto it = state->open_files.find(h); it != state->open_files.end()) {
        char buf[MAX_READ_SIZE];
        const auto s = fgets(buf, sizeof(buf), it->second.f);

        if (ferror(it->second.f) != 0) {
            ip->stack_push('\0');
            ip->stack_push(0);
            ip->reflect();
        } else {
            ip->stack_push(h);
            if (s) {
                const auto len = strlen(s);
                ip->stack_push('\0');
                for (std::size_t i = len; i-- > 0;)
                    ip->stack_push(s[i]);
                ip->stack_push(static_cast<std::int64_t>(len));
            } else {
                ip->stack_push('\0');
                ip->stack_push(0);
            }
        }
    } else {
        ip->stack_push('\0');
        ip->stack_push(0);
        ip->reflect();
    }
}

void amanita::file::semantic_location(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto h = ip->stack_peek();

    if (const auto it = state->open_files.find(h); it != state->open_files.end()) {
        if (const auto l = ftell(it->second.f); l != -1) {
            ip->stack_push(l);
        } else {
            ip->stack_push(0);
            ip->reflect();
        }
    } else {
        ip->stack_push(0);
        ip->reflect();
    }
}

void amanita::file::semantic_open(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto filepath = ip->stack_pop_0gnirts();
    const auto m = ip->stack_pop();
    const auto io_buffer_pos = ip->stack_pop_vec();

    if (const auto *mode = get_funge_file_mode(m); mode) {
        FILE *file = fopen(filepath.c_str(), mode);
        if (!file) {
            ip->stack_push(0);
            ip->reflect();
        } else {
            const auto h = state->open_files.size() + 1;
            state->open_files.emplace(h, State::File(io_buffer_pos, file));
            ip->stack_push(static_cast<std::int64_t>(h));
        }
    } else {
        ip->stack_push(0);
        ip->reflect();
    }
}

void amanita::file::semantic_write_string(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto s = ip->stack_pop_0gnirts();
    const auto h = ip->stack_peek();

    if (const auto it = state->open_files.find(h); it != state->open_files.end()) {
        if (const auto err = fputs(s.c_str(), it->second.f); err == EOF)
            ip->reflect();
    } else {
        ip->reflect();
    }
}

void amanita::file::semantic_read_bytes(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto n = ip->stack_pop();
    const auto h = ip->stack_peek();

    if (n < 0) {
        ip->reflect();
        return;
    }

    if (const auto it = state->open_files.find(h); it != state->open_files.end()) {
        std::vector<unsigned char> buf(n);
        if (const auto bytes_read = fread(&buf[0], sizeof(unsigned char), n, it->second.f);
            bytes_read != n || ferror(it->second.f) != 0) {
            ip->reflect();
        } else {
            for (std::int64_t i = 0; i < n; ++i)
                state->fungespace->put({it->second.io_buffer_pos.x + i, it->second.io_buffer_pos.y}, buf[i]);
        }
    } else {
        ip->reflect();
    }
}

void amanita::file::semantic_seek(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto n = ip->stack_pop();
    const auto m = ip->stack_pop();
    const auto h = ip->stack_peek();

    if (const auto origin = get_funge_seek_origin(m); origin != -1) {
        if (const auto it = state->open_files.find(h); it != state->open_files.end()) {
            if (fseek(it->second.f, n, origin) != 0)
                ip->reflect();
        } else {
            ip->reflect();
        }
    } else {
        ip->reflect();
    }
}

void amanita::file::semantic_write_bytes(State *state, InstructionPointer *ip, std::vector<Action> &) {
    const auto n = ip->stack_pop();
    const auto h = ip->stack_peek();

    if (n < 0) {
        ip->reflect();
        return;
    }

    if (const auto it = state->open_files.find(h); it != state->open_files.end()) {
        std::vector<unsigned char> buf(n);
        for (std::int64_t i = 0; i < n; ++i)
            buf[i] = state->fungespace->get({it->second.io_buffer_pos.x + i, it->second.io_buffer_pos.y}) & 0xff;
        if (const auto bytes_written = fwrite(&buf[0], sizeof(unsigned char), n, it->second.f);
            bytes_written != n || ferror(it->second.f) != 0) {
            ip->reflect();
        }
    } else {
        ip->reflect();
    }
}

const char *get_funge_file_mode(std::int64_t m) {
    switch (m) {
    case 0: return "rb";
    case 1: return "wb";
    case 2: return "ab";
    case 3: return "rb+";
    case 4: return "wb+";
    case 5: return "ab+";
    default: return nullptr;
    }
}

int get_funge_seek_origin(std::int64_t m) {
    switch (m) {
    case 0: return SEEK_SET;
    case 1: return SEEK_CUR;
    case 2: return SEEK_END;
    default: return -1;
    }
}
