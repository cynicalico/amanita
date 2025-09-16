#pragma once

#include "vm.hpp"

#include <SDL3/SDL.h>
#include <imgui.h>

namespace amanita {
class Editor {
public:
    std::unique_ptr<VM> vm;

    explicit Editor(std::unique_ptr<VM> vm);
    ~Editor();

    Editor(const Editor &other) = delete;
    Editor &operator=(const Editor &other) = delete;

    Editor(Editor &&other) noexcept = delete;
    Editor &operator=(Editor &&other) noexcept = delete;

    int mainloop();

private:
    SDL_Window *window_;
    SDL_GLContext gl_context_;

    ImGuiContext *imgui_ctx_;
};
} // namespace amanita
