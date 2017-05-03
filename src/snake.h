#ifndef SNAKE_H 
#define SNAKE_H 
#include "window.h"
#include <ctime>
#define FPS 30
#define RIGHT 0x0A
#define LEFT 0x0B
#define UP 0x0C
#define DOWN 0x0D
#define IDLE 0xFF
#define FAT 16


typedef struct part part;
struct part
{
	int x;
	int y;
	int direction;
	part * next;
	part * prec;
};
class snake : public window
{
public:
	snake();
	snake(int width, int height, string snakename, color rgb);
	snake(int width, int height, string snakename);
	void mainloop();
	~snake();
private :
	
	string score_to_string();
	bool onsnake(int x, int y);
	bool collision();
	void deploy(int &x, int &y);
	void render();
	void moveright();
	void moveleft();
	void moveup();
	void movedown();
	void feed(int row, int col);
	bool deployed;
	bool loss;
	int feeding ;
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
	part * head;
	part * tail;

};
#endif // ! 
