#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;
typedef struct color color;
struct color {
    Uint8 red;
    Uint8 green;
    Uint8 blue;
};

class window {
public:
    window();

    window(int width, int height, string windowname);

    window(int width, int height, string windowname, color rgb);

    virtual ~window();

    virtual void mainloop();

    void update();

protected :
    SDL_Window *windowloc;
    SDL_Event event;
    SDL_Surface *screen;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    bool run;
};

#endif