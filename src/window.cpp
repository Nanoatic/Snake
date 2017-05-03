#include "window.h"

window::window() : run(true) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cout << SDL_GetError << endl;
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("%s", Mix_GetError());
    }
    TTF_Init();
    Mix_AllocateChannels(32);
    windowloc = SDL_CreateWindow("Snaky",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 640, 480,
                                 SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(windowloc, -1, 0);
    SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));


}

window::window(int width, int height, string windowname, color rgb) : run(true) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cout << SDL_GetError << endl;
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("%s", Mix_GetError());
    }
    Mix_AllocateChannels(32);
    TTF_Init();
    windowloc = SDL_CreateWindow(windowname.c_str(),
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 height, width,
                                 SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(windowloc, -1, SDL_RENDERER_PRESENTVSYNC);
    screen = SDL_CreateRGBSurface(0, 640, 480, 32,
                                  rgb.red,
                                  rgb.green,
                                  rgb.blue,
                                  0xFF000000);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                640, 480);
}

window::window(int width, int height, string windowname) : run(true) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cout << SDL_GetError << endl;
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("%s", Mix_GetError());
    }
    Mix_AllocateChannels(32);
    TTF_Init();
    windowloc = SDL_CreateWindow(windowname.c_str(),
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 height, width,
                                 SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(windowloc, -1, 0);
    screen = SDL_CreateRGBSurface(0, 640, 480, 32,
                                  0,
                                  0,
                                  0,
                                  0xFF000000);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                640, 480);
}

window::~window() {
    Mix_CloseAudio();
    SDL_FreeSurface(screen);
    SDL_Quit();
}

SDL_Surface *window::getScreen() {
    return screen;
}

void window::mainloop() {

    while (run) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                run = false;
                break;

        }
        update();
    }

}

void window::update() {
    SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

}
