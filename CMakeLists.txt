cmake_minimum_required(VERSION 3.30)
project(amanita
        VERSION 1.0.0
        DESCRIPTION "Mycology compliant Funge-98 interpreter"
        HOMEPAGE_URL "https://github.com/cynicalico/amanita"
        LANGUAGES C CXX)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

add_executable(amanita)
target_sources(
        amanita

        PRIVATE
        src/fingerprint/catseye/modu.cpp
        src/fingerprint/catseye/roma.cpp
        src/fingerprint/rcs/file.cpp
        src/base_semantics.cpp
        src/editor.cpp
        src/fingerprint.cpp
        src/fungespace.cpp
        src/instruction_pointer.cpp
        src/semantic_stack.cpp
        src/sops.cpp
        src/stackstack.cpp
        src/state.cpp
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
        include/fingerprint/rcs/file.hpp
        include/action.hpp
        include/base_semantics.hpp
        include/editor.hpp
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
)

target_compile_features(amanita PRIVATE cxx_std_23)
if (WIN32)
    target_compile_definitions(amanita PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
endif ()
if (MSVC)
    target_compile_options(amanita PRIVATE /utf-8)
endif ()

add_subdirectory(thirdparty)
target_link_libraries(amanita PRIVATE amanita_thirdparty)
