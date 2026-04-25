cmake_minimum_required(VERSION 3.14)
project(NanoURL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# 1. Global Output Overrides (Standardizes the .exe path)
# -----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ensure no config subfolders on Windows (keeps it in /bin)
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/bin)
endforeach()

# -----------------------------------------------------------------------------
# 2. Hardware-Aware Optimizations (Apple M2)
# -----------------------------------------------------------------------------
if(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    add_compile_options(-O3 -mcpu=apple-m2 -arch arm64)
    message(STATUS "M2 Performance Core Optimizations Enabled")
endif()

# -----------------------------------------------------------------------------
# 3. Targets (Static Approach)
# -----------------------------------------------------------------------------
include_directories(src/NativeEngine/include)

# We define the engine as a STATIC library (compiled into the EXE)
add_library(NanoURLStatic STATIC
    src/NativeEngine/src/InMemoryLinkShortener.cpp
)

# The final standalone CLI app
add_executable(NanoURL_CLI src/NativeEngine/src/main.cpp)
target_link_libraries(NanoURL_CLI PRIVATE NanoURLStatic)