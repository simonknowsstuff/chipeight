#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>

class Keyboard {
public:
    std::vector<int> keys_pressed = {};

    Keyboard();
    bool is_key_pressed(int key_code);
};

#endif //KEYBOARD_H
