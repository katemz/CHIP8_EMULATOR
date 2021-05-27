#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <stddef.h>
#include <cstdint>
#include <string>
#include <array>
#include <memory>
#include "chip8_defs.h"
#include "ipixelarraydisplay.h"

struct CHIP8_impl;


class CHIP8 : public IPixelArrayDisplay
{
public:
    CHIP8();
    ~CHIP8();

    void display() const;
    void loadGame(const std::string& filePath);
    void cycle();

    bool displayUpdatePending() const;
    void clearDisplayUpdatePending();
    void keyPressed(int i);
    void keyReleased(int i);

    virtual size_t getHeight() const override;
    virtual size_t getWidth() const override;
    virtual bool getPixelAt(size_t x, size_t y) const override;

private:
    std::unique_ptr<CHIP8_impl> impl_;
};


#endif
