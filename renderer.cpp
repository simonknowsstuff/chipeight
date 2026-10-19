#include <SDL3/SDL.h>
#include "headers/renderer.h"
#include <iostream>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

Renderer::Renderer(const int _scale) {
    window_height = _scale * ROWS;
    window_width = _scale * COLS;
    scale = _scale;

    // Initialise a window and a renderer
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Unable to initialize SDL");
    }

    window = SDL_CreateWindow("CHIP-8 Emulator", window_width, window_height, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
}

int Renderer::render() {
    if (!window || !renderer) {
        std::cerr << "Window/renderer creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    rendering = true; // Local variable to ensure rendering stops only when quit properly

    // Start the rendering loop:
    while (rendering) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                rendering = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int Renderer::set_pixel(int x, int y) {
    SDL_FRect rect;
    rect.w = rect.h = scale;
    return 0;
}

void Renderer::stop_rendering() {
    rendering = false;
}
