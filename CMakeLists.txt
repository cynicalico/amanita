cmake_minimum_required(VERSION 3.30)
project(amanita)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

include(thirdparty/get_cpm.cmake)

CPMAddPackage(
        NAME mizu
        GITHUB_REPOSITORY cynicalico/mizu
        GIT_TAG acb9dd41f109165232ea031de32a4b0060468ed5
        OPTIONS "MIZU_BUILD_EXAMPLE OFF"
)

add_executable(amanita
        include/fungespace.hpp
        include/instruction_action.hpp
        include/instruction_pointer.hpp
        include/instructions.hpp
        include/interpreter.hpp
        include/sops.hpp
        include/stackstack.hpp
        src/fungespace.cpp
        src/instruction_pointer.cpp
        src/interpreter.cpp
        src/stackstack.cpp
        main.cpp)

target_compile_features(amanita PRIVATE cxx_std_23)

if (WIN32)
    target_compile_options(amanita PUBLIC /utf-8 /W4)
endif ()

target_include_directories(amanita PRIVATE include)
target_include_directories(amanita PRIVATE thirdparty)

target_link_libraries(amanita PRIVATE mizu::mizu)

add_custom_command(TARGET amanita POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:amanita> $<TARGET_RUNTIME_DLLS:amanita>
        COMMAND_EXPAND_LISTS
)
