#include <iostream>

#include "application.h"
#include "chip8.h"

int main(int argc, char *args[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./chip8 <ROM file path>" <<std::endl;
        return -1;
    }

    std::string romFile = args[1];

    Application& app = Application::instance();
    std::unique_ptr<IEmulator> chip8 = std::make_unique<CHIP8>();

    chip8->loadROM(romFile);

    if (!app.init(std::move(chip8))) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    app.run();

    app.close();

    return 0;
}
