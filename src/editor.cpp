#include "editor.hpp"
#include "utf8.h"

constexpr std::size_t ROWS = 40;
constexpr std::size_t COLS = 80;
constexpr std::size_t IP_INFO_CHAR_MAX = 22;
constexpr std::size_t STACK_DIGIT_MAX = 19;
constexpr std::size_t STACKSTACK_ENTRIES = 20;

constexpr float MARGIN = 5.0f;
constexpr float PROGRAM_MARGIN = 5.0f;
constexpr float IP_INFO_MARGIN = 5.0f;
constexpr float STACKSTACK_MARGIN = 5.0f;
constexpr float STATUS_MARGIN = 5.0f;

const mizu::Rgba BORDER_COLOR = mizu::rgb(0x767676);
const mizu::Rgba PROGRAM_COLOR = mizu::rgb(0xcccccc);
const mizu::Rgba CURSOR_COLOR = mizu::rgb(0x0037da);

void draw_rect(mizu::G2d &g2d, glm::vec2 pos, glm::vec2 size, const mizu::Color &color);

Editor::Editor(
        mizu::Engine *engine, const std::filesystem::path &path, std::vector<std::string> args, std::int64_t skip_ticks)
    : Application(engine),
      g2d(*engine->g2d),
      window(*engine->window),
      input(*engine->input),
      viewport_pos{0, 0},
      interpreter(path) {
    very_large_font = std::make_unique<mizu::Font>(g2d, "font/ter-u24b.bdf");
    large_font = std::make_unique<mizu::Font>(g2d, "font/ter-u18b.bdf");
    medium_font = std::make_unique<mizu::Font>(g2d, "font/ter-u14b.bdf");
    small_font = std::make_unique<mizu::Font>(g2d, "font/ter-u12b.bdf");

    program_font = large_font.get();
    program_char_size = program_font->calc_size("W");
    program_size = {
            PROGRAM_MARGIN + program_char_size.x * COLS + PROGRAM_MARGIN,
            PROGRAM_MARGIN + program_char_size.y * ROWS + PROGRAM_MARGIN};
    program_pos = {MARGIN + 1, MARGIN + 1};

    ip_info_font = medium_font.get();
    ip_info_char_size = ip_info_font->calc_size("W");
    ip_info_size = {IP_INFO_MARGIN + ip_info_char_size.x * (IP_INFO_CHAR_MAX + 1) + IP_INFO_MARGIN, program_size.y};
    ip_info_pos = {program_pos.x + program_size.x + 1 + MARGIN + 1, program_pos.y};

    stackstack_font = medium_font.get();
    stackstack_char_size = stackstack_font->calc_size("W");
    stackstack_size = {
            STACKSTACK_MARGIN + stackstack_char_size.x * (STACK_DIGIT_MAX + 1) + STACKSTACK_MARGIN,
            STACKSTACK_MARGIN + stackstack_char_size.y * (STACKSTACK_ENTRIES + 1) + STACKSTACK_MARGIN};
    stackstack_pos = {ip_info_pos.x + ip_info_size.x + 1 + MARGIN + 1, program_pos.y};

    status_font = medium_font.get();
    status_char_size = status_font->calc_size("W");
    status_size = {program_size.x, STATUS_MARGIN + status_char_size.y + STATUS_MARGIN};
    status_pos = {program_pos.x, program_pos.y + program_size.y + 1 + MARGIN + 1};

    const auto window_h = std::max(
            MARGIN + 1 + program_size.y + 1 + MARGIN + 1 + status_size.y + 1 + MARGIN,
            MARGIN + 2 * (1 + stackstack_size.y + 1) + 1 * MARGIN + MARGIN);

    window.set_size(
            {MARGIN + 1 + program_size.x + 1 + MARGIN + 1 + ip_info_size.x + 1 + MARGIN + 1 + stackstack_size.x + 1 +
                     MARGIN,
             window_h});

    input.start_text_input();

    ticker = mizu::Ticker(std::chrono::milliseconds(2));
    slow_ticker = mizu::Ticker(std::chrono::milliseconds(50));
    interpreter.args = std::move(args);
    active_list.emplace_back(&interpreter);

    if (skip_ticks > 0) {
        for (std::int64_t i = 0; i < skip_ticks; i++) {
            do_single_tick();
            check_move_viewport();
        }
    }
}

