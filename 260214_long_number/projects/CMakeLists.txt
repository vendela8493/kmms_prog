cmake_minimum_required(VERSION 3.2...4.1)

project(260220_cpp_classes)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(long_number)

set(CMAKE_SUPPRESS_REGENERATION true)