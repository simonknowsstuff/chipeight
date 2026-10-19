//
// Created by Simon on 19-10-2026.
//

#ifndef KEYBOARD
#define KEYBOARD
#include <vector>

class Keyboard {
public:
    std::vector<int> keys_pressed = {};

    bool is_key_pressed(int key_code);
};

#endif //KEYBOARD