void Editor::update(double dt) {
    if (!paused) {
        const auto tick_count = ticker.tick();
        for (std::uint64_t i = 0; i < tick_count; ++i) {
            do_single_tick();
            check_move_viewport();
        }
    } else if (slow_ticking) {
        const auto tick_count = slow_ticker.tick();
        for (std::uint64_t i = 0; i < tick_count; ++i) {
            do_single_tick();
            check_move_viewport();
        }
    }
}

void Editor::draw() {
    g2d.clear(mizu::rgb(0x000000));

    draw_program();
    draw_ip_info();
    draw_stacks();
    draw_status();
}

void Editor::draw_program() {
    draw_rect(g2d, program_pos - glm::vec2(1.0f), program_size + glm::vec2(2.0f), BORDER_COLOR);

    int64_t cursor_pos[2] = {active_list[0].pos[0] - viewport_pos[0], active_list[0].pos[1] - viewport_pos[1]};
    g2d.fill_rect(
            {program_pos.x + PROGRAM_MARGIN + cursor_pos[0] * program_char_size.x,
             program_pos.y + PROGRAM_MARGIN + cursor_pos[1] * program_char_size.y},
            program_char_size,
            CURSOR_COLOR);


    glm::vec2 pos = {program_pos.x + PROGRAM_MARGIN, program_pos.y + PROGRAM_MARGIN};
    for (std::int64_t y = viewport_pos[1]; y < viewport_pos[1] + ROWS; ++y) {
        std::string s = "";
        for (std::int64_t x = viewport_pos[0]; x < viewport_pos[0] + COLS; ++x) {
            const auto v = interpreter.fungespace.get(x, y);
            // TODO: Display something other than a space
            if (v == '\0' || v == '\r' || v == '\n')
                s += ' ';
            else
                s += static_cast<char>(v);
        }

        program_font->draw(s, {pos.x, pos.y + program_font->pen_offset()}, PROGRAM_COLOR);
        pos.y += program_font->line_height();
    }
}

void Editor::draw_ip_info() {
    draw_rect(g2d, ip_info_pos - glm::vec2(1.0f), ip_info_size + glm::vec2(2.0f), BORDER_COLOR);

    glm::vec2 pos = ip_info_pos;
    auto add_line = [&](std::string_view text, bool right_aligned) {
        std::string s;
        if (right_aligned)
            s = fmt::format("{:>{}}", text, IP_INFO_CHAR_MAX + 1);
        else
            s = text;
        ip_info_font->draw(
                s, {pos.x + IP_INFO_MARGIN, pos.y + IP_INFO_MARGIN + ip_info_font->pen_offset()}, mizu::rgb(0xffffff));
        pos.y += ip_info_char_size.y;
    };

    add_line("IP Info", false);
    pos.y += ip_info_char_size.y;

    if (!active_list.empty()) {
        add_line("ID", false);
        pos.y -= ip_info_char_size.y;
        add_line(fmt::format("{}", active_list[0].id), true);

        pos.y += ip_info_char_size.y;
        add_line("Pos (x, y)", false);
        add_line(fmt::format("{}", active_list[0].pos[0]), true);
        add_line(fmt::format("{}", active_list[0].pos[1]), true);

        pos.y += ip_info_char_size.y;
        add_line("Delta (dx, dy)", false);
        add_line(fmt::format("{}", active_list[0].delta[0]), true);
        add_line(fmt::format("{}", active_list[0].delta[1]), true);

        pos.y += ip_info_char_size.y;
        add_line("Storage Offset (dx, dy)", false);
        add_line(fmt::format("{}", active_list[0].storage_offset[0]), true);
        add_line(fmt::format("{}", active_list[0].storage_offset[1]), true);

        pos.y += ip_info_char_size.y;
        add_line("Stringmode", false);
        pos.y -= ip_info_char_size.y;
        add_line(active_list[0].stringmode ? "true" : "false", true);

        add_line("Hovermode", false);
        pos.y -= ip_info_char_size.y;
        add_line(active_list[0].hovermode ? "true" : "false", true);

        add_line("Invertmode", false);
        pos.y -= ip_info_char_size.y;
        add_line(active_list[0].stack.invertmode ? "true" : "false", true);

        add_line("Queuemode", false);
        pos.y -= ip_info_char_size.y;
        add_line(active_list[0].stack.queuemode ? "true" : "false", true);

        add_line("Switchmode", false);
        pos.y -= ip_info_char_size.y;
        add_line(active_list[0].hovermode ? "true" : "false", true);

        pos.y += ip_info_char_size.y;
        add_line("Fingerprint Semantics", false);
        for (std::size_t i = 0; i < 26; ++i) {
            add_line(fmt::format("{}", static_cast<char>('A' + i)), false);
            pos.y -= ip_info_char_size.y;
            add_line(fmt::format("{}", active_list[0].instruction_stack.loaded_fingerprints[i].back()), true);
        }
    }
}

