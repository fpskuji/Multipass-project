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
