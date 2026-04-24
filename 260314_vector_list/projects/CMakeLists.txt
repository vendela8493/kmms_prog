cmake_minimum_required(VERSION 3.2...4.1)

project(260314_vector_list)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(vector_list)

set(CMAKE_SUPPRESS_REGENERATION true)  