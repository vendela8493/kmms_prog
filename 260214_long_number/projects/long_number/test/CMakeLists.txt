set(SOURCES 
	long_number_test.cpp
)

add_executable(long_number_test ${SOURCES})
target_link_libraries(long_number_test
	${LIBRARY}
	gtest_main 
	gmock_main 
)

add_test(long_number_test long_number_test)