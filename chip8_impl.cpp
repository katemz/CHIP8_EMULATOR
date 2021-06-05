#include "chip8_impl.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

CHIP8_impl::CHIP8_impl()
    : opcode_(0),
      index_(0),
      pc_(CHIP8_defs::START_ADDRESS),
      sp_(0),
      delayTimer_(0),
      soundTimer_(0),
      displayUpdatePending_(false)
{
    mem_.fill(0);
    reg_.fill(0);
    stack_.fill(0);
    display_.fill(0);
    keys_.fill(0);
    memcpy((char*)&mem_[CHIP8_defs::FONTSET_START_ADDRESS], &CHIP8_defs::fontset, CHIP8_defs::FONTSET_SIZE);
    srand(time(NULL));

   // keys_[15] = 1;

}

bool CHIP8_impl::displayUpdatePending() const
{
    return displayUpdatePending_;
}

void CHIP8_impl::clearDisplayUpdatePending()
{
    displayUpdatePending_ = false;
}

void CHIP8_impl::display() const
{
    std::ios_base::sync_with_stdio(false);
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    //std::wcout << "DISPLAY:" << std::endl;
    for (int i = 0; i < CHIP8_defs::DISPLAY_HEIGHT; i++)
    {
        for (int j = 0; j < CHIP8_defs::DISPLAY_WIDTH; j++)
        {
            if (display_[CHIP8_defs::DISPLAY_WIDTH * i + j] == 1)
            {
                std::wcout << L"▆";
            }
            else
            {
                std::wcout << " ";
            }
        }
        std::wcout << std::endl;
    }
}

void CHIP8_impl::nibble_0()
{
    //std::cout << __func__ << std::endl;

    if (opcode_ == 0x0000) // OK
    {
        //std::cout << "No-op" << std::endl;
    }
    else if (opcode_ == 0x00E0) // OK
    {
        //std::cout << "Clear the screen" << std::endl;

        display_.fill(0);
        displayUpdatePending_ = true;
    }
    else if (opcode_ == 0x00EE)
    {
        //std::cout << "Return from subroutine. " << std::endl;

        sp_--;
        pc_ = stack_[sp_];
    }
    else
    {
       // std::cout << "Unknown opcode!";
    }
}

void CHIP8_impl::nibble_1()
{
   // std::cout << __func__ << std::endl;

    uint16_t location = (opcode_ & 0x0FFFu);
  //  std::cout << "Jump to location " << location << std::endl;
    pc_ = location;
}

void CHIP8_impl::nibble_2()
{
   // std::cout << __func__ << std::endl;
    uint16_t location = (opcode_ & 0x0FFFu);
   // std::cout << "Call subroutine " << location;
    stack_[sp_] = pc_;
    sp_++;
    pc_ = location;
}

void CHIP8_impl::nibble_3()
{
   // std::cout << __func__ << std::endl;
    //std::cout << "Skip next instruction if Vx = kk." << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t kk = (opcode_ & 0x00FFu);
    if (reg_.at(Vx) == kk)
    {
        pc_ += 2;
    }
}

 void CHIP8_impl::nibble_4()
 {
    // std::cout << __func__ << std::endl;
    // std::cout << "Skip next instruction if Vx != kk." << std::endl;
     uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
     uint8_t kk = (opcode_ & 0x00FFu);
     if (reg_.at(Vx) != kk)
     {
         pc_ += 2;
     }
 }

void CHIP8_impl::nibble_5()
{
   // std::cout << __func__ << std::endl;
    //std::cout << "Skip next instruction if Vx == Vy." << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode_ & 0x00F0u) >> 4u;
    if (reg_.at(Vx) == reg_.at(Vy))
    {
        pc_ += 2;
    }
}

void CHIP8_impl::nibble_6()
{
   // std::cout << __func__ << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t kk = (opcode_ & 0x00FFu);
    //std::cout << "Set reg[" << std::hex << (int)Vx << "] = " << (int)kk << std::endl;
    reg_[Vx] = kk;
}

void CHIP8_impl::nibble_7()
{
   // std::cout << __func__ << std::endl;
   // std::cout << "Add kk to Vx" << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t kk = (opcode_ & 0x00FFu);
    reg_[Vx] += kk;
}

