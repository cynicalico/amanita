cmake_minimum_required(VERSION 3.30)
project(amanita
        VERSION 1.0.0
        DESCRIPTION "Mycology compliant Funge-98 interpreter"
        HOMEPAGE_URL "https://github.com/cynicalico/amanita"
        LANGUAGES CXX)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

add_executable(amanita)
target_sources(
        amanita

        PRIVATE
        main.cpp

#        PRIVATE
#        FILE_SET amanita_headers
#        TYPE HEADERS
#        BASE_DIRS
#        include
#        FILES
)

target_compile_features(amanita PRIVATE cxx_std_23)
if (WIN32)
    target_compile_definitions(amanita PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
endif ()
if (MSVC)
    target_compile_options(amanita PRIVATE /utf-8)
endif ()

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.2.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmt)

target_link_libraries(amanita PRIVATE fmt::fmt)
