cmake_minimum_required(VERSION 3.20)

project(console_miner_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/dest
)

file(GLOB sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(console_miner
    ${sources}
)

find_package(Curses REQUIRED)

target_include_directories(console_miner PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/extern
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(console_miner PRIVATE
    ${CURSES_LIBRARIES}
)