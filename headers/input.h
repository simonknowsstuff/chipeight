#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <map>
#include <vector>
#include "SDL3/SDL_events.h"

class Input {
public:
    std::vector<int> keys_pressed = {};
    const std::map<int, int> KEYMAP = {
        {SDL_SCANCODE_1, 0x1},
        {SDL_SCANCODE_2, 0x2},
        {SDL_SCANCODE_3, 0x3},
        {SDL_SCANCODE_4, 0xc},
        {SDL_SCANCODE_Q, 0x4},
        {SDL_SCANCODE_W, 0x5},
        {SDL_SCANCODE_E, 0x6},
        {SDL_SCANCODE_R, 0xD},
        {SDL_SCANCODE_A, 0x7},
        {SDL_SCANCODE_S, 0x8},
        {SDL_SCANCODE_D, 0x9},
        {SDL_SCANCODE_F, 0xE},
        {SDL_SCANCODE_Z, 0xA},
        {SDL_SCANCODE_X, 0x0},
        {SDL_SCANCODE_C, 0xB},
        {SDL_SCANCODE_V, 0xF},
    };

    Input();
    void handle_input(SDL_Event &event);
    bool is_key_pressed(int key_code);
};

#endif //KEYBOARD_H
