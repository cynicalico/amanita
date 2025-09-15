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
        src/fingerprint/catseye/modu.cpp
        src/fingerprint/catseye/roma.cpp
        src/base_semantics.cpp
        src/fingerprint.cpp
        src/fungespace.cpp
        src/instruction_pointer.cpp
        src/semantic_stack.cpp
        src/sops.cpp
        src/stackstack.cpp
        src/vec.cpp
        src/vm.cpp
        main.cpp

        PRIVATE
        FILE_SET amanita_headers
        TYPE HEADERS
        BASE_DIRS
        include
        FILES
        include/fingerprint/catseye/modu.hpp
        include/fingerprint/catseye/null.hpp
        include/fingerprint/catseye/roma.hpp
        include/action.hpp
        include/base_semantics.hpp
        include/fingerprint.hpp
        include/fungespace.hpp
        include/instruction.hpp
        include/instruction_pointer.hpp
        include/semantic.hpp
        include/semantic_stack.hpp
        include/sops.hpp
        include/stackstack.hpp
        include/state.hpp
        include/vec.hpp
        include/vm.hpp

        PRIVATE
        FILE_SET amanita_thirdparty_headers
        TYPE HEADERS
        BASE_DIRS
        thirdparty
        FILES
        thirdparty/argparse.hpp
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
