#include <iostream>
#include <bits/this_thread_sleep.h>
#include "headers/cpu.h"
#include "headers/input.h"
#include "headers/renderer.h"
#define RENDER_SCALE 20
#define FPS 700

int main() {
    const auto delay = std::chrono::milliseconds(1000 / FPS);

    // Create required objects:
    auto renderer = Renderer(RENDER_SCALE);
    auto input = Input();
    auto cpu = CPU(renderer, input);

    // Load sprites and ROM into CPU memory
    cpu.load_sprites_into_memory();

    const std::vector<uint8_t> rom = cpu.load_rom(R"(YOUR_ROM_HERE)");
    cpu.load_program_into_memory(rom);

    // Main loop
    while (true) {
        cpu.cycle(); // Execute a cycle in the CPU
        input.handle_input(); // Handle input for every frame

        std::this_thread::sleep_for(delay); // Delay before looping
    }

    return 0;
}
