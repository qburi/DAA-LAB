cmake_minimum_required(VERSION 3.20)
project(DAA_LAB)

set(CMAKE_CXX_STANDARD 20)

# 1. Find all .cpp files
file(GLOB_RECURSE SOURCES "*.cpp")

# 2. Loop through each file
foreach(SOURCE_FILE ${SOURCES})
    # --- THE FIX ---
    # Ignore files inside the cmake build folders to prevent "CMakeCXXCompilerId" error
    if(SOURCE_FILE MATCHES "cmake-build-debug" OR SOURCE_FILE MATCHES "CMakeFiles")
        continue()
    endif()
    # ----------------

    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

    # Create executable
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
endforeach()