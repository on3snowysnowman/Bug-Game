cmake_minimum_required(VERSION 3.24)

project(Bug_Game_lib VERSION "0.1")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Fetch content of paths file.
file(READ "FrostPaths.txt" PATH_FILE_CONTENTS)

# Split the content by lines.
string(REGEX REPLACE "\r?\n" ";" PATH_FILE_LINES "${PATH_FILE_CONTENTS}")

# Fetch specific paths.
list(GET PATH_FILE_LINES 0 FROST_LIB_DIR)
list(GET PATH_FILE_LINES 1 FROST_INCLUDE_DIR)

if(NOT FROST_LIB_DIR OR NOT FROST_INCLUDE_DIR)
    message(FATAL_ERROR "FROST_LIB_DIR or FROST_INCLUDE_DIR is not set.")
endif()

message(STATUS "Frost Lib Directory: " ${FROST_LIB_DIR})
message(STATUS "Frost Include Directory: " ${FROST_INCLUDE_DIR})

# Collect all .cpp files in the source directory and subdirectories (recursive).
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add a library that contains all the globbed src files.
add_library(Bug_Game_lib ${SOURCES})

# Find required dependencies.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(nlohmann_json REQUIRED)

# Specify include directories.
target_include_directories(Bug_Game_lib
PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/Menus
    ${CMAKE_SOURCE_DIR}/include/Sector
    ${CMAKE_SOURCE_DIR}/include/SectorStructures
    ${FROST_INCLUDE_DIR}/Frost
    ${FROST_INCLUDE_DIR}/Frost/UITools
    # ${FROST_INCLUDE_DIR}/nlohmann
    # ${FROST_INCLUDE_DIR}/UITools
)

# Link all depended libraries to the main library.
target_link_libraries(Bug_Game_lib
PUBLIC
    SDL2::SDL2
    SDL2_image
    SDL2_ttf
    ${FROST_LIB_DIR}
)

add_executable(Bug_Game main.cpp)
add_executable(test test.cpp)

# Link executable to the library, which includes the depended libraries in it.
target_link_libraries(Bug_Game
    Bug_Game_lib

)

target_link_libraries(test
    Bug_Game_lib

)