void Editor::draw_stacks() {
    glm::vec2 pos = stackstack_pos;
    auto add_line = [&](std::string_view text, bool right_aligned) {
        std::string s;
        if (right_aligned)
            s = fmt::format("{:>{}}", text, STACK_DIGIT_MAX + 1);
        else
            s = text;
        stackstack_font->draw(
                s,
                {pos.x + IP_INFO_MARGIN, pos.y + IP_INFO_MARGIN + stackstack_font->pen_offset()},
                mizu::rgb(0xffffff));
        pos.y += stackstack_char_size.y;
    };

    pos.y = stackstack_pos.y;
    draw_rect(g2d, pos - glm::vec2(1.0f), stackstack_size + glm::vec2(2.0f), BORDER_COLOR);
    add_line("TOSS", false);
    if (!active_list.empty()) {
        const auto &stack = active_list[0].stack;
        const auto &toss = stack.stacks[stack.toss];
        if (!toss.empty()) {
            std::int64_t start = static_cast<std::int64_t>(toss.size() - 1);
            std::int64_t end = std::max(
                    static_cast<std::int64_t>(0),
                    static_cast<std::int64_t>(toss.size()) - static_cast<std::int64_t>(STACKSTACK_ENTRIES));
            for (auto i = start; i >= end; i--)
                add_line(fmt::format("{}", toss[i]), true);
        } else {
            add_line("EMPTY", true);
        }
    }

    pos.y = stackstack_pos.y + (1 + stackstack_size.y + 1 + MARGIN) * 1;
    draw_rect(g2d, pos - glm::vec2(1.0f), stackstack_size + glm::vec2(2.0f), BORDER_COLOR);
    add_line("SOSS", false);
    if (!active_list.empty()) {
        const auto &stack = active_list[0].stack;
        if (stack.soss != stack.toss) {
            const auto &soss = stack.stacks[stack.soss];
            if (!soss.empty()) {
                std::int64_t start = static_cast<std::int64_t>(soss.size() - 1);
                std::int64_t end = std::max(
                        static_cast<std::int64_t>(0),
                        static_cast<std::int64_t>(soss.size()) - static_cast<std::int64_t>(STACKSTACK_ENTRIES));
                for (auto i = start; i >= end; i--)
                    add_line(fmt::format("{}", soss[i]), true);
            } else {
                add_line("EMPTY", true);
            }
        } else {
            add_line("N/A", true);
        }
    }

    // pos.y = stackstack_pos.y + (1 + stackstack_size.y + 1 + MARGIN) * 2;
    // draw_rect(g2d, pos - glm::vec2(1.0f), stackstack_size + glm::vec2(2.0f), BORDER_COLOR);
    // add_line("NYI", false);
}

void Editor::draw_status() {
    draw_rect(g2d, status_pos - glm::vec2(1.0f), status_size + glm::vec2(2.0f), BORDER_COLOR);
    if (!active_list.empty()) {
        status_font->draw(
                fmt::format("Tick: {}", tick),
                {status_pos.x + STATUS_MARGIN, status_pos.y + STATUS_MARGIN + stackstack_font->pen_offset()},
                mizu::rgb(0xffffff));
    }
}

