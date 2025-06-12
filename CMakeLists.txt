cmake_minimum_required(VERSION 3.31)
project(amanita)

add_executable(amanita main.cpp)

target_compile_features(amanita PRIVATE cxx_std_23)
target_include_directories(amanita PRIVATE include)
