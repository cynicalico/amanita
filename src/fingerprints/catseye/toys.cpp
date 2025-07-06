#include "fingerprints/catseye/toys.hpp"
#include "fungespace.hpp"
#include "instruction_pointer.hpp"
#include "mizu/util/rng.hpp"

// TODO: Refactor to use ip.pop_vec/ip.pop_offset_vec

InstructionAction toys::gable(Fungespace &, InstructionPointer &ip) {
    const auto n = ip.pop();
    const auto v = ip.pop();
    for (Index i = 0; i < n; ++i) ip.push(v);
    return MoveAction{};
}

InstructionAction toys::pair_of_shoes(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    ip.push(a + b);
    ip.push(a - b);
    return MoveAction{};
}

InstructionAction toys::bracelet(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.pop();
    const auto dst_x_orig = ip.pop();
    const auto h = ip.pop();
    const auto w = ip.pop();
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;

    for (Index i = 0; i < h; ++i) {
        for (Index j = 0; j < w; ++j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY) fungespace.put(dst_x, dst_y, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::toilet_seat(Fungespace &, InstructionPointer &ip) {
    ip.push(ip.pop() - 1);
    return MoveAction{};
}

InstructionAction toys::pitchfork_head(Fungespace &, InstructionPointer &ip) {
    Cell sum = 0;
    while (ip.stack.size() > 0) sum += ip.pop();
    ip.push(sum);
    return MoveAction{};
}

InstructionAction toys::calipers(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;
    const auto j = ip.pop();
    const auto i = ip.pop();

    for (Index dy = 0; dy < j; ++dy)
        for (Index dx = 0; dx < i; ++dx) fungespace.put(x + dx, y + dy, ip.pop());

    return MoveAction{};
}

InstructionAction toys::counterclockwise(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;
    const auto j = ip.pop();
    const auto i = ip.pop();

    for (Index dy = j - 1; dy >= 0; --dy)
        for (Index dx = i - 1; dx >= 0; --dx) ip.push(fungespace.get(x + dx, y + dy));

    return MoveAction{};
}

InstructionAction toys::pair_of_stilts(Fungespace &, InstructionPointer &ip) {
    const auto b = ip.pop();
    const auto a = ip.pop();
    if (b > 0) ip.push(a << b);
    else if (b < 0) ip.push(a >> std::abs(b));
    else ip.push(a);
    return MoveAction{};
}

InstructionAction toys::doric_column(Fungespace &, InstructionPointer &ip) {
    ip.push(ip.pop() + 1);
    return MoveAction{};
}

InstructionAction toys::fishhook(Fungespace &fungespace, InstructionPointer &ip) {
    if (const auto trans = ip.pop(); trans < 0) {
        const auto y_start = fungespace.min_coord.y;
        const auto y_end = fungespace.max_coord.y;
        for (Index y = y_start; y < y_end; ++y) {
            const auto v = fungespace.get(ip.pos.x, y);
            fungespace.put(ip.pos.x, y + trans, v);
        }
    } else if (trans > 0) {
        const auto y_start = fungespace.max_coord.y - 1;
        const auto y_end = fungespace.min_coord.y;
        for (Index y = y_start; y >= y_end; --y) {
            const auto v = fungespace.get(ip.pos.x, y);
            fungespace.put(ip.pos.x, y + trans, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::scissors(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.pop();
    const auto dst_x_orig = ip.pop();
    const auto h = ip.pop();
    const auto w = ip.pop();
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;

    for (Index i = h - 1; i >= 0; i--) {
        for (Index j = w - 1; j >= 0; --j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY) fungespace.put(dst_x, dst_y, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::corner(Fungespace &fungespace, InstructionPointer &ip) {
    ip.save_pos();
    ip.save_delta();

    ip.turn_left();
    ip.step_wrap(fungespace);
    ip.push(fungespace.get(ip.pos.x, ip.pos.y));

    ip.restore_pos();
    ip.restore_delta();

    return MoveAction{};
}

InstructionAction toys::kittycat(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.pop();
    const auto dst_x_orig = ip.pop();
    const auto h = ip.pop();
    const auto w = ip.pop();
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;

    for (Index i = 0; i < h; ++i) {
        for (Index j = 0; j < w; ++j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY) fungespace.put(dst_x, dst_y, v);
            fungespace.put(src_x, src_y, EMPTY);
        }
    }

    return MoveAction{};
}

InstructionAction toys::lightning_bolt(Fungespace &, InstructionPointer &ip) {
    ip.push(-ip.pop());
    return MoveAction{};
}

InstructionAction toys::boulder(Fungespace &fungespace, InstructionPointer &ip) {
    if (const auto trans = ip.pop(); trans < 0) {
        const auto x_start = fungespace.min_coord.x;
        const auto x_end = fungespace.max_coord.x;
        for (Index x = x_start; x < x_end; ++x) {
            const auto v = fungespace.get(x, ip.pos.y);
            fungespace.put(x + trans, ip.pos.y, v);
        }
    } else if (trans > 0) {
        const auto x_start = fungespace.max_coord.x;
        const auto x_end = fungespace.min_coord.x;
        for (Index x = x_start; x >= x_end; --x) {
            const auto v = fungespace.get(x, ip.pos.y);
            fungespace.put(x + trans, ip.pos.y, v);
        }
    }

    return MoveAction{};
}

InstructionAction toys::mailbox(Fungespace &, InstructionPointer &ip) {
    Cell prod = 1;
    while (ip.stack.size() > 0) prod *= ip.pop();
    ip.push(prod);
    return MoveAction{};
}

InstructionAction toys::necklace(Fungespace &fungespace, InstructionPointer &ip) {
    const auto v = ip.pop();

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
    ip.push(fungespace.get(ip.pos.x, ip.pos.y));

    ip.restore_pos();
    ip.restore_delta();

    return MoveAction{};
}

InstructionAction toys::chicane(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;
    const auto h = ip.pop();
    const auto w = ip.pop();
    const auto v = ip.pop();

    for (Index dst_y = y; dst_y < y + h; ++dst_y)
        for (Index dst_x = x; dst_x < x + w; ++dst_x) fungespace.put(dst_x, dst_y, v);

    return MoveAction{};
}

InstructionAction toys::barstool(Fungespace &fungespace, InstructionPointer &ip) {
    switch (ip.pop()) {
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
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::GoSouth));
        ip.instruction_stack.perform(Instruction::GoSouth, fungespace, ip);
        break;
    case 1:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::GoEast));
        ip.instruction_stack.perform(Instruction::GoEast, fungespace, ip);
        break;
    case 2:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::GoNorth));
        ip.instruction_stack.perform(Instruction::GoNorth, fungespace, ip);
        break;
    case 3:
        fungespace.put(ip.pos.x, ip.pos.y, static_cast<Cell>(Instruction::GoWest));
        ip.instruction_stack.perform(Instruction::GoWest, fungespace, ip);
        break;
    default:
        std::unreachable();
    }
    return MoveAction{};
}

InstructionAction toys::dixiecup(Fungespace &fungespace, InstructionPointer &ip) {
    const auto dst_y_orig = ip.pop();
    const auto dst_x_orig = ip.pop();
    const auto h = ip.pop();
    const auto w = ip.pop();
    const auto y = ip.pop() + ip.storage_offset.y;
    const auto x = ip.pop() + ip.storage_offset.x;

    for (Index i = h - 1; i >= 0; i--) {
        for (Index j = w - 1; j >= 0; --j) {
            const auto src_y = y + i;
            const auto src_x = x + j;
            const auto dst_y = dst_y_orig + i;
            const auto dst_x = dst_x_orig + j;

            const auto v = fungespace.get(src_x, src_y);
            if (v != EMPTY) fungespace.put(dst_x, dst_y, v);
            fungespace.put(src_x, src_y, EMPTY);
        }
    }

    return MoveAction{};
}

InstructionAction toys::television_antenna(Fungespace &fungespace, InstructionPointer &ip) {
    const auto y = ip.pop();
    const auto x = ip.pop();
    const auto v = ip.pop();

    if (const auto check = fungespace.get(x + ip.storage_offset.x, y + ip.storage_offset.y); check < v) {
        ip.push(v);
        ip.push(x);
        ip.push(y);
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
