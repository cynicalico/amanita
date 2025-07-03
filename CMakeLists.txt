cmake_minimum_required(VERSION 3.30)
project(amanita
        VERSION 1.0.0
        DESCRIPTION "Mycology compliant Funge-98 interpreter"
        HOMEPAGE_URL "https://github.com/cynicalico/amanita"
        LANGUAGES CXX)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

include(thirdparty/get_cpm.cmake)

CPMAddPackage(
        NAME mizu
        GITHUB_REPOSITORY cynicalico/mizu
        GIT_TAG 87969bdbfbf38002b644c5d97c3b462f3a0e6ef1
        OPTIONS "MIZU_BUILD_EXAMPLE OFF"
)

add_executable(amanita
        include/base_instructions.hpp
        include/common.hpp
        include/editor.hpp
        include/fingerprints.hpp
        include/fungespace.hpp
        include/instruction_pointer.hpp
        include/instruction_stack.hpp
        include/instructions.hpp
        include/interpreter.hpp
        include/sops.hpp
        include/stackstack.hpp

        src/base_instructions.cpp
        src/common.cpp
        src/editor.cpp
        src/fingerprints.cpp
        src/fungespace.cpp
        src/instruction_pointer.cpp
        src/instruction_stack.cpp
        src/interpreter.cpp
        src/stackstack.cpp

        include/fingerprints/file.hpp
        include/fingerprints/hrti.hpp
        include/fingerprints/mode.hpp
        include/fingerprints/modu.hpp
        include/fingerprints/orth.hpp
        include/fingerprints/null.hpp
        include/fingerprints/refc.hpp
        include/fingerprints/roma.hpp
        include/fingerprints/toys.hpp

        src/fingerprints/file.cpp
        src/fingerprints/hrti.cpp
        src/fingerprints/mode.cpp
        src/fingerprints/modu.cpp
        src/fingerprints/orth.cpp
        src/fingerprints/refc.cpp
        src/fingerprints/roma.cpp
        src/fingerprints/toys.cpp

        thirdparty/argparse.hpp
        thirdparty/utf8.h

        main.cpp)

target_compile_features(amanita PRIVATE cxx_std_23)

if (WIN32)
    target_compile_options(amanita PUBLIC /utf-8 /W4)
endif ()

target_include_directories(amanita PRIVATE include thirdparty)

target_link_libraries(amanita PRIVATE mizu::mizu)

add_custom_command(TARGET amanita POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:amanita> $<TARGET_RUNTIME_DLLS:amanita>
        COMMAND_EXPAND_LISTS
)
