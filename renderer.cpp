#include <SDL3/SDL.h>
#include "headers/renderer.h"
#include <iostream>

Renderer::Renderer(const float _scale) {
    // Scale window height and width to _scale
    window_height = static_cast<int>(_scale) * ROWS;
    window_width = static_cast<int>(_scale) * COLS;
    scale = _scale;

    // Initialize a window and a renderer
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Unable to initialize SDL");
    }
    window = SDL_CreateWindow("CHIP-8 Emulator", window_width, window_height, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!window || !renderer) { // Handle SDL window or renderer creation failures
        std::cerr << "Window/renderer creation failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error(SDL_GetError());
    }

    // Adjust scale
    SDL_SetRenderScale(renderer, scale, scale);
    clear_display();
}

Renderer::~Renderer() {
    // Destroy renderer and window. Then quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::render_frame() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Draw every pixel under the display buffer
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (display[i][j] > 0) {
                const SDL_FRect rect { .x = static_cast<float>(i), .y = static_cast<float>(j), .w = 1, .h = 1 };
                SDL_RenderRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Renderer::clear_display() {
    // Reset the display buffer
    display = {};
    // Completely clear the display with a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int Renderer::set_pixel(const int x, const int y) {
    // Draw a white pixel in the given (x, y) coordinates
    const int _x = ((x % COLS) + COLS) % COLS;
    const int _y = ((y % ROWS) + ROWS) % ROWS;

    display[_x][_y] ^= 1; // Perform XOR on the particular coordinate of the display
    return !display[_x][_y]; // Return true if pixel was erased
}
