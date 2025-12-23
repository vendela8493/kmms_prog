project(bubble_sort)

add_executable(${PROJECT_NAME}
	main.cpp
	bubble_sort.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE .)