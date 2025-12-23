cmake_minimum_required(VERSION 3.5)

project(251219_cpp_projects)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(bubble_sort)
add_subdirectory(obuchaika)
add_subdirectory(tests)

set(CMAKE_SUPPRESS_REGENERATION true)