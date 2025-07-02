#include "editor.hpp"
#include "utf8.h"

constexpr std::size_t ROWS = 25;
constexpr std::size_t COLS = 80;
constexpr std::size_t STACKSTACK_DIGIT_MAX = 19;
constexpr std::size_t STACKSTACK_ENTRIES = 10;

constexpr float MARGIN = 5.0f;
constexpr float PROGRAM_MARGIN = 5.0f;
constexpr float STACKSTACK_MARGIN = 5.0f;

const mizu::Rgba BORDER_COLOR = mizu::rgb(0x767676);
const mizu::Rgba PROGRAM_COLOR = mizu::rgb(0xcccccc);
const mizu::Rgba CURSOR_COLOR = mizu::rgb(0x0037da);

void draw_rect(mizu::G2d &g2d, glm::vec2 pos, glm::vec2 size, const mizu::Color &color);

Editor::Editor(mizu::Engine *engine, const std::filesystem::path &path)
    : Application(engine),
      g2d(*engine->g2d),
      window(*engine->window),
      input(*engine->input),
      path(path),
      cursor{0, 0},
      cursor_delta{EAST[0], EAST[1]},
      interpreter(path) {
    button_font = std::make_unique<mizu::Font>(g2d, "font/ter-u18b.bdf");
    buttons = mizu::gui::GuiBuilder()
                      .start<mizu::gui::HStack>(
                              {.grow = mizu::gui::Grow::None,
                               .outer_pad = mizu::gui::Padding(MARGIN),
                               .inner_pad = MARGIN})
                      .add<mizu::gui::Button>(
                              {.grow = mizu::gui::Grow::None,
                               .font = button_font.get(),
                               .text = "Run",
                               .text_pad = mizu::gui::Padding(MARGIN),
                               .border = mizu::gui::PxBorder(BORDER_COLOR)})
                      .add<mizu::gui::Button>(
                              {.grow = mizu::gui::Grow::None,
                               .font = button_font.get(),
                               .text = "Load",
                               .text_pad = mizu::gui::Padding(MARGIN),
                               .border = mizu::gui::PxBorder(BORDER_COLOR)})
                      .build();
    buttons->resize(mizu::gui::UNDEFINED_SIZE_V, {0, 0});

    program_font = std::make_unique<mizu::Font>(g2d, "font/ter-u18b.bdf");
    program_char_size = program_font->calc_size("W");
    program_size = {
            PROGRAM_MARGIN + program_char_size.x * COLS + PROGRAM_MARGIN,
            PROGRAM_MARGIN + program_char_size.y * ROWS + PROGRAM_MARGIN};
    program_pos = {MARGIN + 1, buttons->size().y + 1};

    stackstack_font = std::make_unique<mizu::Font>(g2d, "font/ter-u12b.bdf");
    stackstack_char_size = stackstack_font->calc_size("W");
    stackstack_size = {
            STACKSTACK_MARGIN + stackstack_char_size.x * (STACKSTACK_DIGIT_MAX + 1) + STACKSTACK_MARGIN,
            STACKSTACK_MARGIN + stackstack_char_size.y * STACKSTACK_ENTRIES + STACKSTACK_MARGIN};
    stackstack_pos = {program_pos.x + program_size.x + 1 + MARGIN + 1, program_pos.y};

    const auto window_h = std::max(
            buttons->size().y + 1 + program_size.y + 1 + MARGIN,
            buttons->size().y + 3 * (1 + stackstack_size.y + 1) + 2 * MARGIN + MARGIN);

    window.set_size({MARGIN + 1 + program_size.x + 1 + MARGIN + 1 + stackstack_size.x + 1 + MARGIN, window_h});

    input.start_text_input();
}

void Editor::update(double dt) {
    buttons->update(input);
}

void Editor::draw() {
    g2d.clear(mizu::rgb(0x000000));

    buttons->draw(g2d);

    draw_program();
    draw_stacks();
}

void Editor::draw_program() {
    draw_rect(g2d, program_pos - glm::vec2(1.0f), program_size + glm::vec2(2.0f), BORDER_COLOR);

    g2d.fill_rect(
            {program_pos.x + PROGRAM_MARGIN + cursor[0] * program_char_size.x,
             program_pos.y + PROGRAM_MARGIN + cursor[1] * program_char_size.y},
            program_char_size,
            CURSOR_COLOR);

    for (std::int64_t y = 0; y < ROWS; ++y) {
        std::string s = "";
        for (std::int64_t x = 0; x < COLS; ++x)
            s += static_cast<char>(interpreter.fungespace.get(x, y));

        const glm::vec2 pos = {
                program_pos.x + PROGRAM_MARGIN, program_pos.y + PROGRAM_MARGIN + y * program_font->line_height()};
        program_font->draw(s, {pos.x, pos.y + program_font->pen_offset()}, PROGRAM_COLOR);
    }
}

void Editor::draw_stacks() {
    glm::vec2 pos = stackstack_pos;

    draw_rect(g2d, pos - glm::vec2(1.0f), stackstack_size + glm::vec2(2.0f), BORDER_COLOR);
    stackstack_font->draw(
            fmt::format("{:>{}}", "TOSS", STACKSTACK_DIGIT_MAX + 1),
            {pos.x + STACKSTACK_MARGIN, pos.y + STACKSTACK_MARGIN + stackstack_font->pen_offset()},
            mizu::rgb(0xffffff));
    pos.y += 1 + stackstack_size.y + 1 + MARGIN;

    draw_rect(g2d, pos - glm::vec2(1.0f), stackstack_size + glm::vec2(2.0f), BORDER_COLOR);
    stackstack_font->draw(
            fmt::format("{:>{}}", "SOSS", STACKSTACK_DIGIT_MAX + 1),
            {pos.x + STACKSTACK_MARGIN, pos.y + STACKSTACK_MARGIN + stackstack_font->pen_offset()},
            mizu::rgb(0xffffff));
    pos.y += 1 + stackstack_size.y + 1 + MARGIN;

    draw_rect(g2d, pos - glm::vec2(1.0f), stackstack_size + glm::vec2(2.0f), BORDER_COLOR);
    stackstack_font->draw(
            fmt::format("{:>{}}", "STACK N", STACKSTACK_DIGIT_MAX + 1),
            {pos.x + STACKSTACK_MARGIN, pos.y + STACKSTACK_MARGIN + stackstack_font->pen_offset()},
            mizu::rgb(0xffffff));
}

void Editor::key_release_callback(mizu::Key key, mizu::Mod mods) {
    if (key == mizu::Key::Escape)
        engine->shutdown();
    else if (key == mizu::Key::S && (is_flag_set(mods, mizu::Mod::LCtrl) || is_flag_set(mods, mizu::Mod::RCtrl)))
        fmt::println("save!");
}

void Editor::text_input_callback(const char *text) {}

void draw_rect(mizu::G2d &g2d, const glm::vec2 pos, glm::vec2 size, const mizu::Color &color) {
    // TODO: Add proper GL_LINE_LOOP support for mizu and use that instead
    size.x -= 1;
    size.y -= 1;
    g2d.line(pos, {pos.x + size.x, pos.y}, color);
    g2d.line({pos.x + size.x, pos.y}, pos + size, color);
    g2d.line({pos.x, pos.y + size.y}, pos + size, color);
    g2d.line(pos, {pos.x, pos.y + size.y}, color);
}
