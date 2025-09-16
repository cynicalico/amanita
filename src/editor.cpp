#include "editor.hpp"

#include <fmt/format.h>
#include <fmt/std.h>
#include <glad/gl.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

amanita::Editor::Editor(std::unique_ptr<VM> vm)
    : vm(std::move(vm)) {
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(fmt::format("Failed to initialize SDL: {}", SDL_GetError()));

    window_ = SDL_CreateWindow("amanita", 1280, 720, SDL_WINDOW_OPENGL);
    if (!window_)
        throw std::runtime_error(fmt::format("Failed to create SDL window: {}", SDL_GetError()));

    gl_context_ = SDL_GL_CreateContext(window_);
    if (!gl_context_)
        throw std::runtime_error(fmt::format("Failed to create GL Context: {}", SDL_GetError()));

    int glad_version = gladLoadGL(SDL_GL_GetProcAddress);
    if (glad_version == 0)
        throw std::runtime_error("Failed to load OpenGL with Glad");

    IMGUI_CHECKVERSION();
    imgui_ctx_ = ImGui::CreateContext();
    ImGui::GetIO();
    ImGui_ImplSDL3_InitForOpenGL(window_, gl_context_);
    ImGui_ImplOpenGL3_Init("#version 130");
}

amanita::Editor::~Editor() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext(imgui_ctx_);

    SDL_GL_DestroyContext(gl_context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

int amanita::Editor::mainloop() {
    bool running = true;
    do {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);
            switch (e.type) {
            case SDL_EVENT_QUIT: running = false; break;
            default:;
            }
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        if (ImGui::Begin("Info"))
            ImGui::Text("Hello, world!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window_);
    } while (running);

    return 0;
}
