#include "headers/cpu.h"
#include <array>
#include <cstdint>
#include <random>
#include <stack>
#include <iterator>

CPU::CPU(Renderer &renderer, Input &input): _renderer(renderer), _input(input) {
    // Assign the private renderer to the renderer passed in the constructor
    _renderer = renderer;
}

void CPU::cycle() {
    for (int j = 0; j < speed; j++) {
        if (paused) { return; }
        // Read 16 bits of instruction by shifting the first 8 bit instruction
        // and then load the next instruction using OR on it
        const uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
        execute_instruction(opcode); // Execute opcode obtained
    }
}

void CPU::load_program_into_memory(const std::vector<uint8_t> &program) {
    // I've considered the program to be loaded as a big vector for now
    // Read every line in the program and load it into memory
    const size_t program_size = program.size();
    for (int loc = 0; loc < program_size; loc++) {
        memory[0x200 + loc] = program[loc];
    }
}

// TODO: Implement loading ROM
void CPU::load_rom() {
}

// TODO: Implement playing sound
void CPU::play_sound() {
}

void CPU::update_timers() {
    if (delay_timer > 0) {
        delay_timer--;
    }

    if (sound_timer > 0) {
        sound_timer--;
    }
}

void CPU::load_sprites_into_memory() {
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

void CPU::execute_instruction(const uint16_t opcode) {
    pc += 2;

    const uint8_t x = (opcode & 0x0F00) >> 8; // 0x5468 -> 0x04
    const uint8_t y = (opcode & 0x00F0) >> 4; // 0x5468 -> 0x006
    const uint8_t addr = opcode & 0x0FFF;
    const uint8_t byte = opcode & 0x00FF;

    // DRW specific:
    const uint8_t height = opcode & 0xF;

    // Modern random number generator I thought would be nice to use instead of srand():
    std::random_device rd;
    std::mt19937 gen(rd());

    if (paused) { return; }

    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode) {
                case 0x00E0: // CLS
                    _renderer.clear_display();
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
            pc = addr;
            break;
        case 0x2000: // CALL addr
            stack.push(pc);
            pc = addr;
            break;
        case 0x3000: // SE Vx, byte
            if (v[x] == byte) {
                pc += 2;
            }
            break;
        case 0x4000: // SNE Vx, byte
            if (v[x] != byte) {
                pc += 2;
            }
            break;
        case 0x5000: // SE Vx, Vy
            if (v[x] == v[y]) {
                pc += 2;
            }
            break;
        case 0x6000: // LD Vx, byte
            v[x] = byte;
            break;
        case 0x7000: // ADD Vx, byte
            v[x] += byte;
            break;
        case 0x8000:
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
                    if (v[x] + v[y] > 0xFF) {
                        v[0xF] = 1;
                    }
                    v[x] += v[y];
                    break;
                case 0x5: // SUB Vx, Vy
                    v[0xF] = 0;
                    if (v[x] > v[y]) {
                        v[0xF] = 1;
                    }
                    v[x] -= v[y];
                    break;
                case 0x6: // SHR Vx {, Vy}
                    v[0xF] = v[x] & 0x1;
                    v[x] >>= 1;
                    break;
                case 0x7: // SUBN Vx, Vy
                    v[0xF] = 0;
                    if (v[y] > v[x]) {
                        v[0xF] = 1;
                    }
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
            if (v[x] != v[y]) {
                pc += 2;
            }
            break;
        case 0xA000: // LD I, addr
            i = addr;
            break;
        case 0xB000: // JP V0, addr
            pc = addr + pc;
            break;
        case 0xC000: // RND Vx, byte
            v[x] = gen() * 0xFF & byte;
            break;
        case 0xD000: // DRW Vx, Vy, nibble
            v[0xF] = 0; // Set VF to 0 initially
            for (int row = 0; row < height; row++) {
                uint8_t sprite = memory[i + row];

                // If sprite is not 0, erase the pixel
                for (int col = 0; col < SPRITE_WIDTH; col++) {
                    if ((sprite & 0x80) > 0) {
                        // Set VF to the value returned by set pixel
                        v[0xF] = _renderer.set_pixel(v[x] + col, v[y] + row);
                    }
                    sprite <<= 1;
                }
            }
            break;
        case 0xE000:
            switch (byte) {
                case 0x9e: // SKP Vx
                    if (_input.is_key_pressed(v[x])) {
                        pc += 2;
                    }
                    break;
                case 0xA1: // SKNP Vx
                    if (!_input.is_key_pressed(v[x])) {
                        pc += 2;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 0xF000:
            switch (opcode & 0xFF) {
                case 0x07: // LD Vx, DT
                    v[x] = delay_timer;
                    break;
                case 0x0A: // LD Vx, K
                    v[x] = _input.get_key_pressed();
                    break;
                case 0x15: // LD DT, Vx
                    delay_timer = v[x];
                    break;
                case 0x18: // LD ST, Vx
                    sound_timer = v[x];
                    break;
                case 0x1E: // ADD I, Vx
                    i += v[x];
                    break;
                case 0x29: // LD F, Vx
                    i = v[x] * 5;
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
