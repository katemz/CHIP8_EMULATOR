#include "application.h"

Application::Application()
{
}

bool Application::init(std::unique_ptr<IEmulator> emulator)
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

    emulator_ = std::move(emulator);

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
        emulator_->cycle();
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                loop = false;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                std::cout << "Pressed..." << std::endl;

                switch( e.key.keysym.sym )
                {
                case SDLK_1:
                    emulator_->keyPressed('1');
                    break;

                case SDLK_2:
                    emulator_->keyPressed('2');
                    break;

                case SDLK_3:
                    emulator_->keyPressed('3');
                    break;

                case SDLK_4:
                    emulator_->keyPressed('4');
                    break;

                case SDLK_5:
                    emulator_->keyPressed('5');
                    break;

                case SDLK_w:
                    emulator_->keyPressed('w');
                    break;

                case SDLK_e:
                    emulator_->keyPressed('e');
                    break;

                case SDLK_r:
                    emulator_->keyPressed('r');
                    break;

                case SDLK_a:
                    emulator_->keyPressed('a');
                    break;

                case SDLK_d:
                    emulator_->keyPressed('d');
                    break;

                case SDLK_s:
                    emulator_->keyPressed('s');
                    break;

                case SDLK_f:
                    emulator_->keyPressed('f');
                    break;

                case SDLK_z:
                    emulator_->keyPressed('z');
                    break;

                case SDLK_x:
                    emulator_->keyPressed('x');
                    break;

                case SDLK_c:
                    emulator_->keyPressed('c');
                    break;

                case SDLK_v:
                    emulator_->keyPressed('v');
                    break;

                default:
                    break;
                }
            }
        }

        // clear
        SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer_);

        int rectWidth = 10;
        int margin = 1;

        for (size_t i = 0; i < emulator_->getHeight(); i++)
        {
            for (size_t j = 0; j < emulator_->getWidth(); j++)
            {
                int y1 = (2*i + 1) * margin + i * rectWidth;
                int x1 = (2*j + 1) * margin + j * rectWidth;

                SDL_Rect fill_rect = {x1, y1, rectWidth, rectWidth};
                bool pixel = emulator_->getPixelAt(j, i);
                if (pixel)
                {
                    SDL_SetRenderDrawColor(renderer_, 0xff, 0x00, 0x00, 0xff);
                    SDL_RenderFillRect(renderer_, &fill_rect);
                }
            }
        }

        SDL_RenderPresent(renderer_);
    }
}
