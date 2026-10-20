#ifndef CPU_H
#define CPU_H
#include <stack>
#include <vector>
#include "input.h"
#include "renderer.h"
#define SPRITE_WIDTH 8

class CPU {
private:
    std::array<uint8_t, 4096> memory = {}; // 4 KB memory
    std::array<uint8_t, 16> v = {}; // 16 8-bit registers
    uint16_t i = 0; // 1 16-bit register
    std::stack<int> stack = {}; // Stack
    uint16_t pc = 0x200; // Program counter
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    bool paused = false;
    bool waiting_for_press = false;
    uint8_t key_register = 0;
    Renderer &_renderer;
    Input &_input;

public:
    CPU(Renderer &renderer, Input &input);

    void cycle();

    void load_program_into_memory(const std::vector<uint8_t> &program);

    void load_sprites_into_memory();

    std::vector<uint8_t> load_rom(const char* filename);

    void play_sound();

    void update_timers();

    void set_paused(bool value);

    void execute_instruction(const uint16_t opcode);
};

#endif //CPU_H
