#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <iostream>

int main()
{
    bool quit = false;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL." << std::endl;
        return 1;
    }

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);

    int windowWidth = mode.w;
    int windowHeight = mode.h;

    SDL_Window* window = SDL_CreateWindow(
        "Art Prompt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight, SDL_WINDOW_ALWAYS_ON_TOP);

    if (!window)
    {
        std::cout << "Error creating SDL window." << std::endl;
        return 1;
    }

    // -1 means 'default option'
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cout << "Error creating SDL renderer." << std::endl;
        return 1;
    }

    SDL_Surface* image = IMG_Load("../images/Emoji/2763.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Event sdlEvent;
    // sdlEvent is passed by reference
    // event is fetched from queue and assigned to sdlEvent
    while (!quit)
    {
        while (SDL_PollEvent(&sdlEvent))
        {
            // handle core SDL events (close window, key pressed etc.)
            switch (sdlEvent.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_Rect dstRect = { (mode.w / 2) - 256, (mode.h / 2) - 256, 512, 512 };
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
