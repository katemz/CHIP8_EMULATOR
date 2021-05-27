#include <iostream>

#include "application.h"
#include "chip8.h"



int main(int argc, char *args[]) {

    Application& app = Application::instance();
    std::unique_ptr<IPixelArrayDisplay> chip8 = std::make_unique<CHIP8>();

    if (!app.init(std::move(chip8))) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    app.run();

    app.close();

    return 0;
}