void CHIP8_impl::nibble_8()
{
    //std::cout << __func__ << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode_ & 0x00F0u) >> 4u;
    uint8_t d =  (opcode_ & 0x000Fu);

    switch (d)
    {
    case 0x0000:
    {
        // Vx = Vy
        reg_[Vx] = reg_[Vy];
        break;
    }
    case 0x0001:
    {
        // Vx = Vx | Vy
        reg_[Vx] |= reg_[Vy];
        break;
    }
    case 0x0002:
    {
        // Vx = Vx AND Vy
        reg_[Vx] &= reg_[Vy];
        break;
    }
    case 0x0003:
    {
        // Vx = Vx XOR Vy
        reg_[Vx] ^= reg_[Vy];
        break;
    }
    case 0x0004:
    {
        // Add VY to VX. If result >FF, then VF=1.
        uint16_t sum = reg_[Vx] + reg_[Vy];
        if (sum > 0x00FF)
        {
            reg_[0x0F] = 1;
        }
        else
        {
            reg_[0x0F] = 0;
        }
        reg_[Vx] = static_cast<uint8_t>(sum & 0x00FF);
        break;
    }
    case 0x0005:
    {
        // VX=VX-VY Subtract VY. If VX<VY, then VF=0.
        if (reg_[Vx] > reg_[Vy])
        {
            reg_[0xF] = 1;
        }
        else
        {
            reg_[0xF] = 0;
        }
        reg_[Vx] -= reg_[Vy];
        break;
    }
    case 0x0006:
    {
        if (reg_[Vx] & 0x01u)
        {
            reg_[0xF] = 1;
        }
        else
        {
            reg_[0xF] = 0;
        }
        reg_[Vx] = (reg_[Vx] >> 1);
        break;
    }
    case 0x0007:
    {
        if (reg_[Vy] > reg_[Vx])
        {
            reg_[0xF] = 1;
        }
        else
        {
            reg_[0xF] = 0;
        }
        reg_[Vx] = reg_[Vy] - reg_[Vx];
        break;
    }
    case 0x000E:
    {
        if (reg_[Vx] & 0x80u)
        {
            reg_[0xF] = 1;
        }
        else
        {
            reg_[0xF] = 0;
        }
        reg_[Vx] = (reg_[Vx] << 1);
        break;
    }
    }
}

void CHIP8_impl::nibble_9()
{
   // std::cout << "Skip next instruction if Vx != Vy." << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode_ & 0x00F0u) >> 4u;
    if (reg_[Vx] != reg_[Vy])
    {
        pc_ += 2;
    }
}

void CHIP8_impl::nibble_A()
{
    uint16_t val = (opcode_ & 0x0FFFu);
    //std::cout << "The value of register I is set to:" << std::hex << val << std::endl;
    index_ = val;
}

void CHIP8_impl::nibble_B()
{
   // std::cout << "Jump to location nnn + V0." << std::endl;
    uint16_t val = (opcode_ & 0x0FFFu);
    pc_ = reg_[0x0] + val;
}

void CHIP8_impl::nibble_C()
{
   // std::cout << "Set Vx = random byte AND kk." << std::endl;
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t kk = (opcode_ & 0x00FFu);
    uint8_t random = rand() % 0xFF;

    reg_[Vx] = (random & kk);
}

void CHIP8_impl::nibble_D()
{
   // std::cout << " Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision." << std::endl;

    uint8_t x = (opcode_ & 0x0F00u) >> 8u;
    uint8_t y = (opcode_ & 0x00F0u) >> 4u;
    uint8_t height = (opcode_ & 0x000Fu); // height of displayed sprite

    uint8_t xPos = reg_[x] % CHIP8_defs::DISPLAY_WIDTH;
    uint8_t yPos = reg_[y] % CHIP8_defs::DISPLAY_WIDTH;

    reg_[0xF] = 0; // clear collision flag

    size_t displayIdx0 = yPos * CHIP8_defs::DISPLAY_WIDTH + xPos;
    bool collision = false;


    // FIXME ! I am not working!!!
    for (size_t i = 0; i < height; i++)
    {
       // std::cout << "Row: " << i << std::endl;
        uint8_t rowBitsAsByte = mem_[index_ + i];
     //   std::cout << "row bits as byte: " << std::hex << (int)rowBitsAsByte << std::endl;

        for (size_t j = 0; j < 8; j++)
        {
            size_t pixelId = 8 - j - 1;
            uint8_t pixelToSet = ((rowBitsAsByte & (0x01 << pixelId)) >> pixelId);
          //  std::cout << "Column: " << j << " pixel: " << (int)pixelToSet<< std::endl;
            uint8_t pixelOnScreen = display_[displayIdx0 + j + i * CHIP8_defs::DISPLAY_WIDTH];
            collision = collision || ((pixelToSet & 0x01) &  (pixelOnScreen & 0x01));
            display_[displayIdx0 + j + i * CHIP8_defs::DISPLAY_WIDTH] = pixelToSet ^ pixelOnScreen;
        }

        reg_[0xF] = collision;
    }

    displayUpdatePending_ = true;
}

void CHIP8_impl::nibble_E()
{
    if ((opcode_ & 0xF0FF) == 0xE09E)
    {
        uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
        uint8_t keyID = reg_[Vx];

        if (keys_[keyID] == 1)
        {
            pc_ += 2;
        }
    }
    else if ((opcode_ & 0xF0FF) == 0xE0A1)
    {
        uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
        uint8_t keyID = reg_[Vx];

        if (keys_[keyID] != 1)
        {
            pc_ += 2;
        }
    }
}

