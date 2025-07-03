#ifndef AMANITA_EDITOR_HPP
#define AMANITA_EDITOR_HPP

#include "interpreter.hpp"
#include "mizu/mizu.hpp"

class Editor final : public mizu::Application {
public:
    mizu::G2d &g2d;
    mizu::Window &window;
    mizu::InputMgr &input;

    std::unique_ptr<mizu::Font> very_large_font;
    std::unique_ptr<mizu::Font> large_font;
    std::unique_ptr<mizu::Font> medium_font;
    std::unique_ptr<mizu::Font> small_font;

    mizu::Font *program_font;
    glm::vec2 program_char_size{};
    glm::vec2 program_size{};
    glm::vec2 program_pos{};

    mizu::Font *ip_info_font;
    glm::vec2 ip_info_char_size{};
    glm::vec2 ip_info_size{};
    glm::vec2 ip_info_pos{};

    mizu::Font *stackstack_font;
    glm::vec2 stackstack_char_size{};
    glm::vec2 stackstack_size{};
    glm::vec2 stackstack_pos{};

    mizu::Font *status_font;
    glm::vec2 status_char_size{};
    glm::vec2 status_size{};
    glm::vec2 status_pos{};

    std::int64_t tick{0};
    bool paused{true};
    mizu::Ticker<> ticker;
    bool slow_ticking{false};
    mizu::Ticker<> slow_ticker;
    std::int64_t viewport_pos[2];
    std::vector<InstructionPointer> active_list{};
    std::vector<InstructionPointer> inactive_list{};
    Interpreter interpreter{};

    Editor(mizu::Engine *engine,
           const std::filesystem::path &path,
           std::vector<std::string> args,
           std::int64_t skip_ticks);

    void update(double dt) override;

    void draw() override;
    void draw_program();
    void draw_ip_info();
    void draw_stacks();
    void draw_status();

    void key_press_callback(mizu::Key key, mizu::Mod mods) override;
    void key_release_callback(mizu::Key key, mizu::Mod mods) override;
    void text_input_callback(const char *text) override;

    void do_single_tick();
    void check_move_viewport();
};

#endif // AMANITA_EDITOR_HPP
