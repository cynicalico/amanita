cmake_minimum_required(VERSION 3.31)
project(amanita)

include(thirdparty/get_cpm.cmake)

CPMAddPackage(
        NAME mizu
        GITHUB_REPOSITORY cynicalico/mizu
        GIT_TAG 8b54f7c490ed8f8415a83da380666c2752e7be81
        OPTIONS "MIZU_BUILD_EXAMPLE OFF"
)

add_executable(amanita
        include/fungespace.hpp
        src/fungespace.cpp
        main.cpp)

target_compile_features(amanita PRIVATE cxx_std_23)
target_include_directories(amanita PRIVATE include)

target_link_libraries(amanita PRIVATE mizu::mizu)
