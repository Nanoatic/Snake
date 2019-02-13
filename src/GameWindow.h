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

class GameWindow {
    void refreshWindow();
public:
    GameWindow();

    GameWindow(int width, int height, string windowname);

    GameWindow(int width, int height, string windowname, color rgb);

    virtual ~GameWindow();

    void mainloop();



protected :
    virtual void renderGame() = 0;
    virtual void logicAndPhysics() = 0 ;
    virtual void init() = 0;
    virtual void shutdown() =0;
    virtual void handleEvents()= 0;
    SDL_Window *windowloc;
    SDL_Event event;
    SDL_Surface *screen;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    bool run;

    double accumulator = 0;


};

#endif