#include <array>
#include <cstdint>
#include <random>
#include <stack>

class CPU {
    uint8_t memory[4096] = {};  // 4 KB memory
    uint8_t v[16] = {};         // 16 8-bit registers
    uint16_t i = 0;             // 1 16-bit register
    std::stack<int> stack = {}; // Stack
    uint16_t pc = 0x200;        // Program counter
    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;
    int speed = 10;
    bool paused = false;

    void cycle() {
        for (int j = 0; j < speed; j++) {
            if (!paused) {
                const uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
                executeInstruction(opcode);
            }
        }
    }

    void loadProgramIntoMemory(const uint8_t program[]) {
        constexpr int programSize = sizeof(program) / sizeof(program[0]);
        for (int loc = 0; loc < programSize; loc++) {
            memory[0x200 + loc] = program[loc];
        }
    }

    // TODO: Implement loading ROM
    void loadRom() {

    }

    // TODO: Implement playing sound
    void playSound() {

    }

    void updateTimers() {
        if (delayTimer > 0)
            delayTimer--;

        if (soundTimer > 0)
            soundTimer--;
    }

    void loadSpritesIntoMemory() {
        const std::array sprites = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        for (int j = 0; j < sprites.size(); j++) {
            memory[j] = sprites[j];
        }
    }

    void executeInstruction(const uint16_t opcode) {
        if (!paused) {
            pc += 2;

            const uint8_t x = (opcode & 0x0F00) >> 8; // 0x5468 -> 0x04
            const uint8_t y = (opcode & 0x00F0) >> 4; // 0x5468 -> 0x006

            // Modern random number generator I thought would be nice to use instead of srand():
            std::random_device rd;
            std::mt19937 gen(rd());

            switch (opcode & 0xF000) {
                case 0x0000:
                    switch (opcode) {
                        case 0x00E0: // TODO: CLS
                            break;
                        case 0x00EE: // RET
                            pc = stack.top();
                            stack.pop();
                            break;
                        default:
                            break;
                    }
                    break;
                case 0x1000: // JP addr
                    pc = opcode & 0x0FFF;
                    break;
                case 0x2000: // CALL addr
                    stack.push(pc);
                    pc = opcode & 0x0FFF;
                    break;
                case 0x3000: // SE Vx, byte
                    if (v[x] == (opcode & 0x00FF))
                        pc += 2;
                    break;
                case 0x4000: // SNE Vx, byte
                    if (v[x] != (opcode & 0x00FF))
                        pc += 2;
                    break;
                case 0x5000: // SE Vx, Vy
                    if (v[x] == v[y])
                        pc += 2;
                    break;
                case 0x6000: // LD Vx, byte
                    v[x] = opcode & 0x00FF;
                    break;
                case 0x7000: // ADD Vx, byte
                    v[x] += opcode & 0x00FF;
                    break;
                case 0x800:
                    switch (opcode & 0xF) {
                        case 0x0: // LD Vx, Vy
                            v[x] = v[y];
                            break;
                        case 0x1: // OR Vx, Vy
                            v[x] |= v[y];
                            break;
                        case 0x2: // AND Vx, Vy
                            v[x] &= v[y];
                            break;
                        case 0x3: // XOR Vx, Vy
                            v[x] ^= v[y];
                            break;
                        case 0x4: // ADD Vx, Vy
                            v[0xF] = 0;
                            if (v[x] + v[y] > 0xFF)
                                v[0xF] = 1;
                            v[x] += v[y];
                            break;
                        case 0x5: // SUB Vx, Vy
                            v[0xF] = 0;
                            if (v[x] > v[y])
                                v[0xF] = 1;
                            v[x] -= v[y];
                            break;
                        case 0x6: // SHR Vx {, Vy}
                            v[0xF] = v[x] & 0x1;
                            v[x] >>= 1;
                            break;
                        case 0x7: // SUBN Vx, Vy
                            v[0xF] = 0;
                            if (v[y] > v[x])
                                v[0xF] = 1;
                            v[x] = v[y] - v[x];
                            break;
                        case 0xE: // SHL Vx {, Vy}
                            v[0xF] = v[x] & 0x80;
                            v[x] <<= 1;
                            break;
                        default:
                            break;
                    }
                    break;
                case 0x9000: // SNE Vx, Vy
                    if (v[x] != v[y])
                        pc += 2;
                    break;
                case 0xA000: // LD I, addr
                    i = opcode & 0xFFF;
                    break;
                case 0xB000: // JP V0, addr
                    pc = (opcode & 0xFFF) + pc;
                    break;
                case 0xC000: // RND Vx, byte
                    v[x] = (gen() * 0xFF) & (opcode & 0xFF);
                    break;
                case 0xD000: // TODO: DRW Vx, Vy, nibble
                    break;
                case 0xE000:
                    switch (opcode & 0xFF) {
                        case 0x9e: // TODO: SKP Vx
                            break;
                        case 0xA1: // TODO: SKNP Vx
                            break;
                        default:
                            break;
                    }
                    break;
                case 0xF000:
                    switch (opcode & 0xFF) {
                        case 0x07: // LD Vx, DT
                            v[x] = delayTimer;
                            break;
                        case 0x0A: // TODO: LD Vx, K
                            break;
                        case 0x15: // LD DT, Vx
                            delayTimer = v[x];
                            break;
                        case 0x18: // LD ST, Vx
                            soundTimer = v[x];
                            break;
                        case 0x1E: // ADD I, Vx
                            i += v[x];
                            break;
                        case 0x29: // TODO: LD F, Vx
                            break;
                        case 0x33: // LD B, Vx
                            memory[i] = v[x] / 100;
                            memory[i + 1] = v[x] % 100 / 10;
                            memory[i + 2] = v[x] % 10;
                            break;
                        case 0x55: // LD [I], Vx
                            for (int r = 0; r <= x; r++) {
                                memory[i + r] = v[r];
                            }
                            break;
                        case 0x65: // LD Vx, [I]
                            for (int r = 0; r <= x; r++) {
                                v[r] = memory[i + r];
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }
};
