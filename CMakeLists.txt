cmake_minimum_required(VERSION 3.20)
project(DAA_LAB)

set(CMAKE_CXX_STANDARD 20)

# 1. Find all .cpp files in the current directory
file(GLOB_RECURSE SOURCES "*.cpp")

# 2. Loop through each file
foreach(SOURCE_FILE ${SOURCES})
    # Get the filename without extension (e.g., "lab1_huffman")
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

    # 3. Create a separate executable for this file automatically
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
endforeach()