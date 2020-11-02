cmake_minimum_required(VERSION 3.5)

# Options TODO: CREATE TEST BUILD
option(test "test" 0)

# Project name
project(SciLib VERSION 0.0.1)

if (NOT test)
	# Define variables
	set(SOURCES main.cpp)

	# Create executable
	add_executable(scilib 
		${SOURCES}
	)

	# Add compiler options
	add_compile_options(-Wall -Wextra -Wpedantic -g -DDEBUG=1)

	# Specify standard
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	#configure_file(include/scilib.h include/scilib.h)

	# Includes
	target_include_directories(scilib PUBLIC include src)

	# Move scilib to ../release
	add_custom_command(TARGET scilib
		POST_BUILD
		COMMAND mv scilib ../release
	)
else()
	# Define variables
	set(SOURCES test/test_main.o test/test_Matrix2d.cpp test/test_scilib.cpp)

	# Create executable
	add_executable(scilib_test
		${SOURCES}
	)

	# Add compiler options
	add_compile_options(-Wall -Wextra -Wpedantic -g)
	
	# Specify standard
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	configure_file(include/scilib.h include/scilib.h)

	# Includes
	target_include_directories(scilib_test PUBLIC include src)

	# Move scilib to ../release
	add_custom_command(TARGET scilib_test
		POST_BUILD
		COMMAND mv scilib_test ..
	)
endif(NOT test)