

#include "snake.h"

int main(int argc, char *argv[])
{
	
	snake sk(30, 30, "Nano Snake", { 0, 0, 0 });
	sk.mainloop();
	return 0;
}