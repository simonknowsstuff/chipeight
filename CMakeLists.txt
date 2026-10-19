cmake_minimum_required(VERSION 4.3)
project(chipeight)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.16
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
        SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-3.4.6
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3_image)

add_executable(chipeight
        cpu.cpp
        main.cpp
        keyboard.cpp
        renderer.cpp
        headers/cpu.h
        headers/keyboard.h
        headers/renderer.h
)

target_link_libraries(chipeight PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)