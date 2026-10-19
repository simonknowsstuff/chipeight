#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <random>
#include <stack>

class CPU {
public:
    int speed = 10;
    bool paused = false;

    void cycle();
    void load_program_into_memory(const std::vector<uint8_t>& program);
    void update_timers();
    void execute_instruction(uint16_t opcode);
};

#endif //CPU_H
