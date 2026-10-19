//
// Created by Simon on 19-10-2026.
//

#ifndef KEYBOARD
#define KEYBOARD
#include <vector>

class Keyboard {
public:
    std::vector<int> keysPressed = {};

    bool isKeyPressed(int keyCode);
};

#endif //KEYBOARD
