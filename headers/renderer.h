#ifndef RENDERER_H
#define RENDERER_H
#include <array>
#define COLS 64
#define ROWS 32

class Renderer {
private:
    std::array<std::array<int, COLS>, ROWS> display = {};
    int window_height = COLS;
    int window_width = ROWS;
    int rendering = false;
    int scale;

public:
    Renderer(int _scale);

    int render();
    int set_pixel(int x, int y);
    void stop_rendering();
};

#endif //RENDERER_H
