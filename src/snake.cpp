#include "snake.h"

snake::snake(): direction(0) , feeding(0), deployed(false), score(0),loss(false)
{
	head = new part{ 1,1,IDLE,nullptr, nullptr };
	tail = head;

	reset2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	part2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	head2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	food2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);

	SDL_FillRect(head2D, nullptr, SDL_MapRGB(head2D->format, 0, 255, 0));
	SDL_FillRect(part2D, nullptr, SDL_MapRGB(part2D->format, 255, 255, 0));
	SDL_FillRect(reset2D, nullptr, SDL_MapRGB(part2D->format, 0, 0, 0));
	SDL_FillRect(food2D, nullptr, SDL_MapRGB(part2D->format, 255, 0, 0));
	scorefont = TTF_OpenFont("../resources/arcadesnake.ttf", 18);
	fed = Mix_LoadWAV("../resources/feed.wav");
    lose = Mix_LoadWAV("../resources/lose.wav");
}

snake::snake(int width, int height, string snakename, color rgb) : window(FAT*width, FAT*height, snakename, rgb), direction(0), feeding(0), deployed(false), score(0), loss(false)
{
	head = new part{1,1,IDLE,nullptr, nullptr };
	tail = head;
	reset2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	part2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	head2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	food2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);

	SDL_FillRect(head2D, nullptr, SDL_MapRGB(head2D->format, 0, 255, 0));
	SDL_FillRect(part2D, nullptr, SDL_MapRGB(part2D->format, 255, 255, 255));
	SDL_FillRect(reset2D, nullptr, SDL_MapRGB(part2D->format, rgb.red, rgb.green, rgb.blue));
	SDL_FillRect(food2D, nullptr, SDL_MapRGB(part2D->format, 255, 0, 0));
	scorefont = TTF_OpenFont("../resources/arcadesnake.ttf", 18);
	fed = Mix_LoadWAV("../resources/feed.wav");
    lose = Mix_LoadWAV("../resources/lose.wav");

}

snake::snake(int width, int height, string snakename) :window(FAT*width, FAT*height, snakename), direction(0), feeding(0),deployed(false),score(0), loss(false)
{
	head = new part{ 1,1,IDLE,nullptr, nullptr };
	tail = head;

	reset2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	part2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	head2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);
	food2D = SDL_CreateRGBSurface(0, FAT, FAT, 32, 0, 0, 0, 0);

	SDL_FillRect(head2D, nullptr, SDL_MapRGB(head2D->format, 0, 255, 0));
	SDL_FillRect(part2D, nullptr, SDL_MapRGB(part2D->format, 255, 255, 0));
	SDL_FillRect(reset2D, nullptr, SDL_MapRGB(part2D->format,0, 0, 0));
	SDL_FillRect(food2D, nullptr, SDL_MapRGB(part2D->format, 255, 0, 0));
	scorefont = TTF_OpenFont("../resources/arcadesnake.ttf", 18);
	fed = Mix_LoadWAV("../resources/feed.wav");
    lose = Mix_LoadWAV("../resources/lose.wav");

}

string snake::score_to_string()
{
	ostringstream strm;
	strm << score;
	
	return "Score "+strm.str();
}

bool snake::onsnake(int x, int y)
{
	part * cond = head;
	while (cond!=nullptr)
	{
		if (cond->x == x && cond->y == y)
			return true;

		cond = cond->next;

	}
	return false;
}

bool snake::collision()
{
	/*if (head->x == 0 || head->y == 0 || head->y==screen->h/FAT-1 || head->x==screen->w/FAT-1)
		return true;*/
	part * cond = head->next;
	while (cond != nullptr)
	{
		if (head->x == cond->x && head->y == cond->y)
			return true;
		cond = cond->next;
	}
	return false;
}

void snake::deploy(int &x,int &y)
{
	if (!deployed) {
		deployed = true;
		srand((unsigned int) time(0));
		do {
			x = rand() % (screen->w / FAT);
			y = rand() % (screen->h / FAT);
		} while (onsnake(x, y) || y==0 );
		SDL_Rect rect;
		rect.x = x*FAT;
		rect.y = y*FAT;
		SDL_BlitSurface(food2D, nullptr, screen, &rect);
	}
}

void snake::render()
{
	SDL_Rect rect;
	part * cond = head;
	while (cond != nullptr)
	{
		rect.x = cond->x*FAT;
		rect.y = cond->y*FAT;
		if(cond==head)
		SDL_BlitSurface(head2D, nullptr, screen, &rect);
		else
		SDL_BlitSurface(part2D, nullptr, screen, &rect);
		
		cond = cond->next;
	}
}

void snake::moveright()
{
	part * cond = tail;
	SDL_Rect rect;
	rect.x = cond->x*FAT;
	rect.y = cond->y*FAT;
	SDL_BlitSurface(reset2D, nullptr, screen, &rect);
	head->direction = RIGHT;
		while (cond->prec!= nullptr)
	{
		cond->x = cond->prec->x;
		cond->y = cond->prec->y;
		cond->direction = cond->prec->direction;
		cond = cond->prec;
	}
		head->x++;
		if (head->x >= screen->w/FAT)
			head->x =0 ;
}

