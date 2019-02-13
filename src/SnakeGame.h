#ifndef SNAKE_H
#define SNAKE_H

#include "GameWindow.h"
#include <ctime>

#define FPS 30
#define RIGHT 0x0A
#define LEFT 0x0B
#define UP 0x0C
#define DOWN 0x0D
#define IDLE 0xFF
#define FAT 16


typedef struct part part;

struct part {
    int x;
    int y;
    int direction;
    part *next;
    part *prec;
};

class SnakeGame : public GameWindow {
public:
    SnakeGame();

    SnakeGame(int width, int height, string snakename, color rgb);

    SnakeGame(int width, int height, string snakename);

protected:
    void renderGame() override;

    void logicAndPhysics() override;

    void handleEvents() override;

    void init() override;

    void shutdown() override;


public:
    ~SnakeGame();

private :

    string score_to_string();

    bool onsnake(int x, int y);

    bool collisionTwoRectangles(int coord1X, int coord1Y, int w1, int h1, int coord2X, int coord2Y, int w2, int h2);

    bool collision();

    void deployFood(int &x, int &y);

    void renderSnake();

    void moveright();

    void moveleft();

    void moveup();

    void movedown();

    void feed();

    bool deployed;
    bool loss;
    int feeding;
    int direction;
    int score;
    SDL_Surface *part2D;
    SDL_Surface *reset2D;
    SDL_Surface *head2D;
    SDL_Surface *food2D;
    SDL_Surface *score2D;
    SDL_Surface *fps2D;
    Mix_Chunk *fed;
    Mix_Chunk *lose;
    TTF_Font *scorefont;
    part *head;
    part *tail;

    SDL_Rect foodRect;
    SDL_Rect rectsc;
    SDL_Rect rectfps;

    int depx, depy;
};

#endif // !
