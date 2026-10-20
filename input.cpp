#include "headers/input.h"
#include <iostream>
#include <map>
#include <vector>

Input::Input() {

}

void Input::handle_input(SDL_Event &event) {
    switch (event.type) {
        case SDL_EVENT_QUIT:
            exit(0);
            break;
        case SDL_EVENT_KEY_DOWN:
            try {
                std::cout << KEYMAP.at(event.key.scancode) << std::endl;
            } catch (const std::out_of_range&) {
                // Ignore if not present in keymap
            }
            break;
        default:
            break;
    }
}

bool Input::is_key_pressed(const int key_code) {
    return keys_pressed[key_code];
}
