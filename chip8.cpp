#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "chip8.h"
#include "chip8_impl.h"


CHIP8::CHIP8()
    : impl_(std::make_unique<CHIP8_impl>())
{
}

CHIP8::~CHIP8() = default;

void CHIP8::display() const
{
    impl_->display();
}
void CHIP8::loadGame(const std::string& filePath)
{
    std::ifstream in;
    in.open(filePath, std::ios::in | std::ios::binary);

    if (!in.is_open()) {
        std::cout << "Error in open file" << std::endl;
        return;
    }

    in.read((char*)&impl_->mem_[CHIP8_defs::START_ADDRESS], CHIP8_defs::MEM_SIZE - CHIP8_defs::START_ADDRESS);
    in.close();
}

void CHIP8::cycle()
{
    impl_->cycle();
}

bool CHIP8::displayUpdatePending() const
{
    return impl_->displayUpdatePending();
}

void CHIP8::clearDisplayUpdatePending()
{
    impl_->clearDisplayUpdatePending();
}

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

void CHIP8::keyPressed(int i)
{
    std::cout << "Key pressed " << i << std::endl;
    impl_->keys_.at(i) = 1;
}
void CHIP8::keyReleased(int i)
{
    std::cout << "Key released " << i << std::endl;
    impl_->keys_.at(i) = 0;
}

size_t CHIP8::getHeight() const
{
 return CHIP8_defs::DISPLAY_HEIGHT;
}

size_t CHIP8::getWidth() const
{
 return CHIP8_defs::DISPLAY_WIDTH;
}

bool CHIP8::getPixelAt(size_t x, size_t y) const
{
    std::cout << "x=" << x << " y=" << y << std::endl;

    size_t index = y * CHIP8_defs::DISPLAY_WIDTH + x;
    return (impl_->display_.at(index) || true);
}
