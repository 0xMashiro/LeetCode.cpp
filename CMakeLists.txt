cmake_minimum_required(VERSION 3.16)

########################################
# Platform Check - Ubuntu/Linux only
########################################
if(WIN32)
    message(FATAL_ERROR 
        "This project only supports Ubuntu/Linux environment.\n"
        "Windows users please use WSL (Windows Subsystem for Linux).\n"
        "Install WSL: https://learn.microsoft.com/en-us/windows/wsl/install"
    )
endif()

if(NOT UNIX)
    message(WARNING 
        "This project is primarily developed and tested on Ubuntu/Linux.\n"
        "Other Unix systems may work but are not fully tested."
    )
endif()

########################################
# Project Settings
########################################
project(LeetCode
    VERSION 1.0.0
    DESCRIPTION "LeetCode algorithm practice in C++"
    LANGUAGES CXX
)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

########################################
# Module and Common Paths
########################################
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(COMMON_SOURCE ${PROJECT_SOURCE_DIR}/src)
set(COMMON_TEST ${PROJECT_SOURCE_DIR}/test)

########################################
# C++ Standard and Compile Options
########################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler options (using generator expressions for multi-config generators)
add_compile_options(
    "$<$<CONFIG:Debug>:-g3;-gdwarf-2;-O0;-pipe>"
    "$<$<CONFIG:Release>:-g0;-Ofast;-march=native;-mtune=native;-DNDEBUG>"
)

########################################
# Prefer Ninja Generator (if available)
########################################
find_program(NINJA_EXECUTABLE ninja)

if(NINJA_EXECUTABLE)
    message(STATUS "Ninja found at: ${NINJA_EXECUTABLE}")
    set(CMAKE_GENERATOR "Ninja")
else()
    message(STATUS "Ninja is not available in PATH.")
    message(STATUS "To use Ninja, install it: sudo apt install ninja-build")
endif()

########################################
# Check if ccache is available
########################################
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Ccache found: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(STATUS "Ccache not found, using default compiler")
endif()

########################################
# Google Test Configuration
########################################
set(CTEST_OUTPUT_ON_FAILURE TRUE)
enable_testing()

# Download GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

########################################
# Options: Single/Multi Problem Mode
########################################
option(LEETCODE_SINGLE_PROBLEM "Compile single problem (slug, e.g., 'two-sum')" "")
set(LEETCODE_MULTI_PROBLEMS "" CACHE STRING "Compile multiple problems (semicolon-separated slugs, e.g., 'two-sum;lru-cache')")

########################################
# LeetCode Library
########################################
# Utility files (required for all modes)
file(GLOB leetcode_UTILS_FILES CONFIGURE_DEPENDS ${COMMON_SOURCE}/leetcode/utils/*.cpp)

if(LEETCODE_SINGLE_PROBLEM)
    # Single problem mode (convert to list for unified processing)
    set(LEETCODE_MULTI_PROBLEMS ${LEETCODE_SINGLE_PROBLEM})
endif()

if(LEETCODE_MULTI_PROBLEMS)
    # Multi-problem compilation mode
    set(leetcode_SRC_FILES ${leetcode_UTILS_FILES})
    set(leetcode_TEST_FILES "")
    
    foreach(PROBLEM_SLUG ${LEETCODE_MULTI_PROBLEMS})
        set(PROBLEM_HDR ${COMMON_INCLUDES}/leetcode/problems/${PROBLEM_SLUG}.h)
        set(PROBLEM_SRC ${COMMON_SOURCE}/leetcode/problems/${PROBLEM_SLUG}.cpp)
        set(PROBLEM_TEST ${COMMON_TEST}/leetcode/problems/${PROBLEM_SLUG}.cpp)
        
        if(NOT EXISTS ${PROBLEM_HDR})
            message(FATAL_ERROR "Problem header not found: ${PROBLEM_HDR}")
        endif()
        
        if(NOT EXISTS ${PROBLEM_SRC})
            message(FATAL_ERROR "Problem source not found: ${PROBLEM_SRC}")
        endif()
        
        if(NOT EXISTS ${PROBLEM_TEST})
            message(FATAL_ERROR "Problem test not found: ${PROBLEM_TEST}")
        endif()
        
        list(APPEND leetcode_SRC_FILES ${PROBLEM_SRC} ${PROBLEM_HDR})
        list(APPEND leetcode_TEST_FILES ${PROBLEM_TEST})
        
        message(STATUS "Compiling problem: ${PROBLEM_SLUG}")
    endforeach()
    
    # Multi-problem mode uses a different executable name
    set(MULTI_TEST_TARGET "multi_problem_test")
    message(STATUS "Multi-problem mode: ${LEETCODE_MULTI_PROBLEMS}")
else()
    # Full build mode
    file(GLOB_RECURSE leetcode_SRC_FILES CONFIGURE_DEPENDS ${COMMON_SOURCE}/leetcode/*.cpp)
    file(GLOB_RECURSE leetcode_TEST_FILES CONFIGURE_DEPENDS ${COMMON_TEST}/leetcode/*.cpp)
    set(MULTI_TEST_TARGET "")
endif()

add_library(leetcode STATIC ${leetcode_SRC_FILES})

# Set include directories (using target_include_directories instead of global)
target_include_directories(leetcode
    PUBLIC
        ${COMMON_INCLUDES}
)

# Precompiled headers to reduce compile time (full build only)
if(NOT LEETCODE_MULTI_PROBLEMS)
    target_precompile_headers(leetcode PUBLIC ${COMMON_INCLUDES}/leetcode/core.h)
endif()

########################################
# Problem Set Integration Tests
########################################
if(LEETCODE_MULTI_PROBLEMS)
    # Multi-problem test executable (single problem is a special case)
    add_executable(${MULTI_TEST_TARGET} ${leetcode_TEST_FILES})
    target_link_libraries(${MULTI_TEST_TARGET}
        PRIVATE
            leetcode
            GTest::gtest
            GTest::gtest_main
    )
    add_test(NAME ${MULTI_TEST_TARGET} COMMAND ${MULTI_TEST_TARGET})
else()
    # Full test executable
    add_executable(problem_set_tests ${leetcode_TEST_FILES})
    target_link_libraries(problem_set_tests
        PRIVATE
            leetcode
            GTest::gtest
            GTest::gtest_main
    )
    add_test(NAME problem_set_tests COMMAND problem_set_tests)
endif()

########################################
# Generate compile_commands.json for IntelliSense
########################################
# CMAKE_EXPORT_COMPILE_COMMANDS generates compile_commands.json for better IntelliSense support
# This works with Ninja and Unix Makefiles generators
