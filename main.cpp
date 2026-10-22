#include <iostream>
#include <bits/this_thread_sleep.h>
#include "headers/cpu.h"
#include "headers/input.h"
#include "headers/renderer.h"
#include "headers/audio.h"
#define RENDER_SCALE 20

int main(int argc, char *argv[]) {
    // Create required objects:
    auto renderer = Renderer(RENDER_SCALE);
    auto input = Input();
    auto speaker = Speaker();
    auto cpu = CPU(renderer, input, speaker);
    std::vector<uint8_t> rom;

    if (argc >= 2) {
        std::cout << "Loading ROM: " << argv[1] << std::endl; // Assuming this is the ROM
        rom = cpu.load_rom(argv[1]);
    }

    // Load sprites and ROM into CPU memory
    cpu.load_sprites_into_memory();
    cpu.load_program_into_memory(rom);

    // Main loop
    while (true) {
        cpu.update_timers();
        // Setting cycles to be faster by a few subticks
        for (int i = 0; i < CYCLE_SPEED; i++) {
            cpu.cycle(); // Execute a cycle in the CPU
        }
        input.handle_input(); // Handle input
        speaker.update(); // Update speaker
        renderer.render_frame(); // Render frame

        // Older implementation:
        // It resulted in less smoother performance compared to VSync
        // Delay before looping (1 / required FPS)
        // std::this_thread::sleep_for(delay);
    }

    return 0;
}
