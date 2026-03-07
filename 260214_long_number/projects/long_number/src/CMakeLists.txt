target_sources(${LIBRARY}
	PRIVATE
		long_number.cpp
	PUBLIC
		long_number.hpp
)

target_include_directories(${LIBRARY} 
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}"
)