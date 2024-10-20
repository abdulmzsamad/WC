cmake_minimum_required(VERSION 3.10)

# Project name and version
project(WC VERSION 1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Include directories for headers
include_directories(include)

# Source files (you can add more .cpp files to this list)
set(SOURCES
    src/WC.cpp
    main.cpp
)

# Add executable
add_executable(WC ${SOURCES} )
