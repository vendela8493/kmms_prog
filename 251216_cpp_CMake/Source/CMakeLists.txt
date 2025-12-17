cmake_minimum_required(VERSION 3.2...4.1)

project(251216_cpp_CMake)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(bubble_sort)
add_subdirectory(bubble_sort_mf)
add_subdirectory(obuchaika)
add_subdirectory(unit_test_example)

set(CMAKE_SUPPRESS_REGENERATION true)