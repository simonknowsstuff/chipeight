cmake_minimum_required(VERSION 4.3)
project(chipeight)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(chipeight
        cpu.cpp
        main.cpp
        keyboard.cpp
        renderer.cpp
        headers/cpu.h
        headers/keyboard.h
        headers/renderer.h
)

target_link_libraries(chipeight PRIVATE SDL3::SDL3)
