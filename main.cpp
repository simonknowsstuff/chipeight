#include "headers/cpu.h"
#include "headers/input.h"
#include "headers/renderer.h"

int main() {
    Renderer renderer = Renderer(20);
    Input input = Input();
    CPU cpu = CPU(renderer, input);

    // Main loop
    while (true) {
        cpu.cycle();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Let input handle all events
            input.handle_input(event);
        }
        renderer.render_frame();
    }

    return 0;
}