void snake::moveleft()
{
	part * cond = tail;
	SDL_Rect rect;
	rect.x = cond->x*FAT;
	rect.y = cond->y*FAT;
	SDL_BlitSurface(reset2D, nullptr, screen, &rect);
	head->direction = LEFT;
	while (cond->prec != nullptr)
	{
		cond->x = cond->prec->x;
		cond->y = cond->prec->y;
		cond->direction = cond->prec->direction;
		cond = cond->prec;
	}
	head->x--;
	if (head->x < 0)
		head->x = screen->w / FAT -1;
}

void snake::moveup()
{
	part * cond = tail;
	SDL_Rect rect;
	rect.x = cond->x*FAT;
	rect.y = cond->y*FAT;
	SDL_BlitSurface(reset2D, nullptr, screen, &rect);
	head->direction = UP;
	while (cond->prec != nullptr)
	{
		cond->x = cond->prec->x;
		cond->y = cond->prec->y;
		cond->direction = cond->prec->direction;
		cond = cond->prec;
	}
	head->y--;
	if (head->y < 0)
		head->y =screen->h / FAT-1;
}

void snake::movedown()
{
	part * cond = tail;
	SDL_Rect rect;
	rect.x = cond->x*FAT;
	rect.y = cond->y*FAT;
	SDL_BlitSurface(reset2D, nullptr, screen, &rect);
	head->direction = DOWN;
	while (cond->prec != nullptr)
	{
		cond->x = cond->prec->x;
		cond->y = cond->prec->y;
		cond->direction = cond->prec->direction;
		cond = cond->prec;
	}
	head->y++;
	if (head->y >= screen->h/FAT)
		head->y=0;
}

void snake::feed(int row ,int col)
{
	Mix_PlayChannel(4, fed, 0);
	deployed = false;
	score += 50;
	int x(0),y(0);

	if (feeding == 0)
		feeding = 1;

	switch (tail->direction)
	{
	case RIGHT:
		x = tail->x - 1;
		y = tail->y;
		break;
	case LEFT:
		
		x = tail->x +1;
		y = tail->y;
		break;
	case UP:
		x = tail->x;
		y = tail->y + 1;
		break;
	case DOWN:
		x = tail->x;
		y = tail->y - 1;
		break;
	default:
		
		break;
	}
	part * newprt = new part{ x,y,tail->direction,nullptr, nullptr };
	
	newprt->prec=tail;
	tail->next = newprt;
	tail = newprt;
	SDL_Rect rect;
	rect.x = col * FAT;
	rect.y = row * FAT;
	SDL_BlitSurface(reset2D, nullptr, screen, &rect);
}

void snake::mainloop()
{
	SDL_Rect rectsc;
    SDL_Rect rectfps;
	rectsc.x = 0;
	rectsc.y = 0;
    rectfps.x= screen->w -64;
    rectfps.y=0;
	int depx, depy;
	unsigned int startTime, endTime ,diff;

	while (run)
	{
		startTime=SDL_GetTicks();
        //Draw Score
		score2D = TTF_RenderText_Shaded(scorefont, score_to_string().c_str() ,{ 255, 255, 255 }, { 0,0,0 } );
		SDL_BlitSurface(score2D, nullptr, screen, &rectsc);

        //deploy initial snake and save head coords in depx and depy
		deploy(depx, depy);
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP)
				{
					direction = UP;
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					direction = DOWN;
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					direction = RIGHT;
				}
				if (event.key.keysym.sym == SDLK_LEFT)
				{
			         direction = LEFT;
				}
				break;
			case SDL_QUIT:
				run = false;
				break;

			}
		}
		switch (direction)
		{
		case RIGHT:
			switch (feeding)
			{
			case 1:
				if (head->direction != LEFT)
					moveright();
				else
					moveleft();
				break;
			case 0:
				moveright();
				break;
			}
			break;
		case LEFT:
			switch (feeding)
			{
			case 1:
				if (head->direction != RIGHT)
					moveleft();
				else
					moveright();
				break;
			case 0:
				moveleft();
				break;
			}
			break;
		case UP:
			switch (feeding)
			{
			case 1:
				if (head->direction != DOWN)
					moveup();
				else
					movedown();
				break;
			case 0:
				moveup();
				break;
			}
			break;
		case DOWN:
			switch (feeding)
			{
			case 1:
				if (head->direction != UP)
					movedown();
				else
					moveup();
				break;
			case 0:
				movedown();
				break;
			}
			break;
		default:
			break;
		}

		if (head->x == depx && head->y == depy)
			feed(depx, depy);

		render();
		update();
		if (collision())
		{
			loss = true;
            update();
			break;
		}
		endTime=SDL_GetTicks();
		diff=endTime-startTime;

		if((diff)<=1000/FPS)
		SDL_Delay(1000/FPS-diff);
        string strfps=to_string(1000/FPS-diff);
        strfps="fps "+strfps;
        fps2D = TTF_RenderText_Shaded(scorefont,strfps.c_str()  ,{ 255, 255, 255 }, { 0,0,0 } );
        SDL_BlitSurface(fps2D, nullptr, screen, &rectfps);
	}
	if (loss) {

		scorefont = TTF_OpenFont("../resources/arcadesnake.ttf", 48);
		score2D = TTF_RenderText_Shaded(scorefont, "GAME OVER", { 255, 255, 255 }, { 0,0,0 });
		rectsc.x = screen->w / 2-100;
		rectsc.y = screen->h / 2-100;
		SDL_BlitSurface(score2D, NULL, screen, &rectsc);
        Mix_PlayChannel(4, lose, 0);
		update();
		SDL_Delay(5000);
	}
}

snake::~snake()
{
}
