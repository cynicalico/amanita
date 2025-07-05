#include "fingerprints/catseye/toys.hpp"
#include "instruction_pointer.hpp"
#include "mizu/util/rng.hpp"

InstructionAction toys::gable(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.stack.pop();
    const auto v = ip.stack.pop();
    for (std::int64_t i = 0; i < n; ++i)
        ip.stack.push(v);
    return MoveAction{};
}

InstructionAction toys::pair_of_shoes(Fungespace &, InstructionPointer &ip) {
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();
    ip.stack.push(x + y);
    ip.stack.push(x - y);
    return MoveAction{};
}

InstructionAction toys::bracelet(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.stack.pop();
    const auto dst_x_orig = ip.stack.pop();
    const auto h = ip.stack.pop();
    const auto w = ip.stack.pop();
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;

    for (std::int64_t i = 0; i < h; ++i) {
        for (std::int64_t j = 0; j < w; ++j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY)
                fungespace.put(dst_x, dst_y, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::toilet_seat(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(ip.stack.pop() - 1);
    return MoveAction{};
}

InstructionAction toys::pitchfork_head(Fungespace &, InstructionPointer &ip) {
    std::int64_t sum = 0;
    while (ip.stack.size() > 0)
        sum += ip.stack.pop();
    ip.stack.push(sum);
    return MoveAction{};
}

InstructionAction toys::calipers(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;
    const auto j = ip.stack.pop();
    const auto i = ip.stack.pop();

    for (std::int64_t dy = 0; dy < j; ++dy)
        for (std::int64_t dx = 0; dx < i; ++dx)
            fungespace.put(x + dx, y + dy, ip.stack.pop());

    return MoveAction{};
}

InstructionAction toys::counterclockwise(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;
    const auto j = ip.stack.pop();
    const auto i = ip.stack.pop();

    for (std::int64_t dy = j - 1; dy >= 0; --dy)
        for (std::int64_t dx = i - 1; dx >= 0; --dx)
            ip.stack.push(fungespace.get(x + dx, y + dy));

    return MoveAction{};
}

InstructionAction toys::pair_of_stilts(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.stack.pop();
    const auto a = ip.stack.pop();
    if (b > 0)
        ip.stack.push(a << b);
    else if (b < 0)
        ip.stack.push(a >> std::abs(b));
    else
        ip.stack.push(a);
    return MoveAction{};
}

InstructionAction toys::doric_column(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(ip.stack.pop() + 1);
    return MoveAction{};
}

InstructionAction toys::fishhook(Fungespace &fungespace, InstructionPointer &ip) {
    if (const auto trans = ip.stack.pop(); trans < 0) {
        const auto y_start = fungespace.min_coord[1];
        const auto y_end = fungespace.max_coord[1];
        for (std::int64_t y = y_start; y < y_end; ++y) {
            const auto v = fungespace.get(ip.pos.x, y);
            fungespace.put(ip.pos.x, y + trans, v);
        }
    } else if (trans > 0) {
        const auto y_start = fungespace.max_coord[1] - 1;
        const auto y_end = fungespace.min_coord[1];
        for (std::int64_t y = y_start; y >= y_end; --y) {
            const auto v = fungespace.get(ip.pos.x, y);
            fungespace.put(ip.pos.x, y + trans, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::scissors(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.stack.pop();
    const auto dst_x_orig = ip.stack.pop();
    const auto h = ip.stack.pop();
    const auto w = ip.stack.pop();
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;

    for (std::int64_t i = h - 1; i >= 0; i--) {
        for (std::int64_t j = w - 1; j >= 0; --j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY)
                fungespace.put(dst_x, dst_y, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::corner(Fungespace &fungespace, InstructionPointer &ip) {
    ip.save_pos();
    ip.save_delta();

    ip.turn_left();
    ip.step_wrap(fungespace);
    ip.stack.push(fungespace.get(ip.pos.x, ip.pos.y));

    ip.restore_pos();
    ip.restore_delta();

    return MoveAction{};
}

InstructionAction toys::kittycat(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.stack.pop();
    const auto dst_x_orig = ip.stack.pop();
    const auto h = ip.stack.pop();
    const auto w = ip.stack.pop();
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;

    for (std::int64_t i = 0; i < h; ++i) {
        for (std::int64_t j = 0; j < w; ++j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY)
                fungespace.put(dst_x, dst_y, v);
            fungespace.put(src_x, src_y, EMPTY);
        }
    }

    return MoveAction{};
}

InstructionAction toys::lightning_bolt(Fungespace &, InstructionPointer &ip) {
    ip.stack.push(-ip.stack.pop());
    return MoveAction{};
}

InstructionAction toys::boulder(Fungespace &fungespace, InstructionPointer &ip) {
    if (const auto trans = ip.stack.pop(); trans < 0) {
        const auto x_start = fungespace.min_coord[1];
        const auto x_end = fungespace.max_coord[1];
        for (std::int64_t x = x_start; x < x_end; ++x) {
            const auto v = fungespace.get(x, ip.pos.y);
            fungespace.put(x + trans, ip.pos.y, v);
        }
    } else if (trans > 0) {
        const auto x_start = fungespace.max_coord[1];
        const auto x_end = fungespace.min_coord[1];
        for (std::int64_t x = x_start; x >= x_end; --x) {
            const auto v = fungespace.get(x, ip.pos.y);
            fungespace.put(x + trans, ip.pos.y, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::mailbox(Fungespace &, InstructionPointer &ip) {
    std::int64_t prod = 1;
    while (ip.stack.size() > 0)
        prod *= ip.stack.pop();
    ip.stack.push(prod);
    return MoveAction{};
}

InstructionAction toys::necklace(Fungespace &fungespace, InstructionPointer &ip) {
    const auto v = ip.stack.pop();

    ip.save_pos();
    ip.save_delta();

    ip.reflect();
    ip.step_wrap(fungespace);
    fungespace.put(ip.pos.x, ip.pos.y, v);

    ip.restore_pos();
    ip.restore_delta();

    return MoveAction{};
}

InstructionAction toys::can_opener(Fungespace &fungespace, InstructionPointer &ip) {
    ip.save_pos();
    ip.save_delta();

    ip.turn_right();
    ip.step_wrap(fungespace);
    ip.stack.push(fungespace.get(ip.pos.x, ip.pos.y));

    ip.restore_pos();
    ip.restore_delta();

    return MoveAction{};
}

InstructionAction toys::chicane(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;
    const auto h = ip.stack.pop();
    const auto w = ip.stack.pop();
    const auto v = ip.stack.pop();

    for (std::int64_t dst_y = y; dst_y < y + h; ++dst_y)
        for (std::int64_t dst_x = x; dst_x < x + w; ++dst_x)
            fungespace.put(dst_x, dst_y, v);

    return MoveAction{};
}

InstructionAction toys::barstool(Fungespace &fungespace, InstructionPointer &ip) {
    switch (ip.stack.pop()) {
    case 0:
        return ip.instruction_stack.perform(Instruction::EastWestIf, fungespace, ip);
    case 1:
        return ip.instruction_stack.perform(Instruction::NorthSouthIf, fungespace, ip);
    case 2:
        return ip.instruction_stack.perform(Instruction::Compare, fungespace, ip);
    default:
        ip.reflect();
        break;
    }

    return MoveAction{};
}

InstructionAction toys::tumbler(Fungespace &fungespace, InstructionPointer &ip) {
    switch (mizu::rng::get<std::size_t>(3)) {
    case 0:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<std::int64_t>(Instruction::GoSouth));
        ip.instruction_stack.perform(Instruction::GoSouth, fungespace, ip);
        break;
    case 1:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<std::int64_t>(Instruction::GoEast));
        ip.instruction_stack.perform(Instruction::GoEast, fungespace, ip);
        break;
    case 2:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<std::int64_t>(Instruction::GoNorth));
        ip.instruction_stack.perform(Instruction::GoNorth, fungespace, ip);
        break;
    case 3:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<std::int64_t>(Instruction::GoWest));
        ip.instruction_stack.perform(Instruction::GoWest, fungespace, ip);
        break;
    default:
        std::unreachable();
    }
    return MoveAction{};
}

InstructionAction toys::dixiecup(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.stack.pop();
    const auto dst_x_orig = ip.stack.pop();
    const auto h = ip.stack.pop();
    const auto w = ip.stack.pop();
    const auto y = ip.stack.pop() + ip.storage_offset.y;
    const auto x = ip.stack.pop() + ip.storage_offset.x;

    for (std::int64_t i = h - 1; i >= 0; i--) {
        for (std::int64_t j = w - 1; j >= 0; --j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY)
                fungespace.put(dst_x, dst_y, v);
            fungespace.put(src_x, src_y, EMPTY);
        }
    }

    return MoveAction{};
}

InstructionAction toys::television_antenna(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.stack.pop();
    const auto x = ip.stack.pop();
    const auto v = ip.stack.pop();

    if (const auto check = fungespace.get(x + ip.storage_offset.x, y + ip.storage_offset.y); check < v) {
        ip.stack.push(v);
        ip.stack.push(x);
        ip.stack.push(y);
        ip.reflect();
        ip.step_wrap(fungespace);
        ip.reflect();
    } else if (check > v) {
        ip.reflect();
    }

    return MoveAction{};
}

InstructionAction toys::buried_treasure(Fungespace &, InstructionPointer &ip) {
    ip.pos.x += 1;
    return MoveAction{};
}

InstructionAction toys::slingshot(Fungespace &, InstructionPointer &ip) {
    ip.pos.y += 1;
    return MoveAction{};
}

InstructionAction toys::barn_door(Fungespace &, InstructionPointer &ip) {
    ip.reflect();
    return MoveAction{};
}
