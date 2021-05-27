#ifndef __CHIP8_IMPL_H__
#define __CHIP8_IMPL_H__

#include <stddef.h>
#include <cstdint>
//#include <string>
#include <array>

#include "chip8_defs.h"


struct CHIP8_impl
{
    CHIP8_impl();
    bool displayUpdatePending() const;
    void clearDisplayUpdatePending();
    void display() const;

    void cycle();

    // Debug
    void printMem() const;
    void printReg() const;
    void executeOpcode(uint16_t opcode);

    void executeOpcode();

    void nibble_0();
    void nibble_1();
    void nibble_2();
    void nibble_3();
    void nibble_4();
    void nibble_5();
    void nibble_6();
    void nibble_7();
    void nibble_8();
    void nibble_9();
    void nibble_A();
    void nibble_B();
    void nibble_C();
    void nibble_D();
    void nibble_E();
    void nibble_F();


    using DisplayArr = std::array<uint8_t, CHIP8_defs::DISPLAY_WIDTH * CHIP8_defs::DISPLAY_HEIGHT>;

    // 0x000-0x1FF - reserved for CHIP8 interpreter (not used here)
    // 0x050-0x0A0 - 16 built-in character set
    // 0x200-0xFFF - ROM and space free to use
    std::array<uint8_t, CHIP8_defs::MEM_SIZE> mem_;
    // Regs are labeled V0 to VF
    // VF is used as a flag for results of operations
    std::array<uint8_t, CHIP8_defs::REG_COUNT> reg_;
    // Operation code
    uint16_t opcode_;
    // Index register for storing memory addresses
    uint16_t index_;
    // Program counter holds the address of next instruction in memory
    uint16_t pc_;
    // Stack holds the pc values to return to from subroutines
    std::array<uint32_t, CHIP8_defs::STACK_SIZE> stack_;
    // Stack pointer - current index of stack
    uint8_t sp_;

    DisplayArr display_;
    uint8_t delayTimer_;
    uint8_t soundTimer_;

    std::array<uint8_t, CHIP8_defs::KEYBOARD_SIZE> keys_;

    bool displayUpdatePending_;
};

#endif
