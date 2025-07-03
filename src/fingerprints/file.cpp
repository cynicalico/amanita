#include "fingerprints/file.hpp"
#include <fmt/format.h>
#include <fstream>
#include "instruction_pointer.hpp"

#define MAX_STRING_READ 1024

struct File {
    std::int64_t io_buffer_pos[2];
    FILE *f;
};

std::unordered_map<std::int64_t, File> &open_files() {
    static std::unordered_map<std::int64_t, File> open_files{};
    return open_files;
}

const char *get_funge_file_mode(const std::int64_t m) {
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

int get_funge_seek_origin(const std::int64_t m) {
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

InstructionAction file_close(Fungespace &, InstructionPointer &ip) {
    const auto h = ip.stack.pop();

    auto &of = open_files();
    if (const auto it = of.find(h); it != of.end())
        if (const auto err = fclose(it->second.f); err == EOF)
            ip.reflect();
        else
            of.erase(it);
    else
        ip.reflect();

    return MoveAction{};
}

InstructionAction file_delete(Fungespace &, InstructionPointer &ip) {
    const auto filepath = ip.stack.pop_0gnirts();

    if (remove(filepath.c_str()) != 0)
        ip.reflect();

    return MoveAction{};
}

InstructionAction file_read_string(Fungespace &, InstructionPointer &ip) {
    const auto h = ip.stack.pop();

    auto &of = open_files();
    if (const auto it = of.find(h); it != of.end()) {
        char buf[MAX_STRING_READ];
        const auto s = fgets(buf, sizeof(buf), it->second.f);

        if (ferror(it->second.f) != 0) {
            ip.reflect();
            ip.stack.push('\0');
            ip.stack.push(0);
        } else {
            ip.stack.push(h);
            if (s) {
                const auto len = strlen(s);
                ip.stack.push('\0');
                for (std::size_t i = len; i-- > 0;)
                    ip.stack.push(s[i]);
                ip.stack.push(len);
            } else {
                ip.stack.push('\0');
                ip.stack.push(0);
            }
        }
    } else {
        ip.reflect();
        ip.stack.push('\0');
        ip.stack.push(0);
    }

    return MoveAction{};
}

InstructionAction file_location(Fungespace &, InstructionPointer &ip) {
    const auto h = ip.stack.pop();

    auto &of = open_files();
    if (const auto it = of.find(h); it != of.end()) {
        if (const auto l = ftell(it->second.f); l != -1) {
            ip.stack.push(h);
            ip.stack.push(l);
        } else {
            ip.reflect();
            ip.stack.push(h);
            ip.stack.push(0);
        }
    } else {
        ip.reflect();
        ip.stack.push(h);
        ip.stack.push(0);
    }

    return MoveAction{};
}

InstructionAction file_open(Fungespace &, InstructionPointer &ip) {
    const auto filepath = ip.stack.pop_0gnirts();
    const auto m = ip.stack.pop();
    const auto io_buffer_y = ip.stack.pop();
    const auto io_buffer_x = ip.stack.pop();

    if (const auto *mode = get_funge_file_mode(m); mode) {
        FILE *file;
        if (const auto err = fopen_s(&file, filepath.c_str(), mode); err != 0) {
            ip.reflect();
            ip.stack.push(0);
        } else {
            auto &of = open_files();
            const auto h = of.size() + 1;
            of.emplace(h, File{{io_buffer_x, io_buffer_y}, file});
            ip.stack.push(h);
        }
    } else {
        ip.reflect();
        ip.stack.push(0);
    }

    return MoveAction{};
}

InstructionAction file_write_string(Fungespace &, InstructionPointer &ip) {
    const auto s = ip.stack.pop_0gnirts();
    const auto h = ip.stack.pop();

    auto &of = open_files();
    if (const auto it = of.find(h); it != of.end()) {
        if (const auto err = fputs(s.c_str(), it->second.f); err == EOF)
            ip.reflect();
    } else {
        ip.reflect();
    }

    ip.stack.push(h);

    return MoveAction{};
}

InstructionAction file_read_bytes(Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.stack.pop();
    const auto h = ip.stack.pop();

    if (n < 0) {
        ip.reflect();
        return MoveAction{};
    }

    auto &of = open_files();
    if (const auto it = of.find(h); it != of.end()) {
        std::vector<unsigned char> buf(n);
        if (const auto bytes_read = fread(&buf[0], sizeof(unsigned char), n, it->second.f);
            bytes_read != n || ferror(it->second.f) != 0) {
            ip.reflect();
        } else {
            for (std::int64_t i = 0; i < n; ++i)
                fungespace.put(it->second.io_buffer_pos[0] + i, it->second.io_buffer_pos[1], buf[i]);
        }
    } else {
        ip.reflect();
    }

    ip.stack.push(h);

    return MoveAction{};
}

InstructionAction file_seek(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.stack.pop();
    const auto m = ip.stack.pop();
    const auto h = ip.stack.pop();

    if (const auto origin = get_funge_seek_origin(m); origin != std::numeric_limits<int>::max()) {
        auto &of = open_files();
        if (const auto it = of.find(h); it != of.end()) {
            if (fseek(it->second.f, static_cast<long>(n), origin) != 0)
                ip.reflect();
        } else {
            ip.reflect();
        }
    } else {
        ip.reflect();
    }

    ip.stack.push(h);

    return MoveAction{};
}

InstructionAction file_write_bytes(Fungespace &fungespace, InstructionPointer &ip) {
    const auto n = ip.stack.pop();
    const auto h = ip.stack.pop();

    if (n < 0) {
        ip.reflect();
        return MoveAction{};
    }

    auto &of = open_files();
    if (const auto it = of.find(h); it != of.end()) {
        std::vector<unsigned char> buf(n);
        for (std::int64_t i = 0; i < n; ++i)
            buf[i] = fungespace.get(it->second.io_buffer_pos[0] + i, it->second.io_buffer_pos[1]) & 0xff;
        if (const auto bytes_written = fwrite(&buf[0], sizeof(unsigned char), n, it->second.f);
            bytes_written != n || ferror(it->second.f) != 0) {
            ip.reflect();
        }
    } else {
        ip.reflect();
    }

    ip.stack.push(h);

    return MoveAction{};
}
