#include <SDL3/SDL.h>
#include "headers/renderer.h"
#include <iostream>

Renderer::Renderer(const float _scale) {
    // Scale window height and width to _scale
    window_height = static_cast<int>(_scale) * ROWS;
    window_width = static_cast<int>(_scale) * COLS;
    scale = _scale;

    // Initialize SDL video and audio (for speaker)
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Unable to initialize SDL");
    }

    // Create SDL window and renderer
    if (!SDL_CreateWindowAndRenderer(
            "CHIP-8 Emulator",
            window_width,
            window_height,
            0, // The window shouldn't be resizable
            &window,
            &renderer)
    ) { // Handle errors
        std::cerr << "Window/renderer creation failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error(SDL_GetError());
    }

    // Set metadata
    SDL_SetAppMetadata("chipeight emulator", "1.0.0", "com.knowsstuff.chipeight");

    // Wait for VSync
    SDL_SetRenderVSync(renderer, 1);

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
                const SDL_FRect rect{
                    // All parameters have to be floats:
                    .x = static_cast<float>(i),
                    .y = static_cast<float>(j),
                    .w = 1.0f,
                    .h = 1.0f
                };
                SDL_RenderRect(renderer, &rect);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer); // Finally, render it on the renderer
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
    // Draw a white pixel in the given (x, y) coordinates with wrapping
    const int _x = (x % COLS + COLS) % COLS;
    const int _y = (y % ROWS + ROWS) % ROWS;

    display[_x][_y] ^= 1; // Perform XOR on the particular coordinate of the display
    return !display[_x][_y]; // Return true if pixel was erased
}
