#include <iostream>

#include "application.h"



int main(int argc, char *args[]) {

    Application& app = Application::instance();

    if (!app.init()) {
        std::cerr << "Failed to init" << std::endl;
        return -1;
    }

    app.run();

    app.close();

    return 0;
}