void Editor::key_press_callback(mizu::Key key, mizu::Mod mods) {
    if (key == mizu::Key::S && paused && !slow_ticking) {
        slow_ticking = true;
        slow_ticker.reset();
    }

    if (key == mizu::Key::Left)
        viewport_pos[0]--;
    if (key == mizu::Key::Right)
        viewport_pos[0]++;
    if (key == mizu::Key::Up)
        viewport_pos[1]--;
    if (key == mizu::Key::Down)
        viewport_pos[1]++;
}

void Editor::key_release_callback(mizu::Key key, mizu::Mod mods) {
    if (key == mizu::Key::Escape)
        engine->shutdown();

    if (key == mizu::Key::Space) {
        if (paused) {
            paused = false;
            ticker.reset();
        } else {
            paused = true;
        }
    }

    if (key == mizu::Key::Tab && !active_list.empty()) {
        do_single_tick();
        check_move_viewport();
    }

    if (key == mizu::Key::S)
        slow_ticking = false;
}

void Editor::text_input_callback(const char *text) {}

void Editor::do_single_tick() {
    inactive_list.clear();

    for (auto &ip: active_list) {
        Cell ins;
        do {
            ins = interpreter.fungespace.get(ip.pos[0], ip.pos[1]);
            if (!ip.stringmode && (ins == Instruction::Space || ins == Instruction::JumpOver))
                ip.step_to_next_instruction(interpreter.fungespace, '\0', ins == Instruction::JumpOver);
            else
                break;
        } while (true);
        ip.cache_ins = ins;

        auto action = ip.instruction_stack.perform(static_cast<Instruction>(ins), interpreter.fungespace, ip);
        std::visit(
                overloaded{
                        [&](const IterAction &a) {
                            if (!ip.alive)
                                return;

                            for (const auto &sub_action: a.actions) {
                                if (std::holds_alternative<SplitAction>(sub_action)) {
                                    auto new_ip = InstructionPointer(ip);
                                    new_ip.reflect();

                                    inactive_list.push_back(std::move(new_ip));
                                } else if (std::holds_alternative<QuitAction>(sub_action)) {
                                    std::exit(std::get<QuitAction>(sub_action).exit_code);
                                }
                            }

                            inactive_list.push_back(std::move(ip));
                        },
                        [&](const KillAction &) {
                            /* do nothing, ip does not live on */
                        },
                        [&](const MoveAction &) {
                            inactive_list.push_back(std::move(ip));
                        },
                        [&](const SplitAction &) {
                            auto new_ip = InstructionPointer(ip);
                            new_ip.reflect();

                            inactive_list.push_back(std::move(new_ip));
                            inactive_list.push_back(std::move(ip));
                        },
                        [&](const QuitAction &a) {
                            std::exit(a.exit_code);
                        }},
                action);
    }

    std::swap(active_list, inactive_list);
    for (auto &ip: active_list)
        ip.step_to_next_instruction(interpreter.fungespace, ip.cache_ins, false);

    tick++;
}

void Editor::check_move_viewport() {
    const auto &ip = active_list[0];

    // Check move x
    if (ip.pos[0] < viewport_pos[0])
        while (ip.pos[0] < viewport_pos[0])
            viewport_pos[0]--;
    else if (ip.pos[0] >= viewport_pos[0] + COLS)
        while (ip.pos[0] >= viewport_pos[0] + COLS)
            viewport_pos[0]++;

    // Check move y
    if (ip.pos[1] < viewport_pos[1])
        while (ip.pos[1] < viewport_pos[1])
            viewport_pos[1]--;
    else if (ip.pos[1] >= viewport_pos[1] + ROWS)
        while (ip.pos[1] >= viewport_pos[1] + ROWS)
            viewport_pos[1]++;
}

void draw_rect(mizu::G2d &g2d, const glm::vec2 pos, glm::vec2 size, const mizu::Color &color) {
    // TODO: Add proper GL_LINE_LOOP support for mizu and use that instead
    size.x -= 1;
    size.y -= 1;
    g2d.line(pos, {pos.x + size.x, pos.y}, color);
    g2d.line({pos.x + size.x, pos.y}, pos + size, color);
    g2d.line({pos.x, pos.y + size.y}, pos + size, color);
    g2d.line(pos, {pos.x, pos.y + size.y}, color);
}
