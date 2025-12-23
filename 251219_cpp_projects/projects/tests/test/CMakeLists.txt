set(SOURCES 
	test_bubble.cpp
)

add_executable(test_bubble ${SOURCES})
target_link_libraries(test_bubble 
	gtest_main 
	${LIBRARY}
)

add_test(test_bubble test_bubble)