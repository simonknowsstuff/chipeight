#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <map>
#include <array>
#include "SDL3/SDL_events.h"
#define KEYS 16

class Input {
public:
    std::array<bool, KEYS> keys_pressed = {false};
    const std::map<int, uint8_t> KEYMAP = {
        {SDL_SCANCODE_X, 0x0},
        {SDL_SCANCODE_1, 0x1},
        {SDL_SCANCODE_2, 0x2},
        {SDL_SCANCODE_3, 0x3},
        {SDL_SCANCODE_Q, 0x4},
        {SDL_SCANCODE_W, 0x5},
        {SDL_SCANCODE_E, 0x6},
        {SDL_SCANCODE_A, 0x7},
        {SDL_SCANCODE_S, 0x8},
        {SDL_SCANCODE_D, 0x9},
        {SDL_SCANCODE_Z, 0xA},
        {SDL_SCANCODE_C, 0xB},
        {SDL_SCANCODE_4, 0xC},
        {SDL_SCANCODE_R, 0xD},
        {SDL_SCANCODE_F, 0xE},
        {SDL_SCANCODE_V, 0xF},
    };

    Input();

    void handle_input(SDL_Event &event);

    bool is_key_pressed(const uint8_t key_code);

    uint8_t get_key_pressed();
};

#endif //KEYBOARD_H
