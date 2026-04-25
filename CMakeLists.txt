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
# 2. Unified Output Directories
# -----------------------------------------------------------------------------
# This ensures that on Windows, Mac, and Linux, all binaries (.dll, .so, .dylib, .exe)
# and link libraries (.lib) land in the same predictable folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# -----------------------------------------------------------------------------
# 3. Include Paths
# -----------------------------------------------------------------------------
include_directories(src/NativeEngine/include)

# -----------------------------------------------------------------------------
# 4. Native Engine (Shared Library for .NET Interop)
# -----------------------------------------------------------------------------
add_library(NanoURLNative SHARED
    src/NativeEngine/src/InMemoryLinkShortener.cpp
)

# -----------------------------------------------------------------------------
# 5. CLI Application (Local Testing)
# -----------------------------------------------------------------------------
add_executable(NanoURL_CLI src/NativeEngine/src/main.cpp)
target_link_libraries(NanoURL_CLI PRIVATE NanoURLNative)