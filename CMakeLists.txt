cmake_minimum_required(VERSION 3.15)
project(HeapScheduler VERSION 1.0.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES 
    "src/heap/*.cpp"
    "src/scheduler/*.cpp"
)

# Main executable
add_executable(heap_scheduler 
    src/main.cpp
    ${SOURCES}
)

# Tests (optional - uncomment when you add tests)
# enable_testing()
# add_subdirectory(tests)

# Benchmarks (optional)
# add_subdirectory(benchmarks)

# Installation
install(TARGETS heap_scheduler DESTINATION bin)
