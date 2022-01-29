/*
 * This file is part of C11_TEMPLATE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "common.h"
#include "version.h"

#include <SDL2/SDL.h>

#define GIT_HASH() (git_hash())
#define WINDOW_W (1024)
#define WINDOW_H (768)
#define WINDOW_TITLE "C11_TEMPLATE - {git-sha1 = %s}"

#define UNUSED(x) ((void) (x))
#define ARRLEN(x) (sizeof(x) / sizeof(x[0]))

static sig_atomic_t interrupt_flag = 0;

static void
interrupt_handler (int flag)
{
    UNUSED(flag);

    interrupt_flag = 1;
}

int
main (int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    signal(SIGINT, interrupt_handler);

    char window_title[ARRLEN(WINDOW_TITLE)];
    snprintf(window_title, ARRLEN(WINDOW_TITLE), WINDOW_TITLE, GIT_HASH());

    // Initialize SDL, the window, and the renderer
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window *window = SDL_CreateWindow(window_title, 0, 0,
                                          WINDOW_W, WINDOW_H,
                                          SDL_WINDOW_OPENGL);

    SDL_Renderer *render = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

    // Main rendering loop
    while (!interrupt_flag)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    interrupt_flag = 1;
                }
            }
        }

        SDL_RenderClear(render);
        SDL_RenderPresent(render);
    }

    // Cleanup the SDL objects
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();

    return EXIT_SUCCESS;
}
