#ifndef AMANITA_EDITOR_HPP
#define AMANITA_EDITOR_HPP

#include "interpreter.hpp"
#include "mizu/mizu.hpp"

enum class Mode { Run, Edit };

class Editor final : public mizu::Application {
public:
    mizu::G2d &g2d;
    mizu::Window &window;
    mizu::InputMgr &input;

    std::unique_ptr<mizu::Font> button_font;
    std::unique_ptr<mizu::Font> program_font;
    std::unique_ptr<mizu::Font> stackstack_font;
    std::unique_ptr<mizu::Font> title_font;

    const char *title_badge_text{"amanita"};
    glm::vec2 title_badge_size{};

    std::unique_ptr<mizu::gui::Gui> buttons;

    const std::filesystem::path path;
    Mode mode{Mode::Edit};
    std::int64_t cursor[2];
    std::int64_t cursor_delta[2];
    Interpreter interpreter{};

    Editor(mizu::Engine *engine, const std::filesystem::path &path);

    void update(double dt) override;

    void draw() override;

    void key_release_callback(mizu::Key key, mizu::Mod mods) override;

    void text_input_callback(const char *text) override;
};

#endif // AMANITA_EDITOR_HPP
