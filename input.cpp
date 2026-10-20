#include "headers/input.h"
#include <map>
#include <array>
#include <iostream>
#include <stdexcept>
#include <optional>

Input::Input() {
}

void Input::handle_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                exit(0);
                break;
            case SDL_EVENT_KEY_DOWN:
                try {
                    const uint8_t mapped_code = KEYMAP.at(event.key.scancode);
                    keys_pressed[mapped_code] = true;
                } catch (std::out_of_range) {
                    // Ignore if not present in keymap
                }
                break;
            case SDL_EVENT_KEY_UP:
                try {
                    const uint8_t mapped_code = KEYMAP.at(event.key.scancode);
                    keys_pressed[mapped_code] = false;
                } catch (std::out_of_range) {
                    // Same as KEY_DOWN
                }
                break;
            default:
                break;
        }
    }
}

std::array<bool, KEYS> Input::get_key_pressed() {
    return keys_pressed;
}

bool Input::is_key_pressed(const uint8_t key_code) {
    return keys_pressed[key_code];
}

std::optional<uint8_t> Input::wait_for_key_press() {
    for (uint8_t i = 0; i < KEYS; i++) {
        if (keys_pressed[i]) {
            return i;
        }
    }

    return std::nullopt;
}