void CHIP8_impl::nibble_F()
{
    uint8_t Vx = (opcode_ & 0x0F00u) >> 8u;
    uint8_t dd =  (opcode_ & 0x00FFu);

    switch (dd)
    {
    case 0x0007:
    {
        reg_[Vx] = delayTimer_;
        break;
    }

    case 0x000A:
    {
        std::cout << "Wait for key press..." << std::endl;
        bool keyPressed = false;

        for (size_t i = 0; i < keys_.size(); i++)
        {
            if (keys_[i] == 1) // TODO: Write isPressed method
            {
                std::cout << "Key " << i << "found pressed!";
                keyPressed = true;
                keys_[i] = 0;
                reg_[Vx] = i;
                break;
            }
        }

        if (!keyPressed)
        {
            std::cout << "No keys pressed";
            pc_ -= 2;
        }

        break;
    }

    case 0x0015:
    {
        delayTimer_ = reg_[Vx];
        break;
    }

    case 0x0018:
    {
        soundTimer_ = reg_[Vx];
        break;
    }

    case 0x001E:
    {
        index_ += reg_[Vx];
        break;
    }

    case 0x0029:
    {
        index_ = CHIP8_defs::FONTSET_START_ADDRESS + 5 * reg_[Vx];
        break;
    }

    case 0x0033:
    {
        mem_[index_ + 2] = (reg_[Vx] % 10);
        reg_[Vx] /= 10;
        mem_[index_ + 1] = (reg_[Vx] % 10);
        reg_[Vx] /= 10;
        mem_[index_] = (reg_[Vx] % 10);

        break;
    }

    case 0x0055:
    {
        std::copy(&reg_[0], &reg_[Vx + 1], &mem_[index_]); // BUG !!!!!
        break;
    }

    case 0x0065:
    {
        std::copy(&mem_[index_], &mem_[index_ + Vx + 1], &reg_[0]);
        break;
    }
    }
}

void CHIP8_impl::executeOpcode(uint16_t opcode)
{
    opcode_ = opcode;
    executeOpcode();
}

void CHIP8_impl::executeOpcode()
{
   // std::cout << "Opcode: " << std::showbase << std::hex << (int)opcode_ << std::endl;

    switch (opcode_ & 0xF000)
    {
    case 0x0000:
    {
        nibble_0();
        break;
    }

    case 0x1000:
    {
        nibble_1();
        break;
    }

    case 0x2000:
    {
        nibble_2();
        break;
    }
    case 0x3000:
    {
        nibble_3();
        break;
    }

    case 0x4000:
    {
        nibble_4();
        break;
    }

    case 0x5000:
    {
        nibble_5();
        break;
    }

    case 0x6000:
    {
        nibble_6();
        break;
    }


    case 0x7000:
    {
        nibble_7();
        break;
    }

    case 0x8000:
    {
        nibble_8();
        break;
    }

    case 0x9000:
    {
        nibble_9();
        break;
    }

    case 0xA000:
    {
        nibble_A();
        break;
    }

    case 0xB000:
    {
        nibble_B();
        break;
    }

    case 0xC000:
    {
        nibble_C();
        break;
    }

    case 0xD000:
    {
        nibble_D();
        break;
    }

    case 0xE000:
    {
        nibble_E();
        break;
    }

    case 0xF000:
    {
        nibble_F();
        break;
    }


        break;
    }
}

void CHIP8_impl::printMem() const
{
    std::cout << "Printing memory...";
    for (auto it = mem_.cbegin(); it < mem_.cend(); it++)
    {
        std::cout <<std::showbase <<  std::hex << static_cast<int>(*it) << " ";
    }
}

void CHIP8_impl::printReg() const
{
    std::cout << "Printing reg...";
    for (auto it = reg_.cbegin(); it < reg_.cend(); it++)
    {
        std::cout <<std::showbase <<  std::hex << static_cast<int>(*it) << " ";
    }
}

void CHIP8_impl::cycle()
{

//    for (auto i : keys_)
//    {
//        std::cout << (int) i;
//    }
//    std::cout << std::endl;

    // Fetch Opcode


    opcode_ = mem_[pc_] << 8 | mem_[pc_ + 1];
    pc_ = pc_ + 2;

    if (opcode_ == 0xf20a)
    {
        std::cout << "breakpoint";
    }

    executeOpcode();

    // Update timers

    if (delayTimer_ > 0)
    {
        std::cout << "Delay timer is " << (int) delayTimer_;
        delayTimer_--;
    }

    if (soundTimer_ > 0)
    {
        soundTimer_--;
    }


}
