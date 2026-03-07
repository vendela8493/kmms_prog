project(long_numbers)

set(LIBRARY long_number_lib)

add_library(${LIBRARY} "")

add_subdirectory(src)
add_subdirectory(test)