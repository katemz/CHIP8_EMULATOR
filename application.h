#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <iemulator.h>

class Application
{
public:
    static Application& instance()
    {
        static Application instance_;
        return instance_;
    }

    bool init(std::unique_ptr<IEmulator> emulator);
    void run();
    void close();
private:
    Application();

    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    const int WIDTH = 1024;
    const int HEIGHT = 768;
    std::unique_ptr<IEmulator> emulator_;
};

#endif // APPLICATION_H
