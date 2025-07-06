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
        include/fungespace.hpp
        include/instruction_pointer.hpp
        include/instruction_stack.hpp
        include/instructions.hpp
        include/sops.hpp
        include/stackstack.hpp

        src/base_instructions.cpp
        src/common.cpp
        src/editor.cpp
        src/fungespace.cpp
        src/instruction_pointer.cpp
        src/instruction_stack.cpp
        src/stackstack.cpp

        include/fingerprints/catseye/hrti.hpp
        include/fingerprints/catseye/mode.hpp
        include/fingerprints/catseye/modu.hpp
        include/fingerprints/catseye/orth.hpp
        include/fingerprints/catseye/perl.hpp
        include/fingerprints/catseye/null.hpp
        include/fingerprints/catseye/refc.hpp
        include/fingerprints/catseye/roma.hpp
        include/fingerprints/catseye/toys.hpp
        include/fingerprints/rcs/dirf.hpp
        include/fingerprints/rcs/evar.hpp
        include/fingerprints/rcs/file.hpp
        include/fingerprints/rcs/fixp.hpp
        include/fingerprints/rcs/fpdp.hpp
        include/fingerprints/rcs/fpsp.hpp
        include/fingerprints/rcs/subr.hpp

        src/fingerprints/catseye/hrti.cpp
        src/fingerprints/catseye/mode.cpp
        src/fingerprints/catseye/modu.cpp
        src/fingerprints/catseye/orth.cpp
        src/fingerprints/catseye/perl.cpp
        src/fingerprints/catseye/refc.cpp
        src/fingerprints/catseye/roma.cpp
        src/fingerprints/catseye/toys.cpp
        src/fingerprints/rcs/dirf.cpp
        src/fingerprints/rcs/evar.cpp
        src/fingerprints/rcs/file.cpp
        src/fingerprints/rcs/fixp.cpp
        src/fingerprints/rcs/fpdp.cpp
        src/fingerprints/rcs/fpsp.cpp
        src/fingerprints/rcs/subr.cpp

        thirdparty/argparse.hpp
        thirdparty/subprocess.h
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
