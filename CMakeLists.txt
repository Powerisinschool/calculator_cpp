cmake_minimum_required(VERSION 3.15)
project(Calculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Treat warnings as errors during development (good discipline)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Werror)
endif()

# Add src and tests directory
add_subdirectory(src)
add_subdirectory(tests)
