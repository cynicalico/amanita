#include "editor.hpp"
#include "utf8.h"

Editor::Editor(mizu::Engine *engine, const std::filesystem::path &path)
    : Application(engine),
      g2d(*engine->g2d),
      window(*engine->window),
      input(*engine->input),
      path(path),
      cursor{0, 0},
      cursor_delta{EAST[0], EAST[1]},
      interpreter(path) {
    button_font = std::make_unique<mizu::Font>(g2d, "font/ter-u16b.bdf");
    program_font = std::make_unique<mizu::Font>(g2d, "font/ter-u16b.bdf");
    stackstack_font = std::make_unique<mizu::Font>(g2d, "font/ter-u12b.bdf");
    title_font = std::make_unique<mizu::Font>(g2d, "font/ter-u20b.bdf");

    title_badge_size = title_font->calc_size("amanita");

    buttons = mizu::gui::GuiBuilder()
                      .start<mizu::gui::HStack>(
                              {.grow = mizu::gui::Grow::None, .outer_pad = mizu::gui::Padding(3.0f), .inner_pad = 3.0f})
                      .add<mizu::gui::Button>(
                              {.grow = mizu::gui::Grow::None,
                               .font = button_font.get(),
                               .text = "Edit",
                               .text_pad = mizu::gui::Padding(3.0f, 5.0f)})
                      .add<mizu::gui::Button>(
                              {.grow = mizu::gui::Grow::None,
                               .font = button_font.get(),
                               .text = "Load",
                               .text_pad = mizu::gui::Padding(3.0f, 5.0f)})
                      .build();
    buttons->resize(mizu::gui::UNDEFINED_SIZE_V, {0, 0});

    const auto w_size = program_font->calc_size("W");
    window.set_size({3 + 1 + w_size.x * 80 + 1 + 3, buttons->size().y + 1 + w_size.y * 25 + 1 + title_badge_size.y});

    input.start_text_input();
}

void Editor::update(double dt) {
    buttons->update(input);
}

void Editor::draw() {
    g2d.clear(mizu::rgb(0x000000));

    title_font->draw(
            title_badge_text,
            {window.size().x - title_badge_size.x - 3,
             window.size().y - title_font->line_height() + title_font->pen_offset()});
    buttons->draw(g2d);

    g2d.line({3, buttons->size().y}, {window.size().x - 3, buttons->size().y}, mizu::rgb(0xffffff));
    g2d.line({3, buttons->size().y}, {3, window.size().y - title_badge_size.y}, mizu::rgb(0xffffff));
    g2d.line(
            {3, window.size().y - title_badge_size.y},
            {window.size().x - 3, window.size().y - title_badge_size.y},
            mizu::rgb(0xffffff));
    g2d.line(
            {window.size().x - 4, buttons->size().y},
            {window.size().x - 4, window.size().y - title_badge_size.y},
            mizu::rgb(0xffffff));

    for (std::int64_t y = 0; y < 25; ++y) {
        std::string s = "";
        for (std::int64_t x = 0; x < 80; ++x)
            s += static_cast<char>(interpreter.fungespace.get(x, y));

        const glm::vec2 pos = {4, buttons->size().y + 1 + y * program_font->line_height()};
        program_font->draw(s, {pos.x, pos.y + program_font->pen_offset()});
    }
}

void Editor::key_release_callback(mizu::Key key, mizu::Mod mods) {
    if (key == mizu::Key::Escape)
        engine->shutdown();
    else if (key == mizu::Key::S && (is_flag_set(mods, mizu::Mod::LCtrl) || is_flag_set(mods, mizu::Mod::RCtrl)))
        fmt::println("save!");
}

void Editor::text_input_callback(const char *text) {
    if (mode == Mode::Edit) {
        const auto cp = utf8::next(text, text + strlen(text));
        interpreter.fungespace.put(cursor[0], cursor[1], static_cast<Cell>(cp));

        cursor[0] += cursor_delta[0];
        cursor[1] += cursor_delta[1];
    }
}
