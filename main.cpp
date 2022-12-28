
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <sqlite3.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    bool quit = false;

    /**
    Access SQlite db to write all emoji svgs into the sqlite db
    */
    sqlite3* db;
    int rc;
    char* zErrMsg = 0;
    std::string jobsQuery;
    sqlite3_stmt* compiledJobsQuery{ nullptr };
    std::string emojiSVG = "";

    rc = sqlite3_open("../ranmoji.db", &db);

    if (rc)
    {
        std::cerr << "Unable to open database" << sqlite3_errmsg(db)
                  << std::endl;
        return 0;
    }

    std::cout << "Opened database successfully" << std::endl;

    // select current job: job with status RUNNING
    jobsQuery = "select * from jobs where status = 'RUNNING' limit 1";

    rc = sqlite3_prepare_v2(db, jobsQuery.c_str(), -1, &compiledJobsQuery,
                            nullptr);

    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(compiledJobsQuery);
        std::cerr << "SQLite: Failed to prepare statement: "
                  << sqlite3_errstr(rc) << std::endl;
        return 1;
    }

    rc = sqlite3_step(compiledJobsQuery);

    if (rc == SQLITE_ROW)
    {
        emojiSVG =
            std::string((char*)sqlite3_column_text(compiledJobsQuery, 2));
    }
    else if (rc == SQLITE_DONE)
    {
        jobsQuery =
            "select * from jobs where status = 'NEW' order by random() limit 1";
        rc = sqlite3_prepare_v2(db, jobsQuery.c_str(), -1, &compiledJobsQuery,
                                nullptr);

        if (rc != SQLITE_OK)
        {
            sqlite3_finalize(compiledJobsQuery);
            std::cerr << "SQLite: Failed to prepare statement: "
                      << sqlite3_errstr(rc) << std::endl;
            return 1;
        }

        rc = sqlite3_step(compiledJobsQuery);

        if (rc == SQLITE_ROW)
        {
            emojiSVG =
                std::string((char*)sqlite3_column_text(compiledJobsQuery, 2));
            // TODO: update row; set startedAt to current date, set status to
            // 'RUNNING'
        }
    }

    sqlite3_finalize(compiledJobsQuery);

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

    SDL_RWops* rw = SDL_RWFromConstMem(emojiSVG.c_str(), emojiSVG.size());
    SDL_Surface* image = IMG_LoadSVG_RW(rw);
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
