cmake_minimum_required(VERSION 3.16)

########################################
# 平台检查 - 仅支持 Ubuntu/Linux
########################################
if(WIN32)
    message(FATAL_ERROR 
        "此项目仅支持在 Ubuntu/Linux 环境下构建。\n"
        "Windows 用户请考虑使用 WSL (Windows Subsystem for Linux)。\n"
        "安装 WSL: https://learn.microsoft.com/zh-cn/windows/wsl/install"
    )
endif()

if(NOT UNIX)
    message(WARNING 
        "此项目主要针对 Ubuntu/Linux 环境开发和测试。\n"
        "其他 Unix 系统可能可以工作，但未经过充分测试。"
    )
endif()

########################################
# 项目设置
########################################
project(LeetCode
    VERSION 1.0.0
    DESCRIPTION "LeetCode algorithm practice in C++"
    LANGUAGES CXX
)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

########################################
# 模块和通用路径设置
########################################
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(COMMON_SOURCE ${PROJECT_SOURCE_DIR}/src)
set(COMMON_TEST ${PROJECT_SOURCE_DIR}/test)

########################################
# C++ 标准和编译选项
########################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 编译器选项（使用生成器表达式，支持多配置生成器）
add_compile_options(
    "$<$<CONFIG:Debug>:-g3;-gdwarf-2;-O0;-pipe>"
    "$<$<CONFIG:Release>:-g0;-Ofast;-march=native;-mtune=native;-DNDEBUG>"
)

########################################
# 优先使用 Ninja 生成器（如果可用）
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
# 检查 ccache 是否可用
########################################
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Ccache found: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(STATUS "Ccache not found, using default compiler")
endif()

########################################
# Google Test 配置
########################################
set(CTEST_OUTPUT_ON_FAILURE TRUE)
enable_testing()

# 使用 FetchContent 下载 GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

########################################
# LeetCode 库
########################################
file(GLOB_RECURSE leetcode_SRC_FILES CONFIGURE_DEPENDS ${COMMON_SOURCE}/leetcode/*.cpp)
add_library(leetcode STATIC ${leetcode_SRC_FILES})

# 设置包含目录（使用 target_include_directories 替代全局 include_directories）
target_include_directories(leetcode
    PUBLIC
        ${COMMON_INCLUDES}
)

# 预编译头文件以减少编译时间
target_precompile_headers(leetcode PUBLIC ${COMMON_INCLUDES}/leetcode/core.h)

########################################
# Problem Set 集成测试
########################################
file(GLOB_RECURSE leetcode_TEST_FILES CONFIGURE_DEPENDS ${COMMON_TEST}/leetcode/*.cpp)
add_executable(problem_set_tests ${leetcode_TEST_FILES})

# 链接库（使用 PRIVATE，因为测试不需要暴露依赖）
target_link_libraries(problem_set_tests
    PRIVATE
        leetcode
        GTest::gtest
        GTest::gtest_main
)

# 可以使用 `ctest` 运行所有集成测试
add_test(NAME problem_set_tests COMMAND problem_set_tests)

########################################
# 生成 compile_commands.json 用于 IntelliSense
########################################
# CMAKE_EXPORT_COMPILE_COMMANDS 会生成 compile_commands.json 以提供更好的 IntelliSense 支持
# 这适用于 Ninja 和 Unix Makefiles 生成器