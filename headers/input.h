#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <map>
#include <array>
#include "SDL3/SDL_events.h"
#include <optional>
#define KEYS 16

class Input {
private:
    std::array<bool, KEYS> keys_pressed = {false};

public:
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

    void handle_input();

    std::array<bool, KEYS> get_key_pressed();

    bool is_key_pressed(const uint8_t key_code);

    std::optional<uint8_t> wait_for_key_press();
};

#endif //KEYBOARD_H
