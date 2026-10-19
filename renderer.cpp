#include <array>
#include <SDL3/SDL.h>
#include <iostream>
#define COLS 64
#define ROWS 32

class Renderer {
    std::array<std::array<int, COLS>, ROWS> display = {};
    int window_height = COLS;
    int window_width = ROWS;

    Renderer(int scale) {
        window_height = scale * ROWS;
        window_width = scale * COLS;

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;

        }
    }

    void render() {

    }
};
