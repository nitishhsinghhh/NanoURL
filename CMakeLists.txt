cmake_minimum_required(VERSION 3.14)
project(NanoURL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# 1. Hardware-Aware Optimizations (Apple M2)
# -----------------------------------------------------------------------------
if(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    add_compile_options(-O3 -mcpu=apple-m2 -arch arm64)
    message(STATUS "M2 Performance Core Optimizations Enabled")
endif()

# -----------------------------------------------------------------------------
# 2. Include Paths
# -----------------------------------------------------------------------------
include_directories(src/NativeEngine/include)

# -----------------------------------------------------------------------------
# 3. Native Engine (Shared Library for .NET Interop)
# -----------------------------------------------------------------------------
# Creates libNanoURLNative.dylib
add_library(NanoURLNative SHARED
    src/NativeEngine/src/InMemoryLinkShortener.cpp
)

# -----------------------------------------------------------------------------
# 4. CLI Application (Local Testing)
# -----------------------------------------------------------------------------
# Creates the NanoURL_CLI executable
add_executable(NanoURL_CLI src/NativeEngine/src/main.cpp)
target_link_libraries(NanoURL_CLI PRIVATE NanoURLNative)

# -----------------------------------------------------------------------------
# 5. Output Configuration
# -----------------------------------------------------------------------------
# Ensures binaries go to a 'bin' folder in your build directory for easy access
set_target_properties(NanoURL_CLI PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(NanoURLNative PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")