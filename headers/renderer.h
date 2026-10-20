#ifndef RENDERER_H
#define RENDERER_H
#include <array>
#define COLS 64
#define ROWS 32

class Renderer {
private:
    std::array<std::array<int, ROWS>, COLS> display = {};   // Display buffer
    int window_height = COLS;                               // Window height
    int window_width = ROWS;                                // Window width
    float scale;                                            // Scale value

public:
    Renderer(float _scale);
    ~Renderer();

    void clear_display();
    void render_frame();
    int set_pixel(const int x, const int y);
    std::array<std::array<int, ROWS>, COLS> get_display_buffer();
};

#endif //RENDERER_H
