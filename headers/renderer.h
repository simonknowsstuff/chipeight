#ifndef RENDERER_H
#define RENDERER_H
#include <array>
#include <SDL3/SDL.h>
#define COLS 64
#define ROWS 32

class Renderer {
private:
    std::array<std::array<int, ROWS>, COLS> display = {}; // Display buffer
    int window_height = COLS; // Window height
    int window_width = ROWS; // Window width
    float scale; // Scale value
    // Initialize required SDL variables
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

public:
    Renderer(float _scale);

    ~Renderer();

    void clear_display();

    void render_frame();

    int set_pixel(const int x, const int y);
};

#endif //RENDERER_H
