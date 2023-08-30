# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Enable exporting of compile commands for external tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the project name and the programming language
project(pepita LANGUAGES C)

# Enable colorized output during build
set(CMAKE_COLOR_MAKEFILE ON)

# Set the C compiler and its flags
set(CMAKE_C_COMPILER clang)
add_compile_options(
    -Wall         # Enable all common warnings
    -Wextra       # Enable additional warnings
    -Wpedantic    # Enable strict ISO C and ISO C++ standards conformance
    -Wconversion  # Enable warnings for implicit type conversions
    -Wformat      # Enable warnings for format string vulnerabilities
)

# Debug build type-specific compile options
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(
        -g            # Enable debug information
        -fsanitize=address        # Enable address sanitizer for runtime memory checking
        -fsanitize=undefined      # Enable undefined behavior sanitizer for runtime checks
        -fprofile-instr-generate  # Enable generation of instrumentation for profiling
        -fcoverage-mapping        # Enable coverage mapping for code coverage analysis
    )

    # Debug build type-specific linker flags
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
        -fsanitize=address \
        -fsanitize=undefined \
        -fprofile-instr-generate \
        -fcoverage-mapping")
endif()

# Release build type-specific compile options
if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(
        -O3           # Optimization level 3
        -DNDEBUG      # Disable debug information and assertions
    )
endif()

# Add the source files
file(GLOB SRC_FILES src/*.c)

# Generate the pepita library
add_library(pepita_lib ${SRC_FILES})
target_include_directories(pepita_lib PRIVATE include)

# Create the executable target
add_executable(pepita src/main.c)
target_link_libraries(pepita PRIVATE pepita_lib)
target_include_directories(pepita PRIVATE include)

# Enable testing functionality
enable_testing()

# Specify the desired number of parallel jobs
set(CTEST_PARALLEL_LEVEL 4)

# Gather all test source files
file(GLOB TEST_FILES test/*.c)

# Create the test executable
add_executable(tests ${TEST_FILES})
target_link_libraries(tests PRIVATE pepita_lib)
target_include_directories(tests PRIVATE include)

# Add the test as a target
add_test(NAME pepita_tests COMMAND tests)

# Add a custom target for running the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add a custom target for generating code coverage reports
add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -j ${CTEST_PARALLEL_LEVEL}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/default.profraw ${CMAKE_BINARY_DIR}/coverage.profraw
    COMMAND xcrun llvm-profdata merge -sparse ${CMAKE_BINARY_DIR}/coverage.profraw -o ${CMAKE_BINARY_DIR}/coverage.profdata
    COMMAND xcrun llvm-cov report ${CMAKE_BINARY_DIR}/tests -instr-profile=${CMAKE_BINARY_DIR}/coverage.profdata
    COMMAND xcrun llvm-cov show --use-color -format=html -output-dir=${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/tests
            -instr-profile=${CMAKE_BINARY_DIR}/coverage.profdata --ignore-filename-regex="test|debug"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
