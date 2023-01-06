cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_STANDARD 17)

project(so-commons-library C)

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
