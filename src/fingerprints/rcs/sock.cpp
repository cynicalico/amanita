#include "fingerprints/rcs/sock.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"

#if defined(MIZU_PLATFORM_WINDOWS)
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

static std::once_flag initialized_winsock;

bool check_winsock_initialized(State &state) {
    std::call_once(initialized_winsock, [&] {
        const int result = WSAStartup(MAKEWORD(2, 2), &state.sock.wsa_data);
        state.sock.initialized = result == 0;
    });
    return state.sock.initialized;
}
#else
#include <arpa/inet.h>
#include <netdb.h>
#endif

constexpr int BAD_PARAM = std::numeric_limits<int>::max();

int get_funge_ct(std::int64_t ct);
int get_funge_o(std::int64_t o);
int get_funge_pf(std::int64_t pf);
int get_funge_typ(std::int64_t typ);
int get_funge_pro(std::int64_t pro);

InstructionAction fingerprints::sock::accept(State &state, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop();

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end()) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    sockaddr_in service;
    int service_size = sizeof(service);
    const SOCKET accept_socket = ::accept(it->second.h, reinterpret_cast<SOCKADDR *>(&service), &service_size);
    if (accept_socket == INVALID_SOCKET || service.sin_family != AF_INET) {
        ip.reflect();
        return MoveAction{};
    }

    const auto accept_s = static_cast<std::int64_t>(state.sock.sockets.size() + 1);
    state.sock.sockets.emplace(accept_s, State::Socket{.h = accept_socket});
#else
    sockaddr_in service{};
    socklen_t service_size = sizeof(service);
    const int accept_socket = ::accept(it->second, reinterpret_cast<sockaddr *>(&service), &service_size);
    if (accept_socket == -1 || service.sin_family != AF_INET) {
        ip.reflect();
        return MoveAction{};
    }

    const auto accept_s = static_cast<std::int64_t>(state.sock.sockets.size() + 1);
    state.sock.sockets.emplace(accept_s, accept_socket);
#endif
    ip.push(service.sin_port);
    ip.push(service.sin_addr.s_addr);
    ip.push(accept_s);

    return MoveAction{};
}

InstructionAction fingerprints::sock::bind(State &state, Fungespace &, InstructionPointer &ip) {
    const auto addr = ip.pop();
    const auto port = ip.pop();
    const auto ct = get_funge_ct(ip.pop());
    const auto s = ip.pop();

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end() || ct == AF_UNIX || ct == BAD_PARAM) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    sockaddr_in service;
    service.sin_family = ct;
    service.sin_addr.s_addr = static_cast<ULONG>(addr);
    service.sin_port = htons(port);

    if (::bind(it->second.h, reinterpret_cast<SOCKADDR *>(&service), sizeof(service)) == SOCKET_ERROR) ip.reflect();
#else
    sockaddr_in service{};
    service.sin_family = ct;
    service.sin_addr.s_addr = static_cast<uint32_t>(addr);
    service.sin_port = htons(port);

    if (::bind(it->second, reinterpret_cast<sockaddr *>(&service), sizeof(service)) == -1) ip.reflect();
#endif

    return MoveAction{};
}

InstructionAction fingerprints::sock::connect(State &state, Fungespace &, InstructionPointer &ip) {
    const auto addr = ip.pop();
    const auto port = ip.pop();
    const auto ct = get_funge_ct(ip.pop());
    const auto s = ip.pop();

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end() || ct == AF_UNIX || ct == BAD_PARAM) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    sockaddr_in service;
    service.sin_family = ct;
    service.sin_addr.s_addr = static_cast<ULONG>(addr);
    service.sin_port = htons(port);

    if (::connect(it->second.h, reinterpret_cast<SOCKADDR *>(&service), sizeof(service)) == SOCKET_ERROR) ip.reflect();
#else
    sockaddr_in service{};
    service.sin_family = ct;
    service.sin_addr.s_addr = static_cast<std::uint32_t>(addr);
    service.sin_port = htons(port);

    if (::connect(it->second, reinterpret_cast<sockaddr *>(&service), sizeof(service))  == -1) ip.reflect();
#endif
    return MoveAction{};
}

InstructionAction fingerprints::sock::convert_addr(State &state, Fungespace &, InstructionPointer &ip) {
    const auto addr_s = ip.pop_0gnirts();
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }
#endif
    addrinfo *result;
    if (getaddrinfo(addr_s.c_str(), nullptr, nullptr, &result) != 0 || result->ai_family != AF_INET) {
        ip.reflect();
    } else {
        const auto result_ipv4 = reinterpret_cast<struct sockaddr_in *>(result->ai_addr);
        ip.push(result_ipv4->sin_addr.s_addr);
    }
    freeaddrinfo(result);

    return MoveAction{};
}

InstructionAction fingerprints::sock::kill(State &state, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop();

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end()) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    if (closesocket(it->second.h) == SOCKET_ERROR) ip.reflect();
    else state.sock.sockets.erase(it);
#else
    if (close(it->second) == -1) ip.reflect();
    else state.sock.sockets.erase(it);
#endif
    return MoveAction{};
}

InstructionAction fingerprints::sock::listen(State &state, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop();
    const auto n = static_cast<int>(ip.pop());

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end()) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    if (::listen(it->second.h, n) == SOCKET_ERROR) ip.reflect();
#else
    if (::listen(it->second, n) == -1) ip.reflect();
#endif
    return MoveAction{};
}

