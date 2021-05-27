#ifndef CHIP8_DEFS_H
#define CHIP8_DEFS_H

#include <stddef.h>
#include <cstdint>
#include <array>


namespace CHIP8_defs {

static constexpr size_t MEM_SIZE        = 4096;
static constexpr size_t REG_COUNT       = 16;
static constexpr size_t STACK_SIZE      = 12;
static constexpr size_t START_ADDRESS   = 0x200;
static constexpr size_t DISPLAY_WIDTH   = 64;
static constexpr size_t DISPLAY_HEIGHT  = 32;
static constexpr size_t FONTSET_START_ADDRESS = 0x50;
static constexpr size_t KEYBOARD_SIZE   = 16;
static constexpr size_t FONTSET_SIZE    = 80;

static constexpr uint8_t fontset[FONTSET_SIZE] =
{
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

using Display = std::array<uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT>;

//Keypad                   Keyboard
//+-+-+-+-+                +-+-+-+-+
//|1|2|3|C|                |1|2|3|4|
//+-+-+-+-+                +-+-+-+-+
//|4|5|6|D|                |Q|W|E|R|
//+-+-+-+-+       =>       +-+-+-+-+
//|7|8|9|E|                |A|S|D|F|
//+-+-+-+-+                +-+-+-+-+
//|A|0|B|F|                |Z|X|C|V|
//+-+-+-+-+                +-+-+-+-+

}

#endif // CHIP8_DEFS_H
