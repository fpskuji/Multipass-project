cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Multipass)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(inc)

# Add the executable
add_executable(Multipass
    src/multipass.cpp
    src/jsondownloader.cpp
    src/jsonparser.cpp
    src/ReleaseInfoAMD64.cpp
)

# Find and link RapidJSON
find_package(RapidJSON REQUIRED)
if (RapidJSON_FOUND)
    include_directories(${RapidJSON_INCLUDE_DIRS})
    target_link_libraries(Multipass ${RapidJSON_LIBRARIES})
else()
    message(FATAL_ERROR "RapidJSON not found!")
endif()

# Find and link libcurl
find_package(CURL REQUIRED)
target_include_directories(Multipass PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(Multipass ${CURL_LIBRARIES})


# OS-specific settings
if (WIN32)
    # Windows-specific settings
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    message(STATUS "Configuring for Windows")
elseif (CYGWIN)
    # Cygwin-specific settings
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    message(STATUS "Configuring for Cygwin")
elseif (APPLE)
    # macOS-specific settings
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(CMAKE_C_COMPILER oa64-clang)
        set(CMAKE_CXX_COMPILER oa64-clang++)
        message(STATUS "Configuring for Apple Silicon (arm64)")
    else()
        set(CMAKE_C_COMPILER o64-clang)
        set(CMAKE_CXX_COMPILER o64-clang++)
        message(STATUS "Configuring for Intel-based macOS (x86_64)")
    endif()
elseif (LINUX)
    # Linux-specific settings
    message(STATUS "Configuring for Linux")
endif()
