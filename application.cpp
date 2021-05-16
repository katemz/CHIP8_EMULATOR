#include "application.h"

Application::Application()
{
}

bool Application::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to init: " << SDL_GetError() << std::endl;
        return false;
    }

    window_ = SDL_CreateWindow("CHIP8 EMULATOR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window_ == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

    if (renderer_ == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff) < 0)
    {
        std::cerr << "Failed to set renderer drawing color: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Application::close()
{
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    SDL_Quit();
}

void Application::run()
{
    bool loop = true;

    while (loop)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_w:
                    std::cout << "Pressed up!" << std::endl;
                    break;

                    case SDLK_a:
                    std::cout << "Pressed left!" << std::endl;
                    break;

                    case SDLK_d:
                    std::cout << "Pressed right!" << std::endl;
                    break;

                    case SDLK_s:
                    std::cout << "Pressed down!" << std::endl;
                    break;

                    default:
                    break;
                }
            }
        }

        // clear
        SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer_);

        size_t n = 60;
        int rectWidth = 10;
        int margin = 1;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                int x1 = (2*i + 1) * margin + i * rectWidth;
                int y1 = (2*j + 1) * margin + j * rectWidth;

                //std::cout << "Rectangle: " << i << " - x1,y1: " << x1 << "," << y1 << std::endl;


                SDL_Rect fill_rect = {x1, y1, rectWidth, rectWidth};
                SDL_SetRenderDrawColor(renderer_, 0xff, 0x00, 0x00, 0xff);
                SDL_RenderFillRect(renderer_, &fill_rect);
            }
        }

        SDL_RenderPresent(renderer_);
    }
}
