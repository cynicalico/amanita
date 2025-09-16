include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.2.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        glad2
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG v2.0.8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glad2)
add_subdirectory(${glad2_SOURCE_DIR}/cmake ${glad2_BINARY_DIR})
if (WIN32)
    glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6 wgl=1.0)
else ()
    glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6 egl=1.5)
endif ()

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.92.2
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        pcg
        GIT_REPOSITORY https://github.com/imneme/pcg-cpp
        GIT_TAG 428802d1a5634f96bcd0705fab379ff0113bcf13
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(pcg)

FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-3.2.18
        GIT_SHALLOW TRUE
)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
FetchContent_MakeAvailable(sdl3)

add_library(amanita_thirdparty)
add_library(amanita::amanita_thirdparty ALIAS amanita_thirdparty)

target_sources(
        amanita_thirdparty

        PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp

        PUBLIC
        FILE_SET imgui_headers
        TYPE HEADERS
        BASE_DIRS
        ${imgui_SOURCE_DIR}
        FILES
        ${imgui_SOURCE_DIR}/imconfig.h
        ${imgui_SOURCE_DIR}/imgui.h
        ${imgui_SOURCE_DIR}/imgui_internal.h
        ${imgui_SOURCE_DIR}/imstb_rectpack.h
        ${imgui_SOURCE_DIR}/imstb_textedit.h
        ${imgui_SOURCE_DIR}/imstb_truetype.h

        PUBLIC
        FILE_SET imgui_backend_headers
        TYPE HEADERS
        BASE_DIRS
        ${imgui_SOURCE_DIR}/backends
        FILES
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h

        PUBLIC
        FILE_SET pcg_headers
        TYPE HEADERS
        BASE_DIRS
        ${pcg_SOURCE_DIR}/include
        FILES
        ${pcg_SOURCE_DIR}/include/pcg_extras.hpp
        ${pcg_SOURCE_DIR}/include/pcg_random.hpp
        ${pcg_SOURCE_DIR}/include/pcg_uint128.hpp

        PRIVATE
        FILE_SET amanita_thirdparty_headers
        TYPE HEADERS
        BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        argparse.hpp
)

target_link_libraries(
        amanita_thirdparty

        PUBLIC
        fmt::fmt
        glad_gl_core_46
        SDL3::SDL3
)
