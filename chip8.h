#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <stddef.h>
#include <cstdint>
#include <string>
#include <array>
#include <memory>
#include "chip8_defs.h"
#include "iemulator.h"
#include <map>

struct CHIP8_impl;


class CHIP8 : public IEmulator
{
public:
    CHIP8();
    ~CHIP8();

    void display() const;

    bool displayUpdatePending() const;
    void clearDisplayUpdatePending();

    // IEmulator
    void cycle() override;

    // IEmulator : IDisplayable
    virtual size_t getHeight() const override;
    virtual size_t getWidth() const override;
    virtual bool getPixelAt(size_t x, size_t y) const override;

    // IEmulator : IHasKeyboard
    void keyPressed(char c) override;
    void keyReleased(char c) override;

    // IEmulator : IHasLoadableROM
    void loadROM(const std::string& filePath) override;

private:
    std::unique_ptr<CHIP8_impl> impl_;

    static std::map<char, int> keyLayout_;
};


#endif
