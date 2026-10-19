#include <array>
#include <SDL3/SDL.h>
#include <iostream>
#define COLS 64
#define ROWS 32

class Renderer {
    std::array<std::array<int, COLS>, ROWS> display = {};

    Renderer(int scale) {
        const int WINDOW_HEIGHT = scale * ROWS;
        const int WINDOW_WIDTH = scale * COLS;
    }
};
