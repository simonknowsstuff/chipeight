#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <random>
#include <stack>

class CPU {
private:
    uint8_t memory[4096] = {};
    uint8_t v[16] = {};
    uint16_t i = 0;
    std::stack<int> stack = {};
    uint16_t pc = 0x200;
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;

public:
    int speed = 10;
    bool paused = false;

    void cycle();
    void load_program_into_memory(std::vector<uint8_t>& program);
    void update_timers();
    void execute_instruction(uint16_t opcode);
};

#endif //CPU_H
