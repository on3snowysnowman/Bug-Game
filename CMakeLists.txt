cmake_minimum_required(VERSION 3.24)

project(Astrobaut_proj VERSION "0.1")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Fetch content of paths file.
file(READ "FrostPaths.txt" PATH_FILE_CONTENTS)

# Split the content by lines.
string(REGEX REPLACE "\r?\n" ";" PATH_FILE_LINES "${PATH_FILE_CONTENTS}")

# Fetch specific paths.
list(GET PATH_FILE_LINES 0 FROST_LIB_DIR)
list(GET PATH_FILE_LINES 1 FROST_INCLUDE_DIR)

message(STATUS "Frost Lib Directory: " ${FROST_LIB_DIR})
message(STATUS "Frost Include Directory: " ${FROST_INCLUDE_DIR})

# Collect all .cpp files in the source directory and subdirectories (recursive).
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add a library that contains all the globbed src files.
add_library(Astrobaut_lib ${SOURCES})

# Find required dependencies.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(nlohmann_json REQUIRED)

# Specify include directories.
target_include_directories(Astrobaut_lib
PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${FROST_INCLUDE_DIR}
)

# Link all depended libraries to the executable.
target_link_libraries(Astrobaut_lib
    SDL2::SDL2
    SDL2_image
    SDL2_ttf
    ${FROST_LIB_DIR}
)

add_executable(Astrobaut main.cpp)

# Specify include directories.
target_include_directories(Astrobaut
PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${FROST_INCLUDE_DIR}
)

# Link all depended libraries to the executable.
target_link_libraries(Astrobaut
    SDL2::SDL2
    SDL2_image
    SDL2_ttf
    ${FROST_LIB_DIR}
    Astrobaut_lib
)

