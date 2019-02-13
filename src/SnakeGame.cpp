#include "SnakeGame.h"
#include "TimeManager.h"

SnakeGame::SnakeGame() : direction(0), feeding(0), deployed(false), score(0), loss(false) {
    head = new part{1, 1, IDLE, nullptr, nullptr};
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

//this constructor we will actually use
SnakeGame::SnakeGame(int width, int height, string snakename, color rgb) : GameWindow(FAT * width, FAT * height,
                                                                                      snakename, rgb),
                                                                           direction(0), feeding(0), deployed(false),
                                                                           score(0),
                                                                           loss(false) {
    head = new part{1, 1, IDLE, nullptr, nullptr};
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

SnakeGame::SnakeGame(int width, int height, string snakename) : GameWindow(FAT * width, FAT * height, snakename),
                                                                direction(0),
                                                                feeding(0), deployed(false), score(0), loss(false) {
    head = new part{1, 1, IDLE, nullptr, nullptr};
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

//convert score to string
string SnakeGame::score_to_string() {
    ostringstream strm;
    strm << score;

    return "Score " + strm.str();
}

//used to test if something on the SnakeGame {food} to avoid spwning the food on the SnakeGame
bool SnakeGame::onsnake(int x, int y) {
    part *cond = head;
    while (cond != nullptr) {
        if (collisionTwoRectangles(x, y, FAT,FAT, cond->x, cond->y, FAT,FAT))
            return true;

        cond = cond->next;

    }
    return false;
}

//test Collision
bool SnakeGame::collision() {
    /*if (head->x == 0 || head->y == 0 || head->y==screen->h/FAT-1 || head->x==screen->w/FAT-1)
        return true;*/
    part *cond = head->next;
    //test all parts with collision with the head
    while (cond != nullptr) {
        if (collisionTwoRectangles(head->x, head->y,  FAT,FAT, cond->x, cond->y,  FAT,FAT))
            return true;
        cond = cond->next;
    }
    return false;
}

//deploy food
void SnakeGame::deployFood(int &x, int &y) {
    if (!deployed) {
        deployed = true;
        srand((unsigned int) time(0));
        do {
            x = rand() % (screen->w );
            y = rand() % (screen->h );
            std::cout<< x <<","<<y<<endl ;
        } while (onsnake(x, y) || y == 0);

        foodRect.x = x ;
        foodRect.y = y ;

    }
}

//draw the whole SnakeGame
void SnakeGame::renderSnake() {
    SDL_Rect rect;
    part *part1 = head;
    while (part1 != nullptr) {
        rect.x = part1->x;
        rect.y = part1->y;
        if (part1 == head)
            SDL_BlitSurface(head2D, nullptr, screen, &rect);
        else
            SDL_BlitSurface(part2D, nullptr, screen, &rect);

        part1 = part1->next;
    }
}

// move SnakeGame head to the right
void SnakeGame::moveright() {
    part *cond = tail;
    head->direction = RIGHT;
    while (cond->prec != nullptr) {
        cond->x = cond->prec->x;
        cond->y = cond->prec->y;
        cond->direction = cond->prec->direction;
        cond = cond->prec;
    }
    head->x+=FAT ;
    if (head->x >= screen->w )
        head->x = 0;


}

//move  SnakeGame head to the left
void SnakeGame::moveleft() {


    part *cond = tail;
    head->direction = LEFT;
    while (cond->prec != nullptr) {
        cond->x = cond->prec->x;
        cond->y = cond->prec->y;
        cond->direction = cond->prec->direction;
        cond = cond->prec;
    }
    head->x-=FAT;
    if (head->x < 0)
        head->x = screen->w;


}

//move SnakeGame head up
void SnakeGame::moveup() {
    part *part1 = tail;

    head->direction = UP;
    while (part1->prec != nullptr) {
        part1->x = part1->prec->x;
        part1->y = part1->prec->y;
        part1->direction = part1->prec->direction;
        part1 = part1->prec;
    }
    head->y-=FAT;
    if (head->y < 0)
        head->y = screen->h;
}

//move SnakeGame head down
void SnakeGame::movedown() {
    part *part1 = tail;

    head->direction = DOWN;

    while (part1->prec != nullptr) {
        part1->x = part1->prec->x;
        part1->y = part1->prec->y;
        part1->direction = part1->prec->direction;
        part1 = part1->prec;
    }
    head->y+=FAT;
    if (head->y >= screen->h)
        head->y = 0;

}

//feed and add to tail the foot part will become the tail part
void SnakeGame::feed() {
    Mix_PlayChannel(4, fed, 0);
    //deployed is used to deploy next food
    deployed = false;
    //scoring
    score += 50;
    int x(0), y(0);

    if (feeding == 0)
        feeding = 1;

    switch (tail->direction) {
        case RIGHT:
            x = tail->x - FAT;
            y = tail->y;
            break;
        case LEFT:
            x = tail->x + FAT;
            y = tail->y;
            break;
        case UP:
            x = tail->x;
            y = tail->y + FAT;
            break;
        case DOWN:
            x = tail->x;
            y = tail->y - FAT;
            break;
        default:

            break;
    }
    //adding new part to SnakeGame
    part *newprt = new part{x, y, tail->direction, nullptr, nullptr};

    newprt->prec = tail;
    tail->next = newprt;
    tail = newprt;
    std::cout << "Fed" << std::endl;
}


SnakeGame::~SnakeGame() {
}


void SnakeGame::init() {
    rectsc.x = 0;
    rectsc.y = 0;
    rectfps.x = static_cast<int>(screen->w - 64 * 2 / 1.75);
    rectfps.y = 0;


}

void SnakeGame::renderGame() {
    //draw fps
    string strfps = to_string(TimeManager::getInstance().getFps());
    strfps = "fps " + strfps;
    fps2D = TTF_RenderText_Shaded(scorefont, strfps.c_str(), {255, 255, 255}, {0, 0, 0});
    SDL_BlitSurface(fps2D, nullptr, screen, &rectfps);

    //Draw Score
    score2D = TTF_RenderText_Shaded(scorefont, score_to_string().c_str(), {255, 255, 255}, {0, 0, 0});
    SDL_BlitSurface(score2D, nullptr, screen, &rectsc);

    // SnakeGame not to move in the opposite direction
    if (deployed) {
        SDL_BlitSurface(food2D, nullptr, screen, &foodRect);
    }

    renderSnake();


}

void SnakeGame::logicAndPhysics() {
    switch (direction) {
        case RIGHT:
            switch (feeding) {
                case 1:
                    if (head->direction != LEFT)
                        moveright();
                    else
                        moveleft();
                    break;
                case 0:
                    moveright();
                    break;
                default:
                    break;
            }
            break;
        case LEFT:
            switch (feeding) {
                case 1:
                    if (head->direction != RIGHT)
                        moveleft();
                    else
                        moveright();
                    break;
                case 0:
                    moveleft();
                    break;
                default:
                    break;
            }
            break;
        case UP:
            switch (feeding) {
                case 1:
                    if (head->direction != DOWN)
                        moveup();
                    else
                        movedown();
                    break;
                case 0:
                    moveup();
                    break;
                default:
                    break;
            }
            break;
        case DOWN:
            switch (feeding) {
                case 1:
                    if (head->direction != UP)
                        movedown();
                    else
                        moveup();
                    break;
                case 0:
                    movedown();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
if(collisionTwoRectangles(head->x,head->y,FAT,FAT,depx,depy,FAT,FAT))
        feed();

    deployFood(depx, depy);

    if (collision()) {
        loss = true;
        run = false;
    }

}

void SnakeGame::shutdown() {
    if (loss) {
        scorefont = TTF_OpenFont("../resources/arcadesnake.ttf", 48);
        score2D = TTF_RenderText_Shaded(scorefont, "GAME OVER", {255, 255, 255}, {0, 0, 0});
        rectsc.x = screen->w / 2 - 100;
        rectsc.y = screen->h / 2 - 100;
        SDL_BlitSurface(score2D, NULL, screen, &rectsc);
        Mix_PlayChannel(4, lose, 0);

        SDL_Delay(5000);
    }

}

void SnakeGame::handleEvents() {

    switch (event.type) {
        case SDL_KEYUP:

            if (event.key.keysym.sym == SDLK_UP) {
                direction = UP;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                direction = DOWN;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                direction = RIGHT;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                direction = LEFT;
            }
            break;
        case SDL_QUIT:
            run=false;
            break;
        default:
            break;

    }

}

bool
SnakeGame::collisionTwoRectangles(int coord1X, int coord1Y, int w1, int h1, int coord2X, int coord2Y, int w2, int h2) {
    return coord1X < coord2X + w2 && coord2X < coord1X + w1 && coord1Y < coord2Y + h2 && coord2Y < coord1Y + h1;
}

