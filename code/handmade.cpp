#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void printSDL_Error() {
    printf("SDL_Error: %s\n", SDL_GetError());
}

bool handleEvent(SDL_Event *event) {
    bool shouldQuit= false;
    switch (event->type) {
    case SDL_QUIT: {
        printf("SDL_QUIT\n");
        shouldQuit = true;
    } break;
    case SDL_WINDOWEVENT: {
        switch (event->window.event) {
        case SDL_WINDOWEVENT_RESIZED: {
            printf("Window %d resized to %dx%d\n",
                    event->window.windowID,
                    event->window.data1,
                    event->window.data2);
        } break;
        }
    } break;
    case SDL_WINDOWEVENT_EXPOSED: {
        SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
        SDL_Renderer *renderer = SDL_GetRenderer(window);
        static bool isWhite = true;
        SDL_RenderClear(renderer);
        if (isWhite) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            isWhite = false;
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            isWhite = true;
        }
        SDL_RenderPresent(renderer);
    } break;
    default: {
        } break;
    }
    return shouldQuit;
}

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printSDL_Error();
        return 1;
    } else {
        window = SDL_CreateWindow("Handmade Hero",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_RESIZABLE);
        if (!window) {
            printSDL_Error();
            SDL_QUIT;
            return 1;
        }

        // Try there for renderFlags: SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        Uint32 renderFlags = 0;
        renderer = SDL_CreateRenderer(window,
                                      -1, // Default driver index
                                      renderFlags);
        if (!renderer) {
            printSDL_Error();
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        for ( ; ; ) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            if (handleEvent(&event)) {
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