InstructionAction fingerprints::sock::set_opt(State &state, Fungespace &, InstructionPointer &ip) {
    const auto s = ip.pop();
    const auto o = get_funge_o(ip.pop());
    const auto n = static_cast<int>(ip.pop());

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end() || o == BAD_PARAM) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    BOOL opt_val = n == 0 ? FALSE : TRUE;
    constexpr int opt_len = sizeof(BOOL);
    if (setsockopt(it->second.h, SOL_SOCKET, o, reinterpret_cast<char *>(&opt_val), opt_len) == SOCKET_ERROR)
        ip.reflect();
#else
    int opt_val = n == 0 ? 0 : 1;
    constexpr int opt_len = sizeof(int);
    if (setsockopt(it->second, SOL_SOCKET, o, &opt_val, opt_len) == -1) ip.reflect();
#endif
    return MoveAction{};
}

InstructionAction fingerprints::sock::recv(State &state, Fungespace &fungespace, InstructionPointer &ip) {
    const auto s = ip.pop();
    const auto l = static_cast<int>(ip.pop());
    auto v = ip.pop_offset_vec();

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end() || l > 8192) {
        ip.reflect();
        return MoveAction{};
    }

    static char buf[8192];
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    const auto bytes_read = ::recv(it->second.h, buf, l, 0);
    if (bytes_read == SOCKET_ERROR) {
        ip.reflect();
    } else {
        for (int i = 0; i < bytes_read; ++i) {
            fungespace.put(v.x, v.y, buf[i]);
            v += EAST;
        }
    }
    ip.push(bytes_read);
#else
    const auto bytes_read = ::recv(it->second, buf, l, 0);
    if (bytes_read == -1) {
        ip.reflect();
    } else {
        for (int i = 0; i < bytes_read; ++i) {
            fungespace.put(v.x, v.y, buf[i]);
            v += EAST;
        }
    }
    ip.push(bytes_read);
#endif
    return MoveAction{};
}

InstructionAction fingerprints::sock::create(State &state, Fungespace &, InstructionPointer &ip) {
    const auto pro = get_funge_pro(ip.pop());
    const auto typ = get_funge_typ(ip.pop());
    const auto pf = get_funge_pf(ip.pop());

    if (pf == PF_UNIX || pro == BAD_PARAM || typ == BAD_PARAM || pf == BAD_PARAM) {
        ip.reflect();
        return MoveAction{};
    }

#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = pf;
    hints.ai_socktype = typ;
    hints.ai_protocol = pro;

    SOCKET h = INVALID_SOCKET;
    h = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
    if (h == INVALID_SOCKET) {
        ip.reflect();
        return MoveAction{};
    }

    const auto s = static_cast<std::int64_t>(state.sock.sockets.size() + 1);
    state.sock.sockets.emplace(s, State::Socket{hints, h});

    ip.push(s);
#else
    int h = socket(pf, typ, pro);
    if (h == -1) {
        ip.reflect();
        return MoveAction{};
    }

    const auto s = static_cast<std::int64_t>(state.sock.sockets.size() + 1);
    state.sock.sockets.emplace(s, h);

    ip.push(s);
#endif
    return MoveAction{};
}

InstructionAction fingerprints::sock::send(State &state, Fungespace &fungespace, InstructionPointer &ip) {
    const auto s = ip.pop();
    const auto l = static_cast<int>(ip.pop());
    auto v = ip.pop_offset_vec();

    const auto it = state.sock.sockets.find(s);
    if (it == state.sock.sockets.end()) {
        ip.reflect();
        return MoveAction{};
    }
#if defined(MIZU_PLATFORM_WINDOWS)
    if (!check_winsock_initialized(state)) {
        ip.reflect();
        return MoveAction{};
    }

    std::string buf;
    for (int i = 0; i < l; ++i) {
        buf += static_cast<char>(fungespace.get(v.x, v.y));
        v += EAST;
    }

    const auto bytes_sent = ::send(it->second.h, buf.c_str(), l, 0);
    if (bytes_sent == SOCKET_ERROR) ip.reflect();
    ip.push(bytes_sent);
#else
    std::string buf;
    for (int i = 0; i < l; ++i) {
        buf += static_cast<char>(fungespace.get(v.x, v.y));
        v += EAST;
    }

    const auto bytes_sent = ::send(it->second, buf.c_str(), l, 0);
    if (bytes_sent == -1) ip.reflect();
    ip.push(bytes_sent);
#endif
    return MoveAction{};
}

int get_funge_ct(std::int64_t ct) {
    switch (ct) {
    case 1: return AF_UNIX;
    case 2: return AF_INET;
    default: return BAD_PARAM;
    }
}

int get_funge_o(std::int64_t o) {
    switch (o) {
    case 1: return SO_DEBUG;
    case 2: return SO_REUSEADDR;
    case 3: return SO_KEEPALIVE;
    case 4: return SO_DONTROUTE;
    case 5: return SO_BROADCAST;
    case 6: return SO_OOBINLINE;
    default: return BAD_PARAM;
    }
}

int get_funge_pf(std::int64_t pf) {
    switch (pf) {
    case 1: return PF_UNIX;
    case 2: return PF_INET;
    default: return BAD_PARAM;
    }
}

int get_funge_typ(std::int64_t typ) {
    switch (typ) {
    case 1: return SOCK_DGRAM;
    case 2: return SOCK_STREAM;
    default: return BAD_PARAM;
    }
}

int get_funge_pro(std::int64_t pro) {
    switch (pro) {
    case 1: return IPPROTO_TCP;
    case 2: return IPPROTO_UDP;
    default: return BAD_PARAM;
    }
}
