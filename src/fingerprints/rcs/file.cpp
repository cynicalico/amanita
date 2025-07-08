#include "fingerprints/rcs/file.hpp"
#include <cstdio>
#include <cstring>
#include "fungespace.hpp"
#include "instruction_pointer.hpp"
#include "mizu/util/platform.hpp"

#define MAX_STRING_READ 1024

const char *get_funge_file_mode(Cell m);
int get_funge_seek_origin(Cell m);

InstructionAction fingerprints::file::close(State &state, Fungespace &, InstructionPointer &ip) {
    const auto h = ip.pop();

    if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end())
        if (const auto err = fclose(it->second.f); err == EOF) ip.reflect();
        else state.file.open_files.erase(it);
    else ip.reflect();

    return MoveAction{};
}

InstructionAction fingerprints::file::delete_(State &, Fungespace &, InstructionPointer &ip) {
    const auto filepath = ip.pop_0gnirts();

    if (remove(filepath.c_str()) != 0) ip.reflect();

    return MoveAction{};
}

InstructionAction fingerprints::file::read_string(State &state, Fungespace &, InstructionPointer &ip) {
    const auto h = ip.pop();

    if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end()) {
        char buf[MAX_STRING_READ];
        const auto s = fgets(buf, sizeof(buf), it->second.f);

        if (ferror(it->second.f) != 0) {
            ip.reflect();
            ip.push('\0');
            ip.push(0);
        } else {
            ip.push(h);
            if (s) {
                const auto len = strlen(s);
                ip.push('\0');
                for (std::size_t i = len; i-- > 0;) ip.push(s[i]);
                ip.push(len);
            } else {
                ip.push('\0');
                ip.push(0);
            }
        }
    } else {
        ip.reflect();
        ip.push('\0');
        ip.push(0);
    }

    return MoveAction{};
}

InstructionAction fingerprints::file::location(State &state, Fungespace &, InstructionPointer &ip) {
    const auto h = ip.pop();

    if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end()) {
        if (const auto l = ftell(it->second.f); l != -1) {
            ip.push(h);
            ip.push(l);
        } else {
            ip.reflect();
            ip.push(h);
            ip.push(0);
        }
    } else {
        ip.reflect();
        ip.push(h);
        ip.push(0);
    }

    return MoveAction{};
}

InstructionAction fingerprints::file::open(State &state, Fungespace &, InstructionPointer &ip) {
    const auto filepath = ip.pop_0gnirts();
    const auto m = ip.pop();
    const auto io_buffer_y = ip.pop();
    const auto io_buffer_x = ip.pop();

    if (const auto *mode = get_funge_file_mode(m); mode) {
        FILE *file;
#if defined(MIZU_PLATFORM_WINDOWS)
        if (const auto err = fopen_s(&file, filepath.c_str(), mode); err != 0) {
#else
        file = fopen(filepath.c_str(), mode);
        if (!file) {
#endif
            ip.reflect();
            ip.push(0);
        } else {
            const auto h = state.file.open_files.size() + 1;
            state.file.open_files.emplace(h, State::File{{io_buffer_x, io_buffer_y}, file});
            ip.push(h);
        }
    } else {
        ip.reflect();
        ip.push(0);
    }

    return MoveAction{};
}

InstructionAction fingerprints::file::write_string(State &state, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop_0gnirts();
    const auto h = ip.pop();

    if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end()) {
        if (const auto err = fputs(s.c_str(), it->second.f); err == EOF) ip.reflect();
    } else {
        ip.reflect();
    }

    ip.push(h);

    return MoveAction{};
}

InstructionAction fingerprints::file::read_bytes(State &state, Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto h = ip.pop();

    if (n < 0) {
        ip.reflect();
        return MoveAction{};
    }

    if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end()) {
        std::vector<unsigned char> buf(n);
        if (const auto bytes_read = fread(&buf[0], sizeof(unsigned char), n, it->second.f);
            bytes_read != n || ferror(it->second.f) != 0) {
            ip.reflect();
        } else {
            for (Index i = 0; i < n; ++i)
                fungespace.put(it->second.io_buffer_pos.x + i, it->second.io_buffer_pos.y, buf[i]);
        }
    } else {
        ip.reflect();
    }

    ip.push(h);

    return MoveAction{};
}

InstructionAction fingerprints::file::seek(State &state, Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto m = ip.pop();
    const auto h = ip.pop();

    if (const auto origin = get_funge_seek_origin(m); origin != std::numeric_limits<int>::max()) {
        if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end()) {
            if (fseek(it->second.f, static_cast<long>(n), origin) != 0) ip.reflect();
        } else {
            ip.reflect();
        }
    } else {
        ip.reflect();
    }

    ip.push(h);

    return MoveAction{};
}

InstructionAction fingerprints::file::write_bytes(State &state, Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto h = ip.pop();

    if (n < 0) {
        ip.reflect();
        return MoveAction{};
    }

    if (const auto it = state.file.open_files.find(h); it != state.file.open_files.end()) {
        std::vector<unsigned char> buf(n);
        for (Index i = 0; i < n; ++i)
            buf[i] = fungespace.get(it->second.io_buffer_pos.x + i, it->second.io_buffer_pos.y) & 0xff;
        if (const auto bytes_written = fwrite(&buf[0], sizeof(unsigned char), n, it->second.f);
            bytes_written != n || ferror(it->second.f) != 0) {
            ip.reflect();
        }
    } else {
        ip.reflect();
    }

    ip.push(h);

    return MoveAction{};
}

const char *get_funge_file_mode(const Cell m) {
    switch (m) {
    case 0:
        return "rb";
    case 1:
        return "wb";
    case 2:
        return "ab";
    case 3:
        return "rb+";
    case 4:
        return "wb+";
    case 5:
        return "ab+";
    default:
        return nullptr;
    }
}

int get_funge_seek_origin(const Cell m) {
    switch (m) {
    case 0:
        return SEEK_SET;
    case 1:
        return SEEK_CUR;
    case 2:
        return SEEK_END;
    default:
        return std::numeric_limits<int>::max();
    }
}
