#include <SDL3/SDL.h>
#include "headers/renderer.h"
#include <iostream>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (display[i][j] > 0) {
                const SDL_FRect rect { .x = static_cast<float>(i), .y = static_cast<float>(j), .w = 1, .h = 1 };
                SDL_RenderRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Renderer::clear_display() {
    // Completely clear the display with a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int Renderer::set_pixel(const int x, const int y) {
    // Draw a white pixel in the given (x, y) coordinates
    int _x = x;
    int _y = y;
    // Wrap around coordinates if they are out of bounds
    if (_x > COLS) {
        _x -= COLS;
    } else if (_x < 0) {
        _x += COLS;
    }
    if (_y > ROWS) {
        _y -= ROWS;
    } else if (_y < 0) {
        _y += ROWS;
    }

    display[_x][_y] ^= 1; // Perform XOR on the particular coordinate of the display
    return !display[_x][_y]; // Return true if pixel was erased
}

std::array<std::array<int, ROWS>, COLS> Renderer::get_display_buffer() {
    // Return the display buffer
    return display;
}
