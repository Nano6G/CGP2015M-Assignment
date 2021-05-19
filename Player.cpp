#include "Player.h"
#include "GameWorld.h"

Player::Player()
{
	printf("Player object created\n");
}

void Player::Init(int x, int y, int w, int h)
{
    this->playerSprite.x = x;
    this->playerSprite.y = y;
    this->playerSprite.w = w;
    this->playerSprite.h = h;
}

void Player::Input()
{
    //printf("Checking inputs for the player...\n");

    /*
    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_w:
                printf("W has been pressed \n");
                //GameWorld pressedKeys[SDLK_w] = true;
                playerSprite.y += 10;
                break;
            }
        }

        if (_event.type == SDL_KEYUP && _event.key.repeat == NULL)
        {
            switch (_event.key.keysym.sym)
            {
            case SDLK_w:
                printf("W has been unpressed \n");
                //pressedKeys[SDLK_w] = false;
                break;
            }
        }
    }
    */
}

void Player::Update(int changeX, int changeY)
{
    playerSprite.x += changeX;
    playerSprite.y += changeY;


}

void Player::Render(SDL_Renderer* renderer)
{
	//printf("Player object drawn\n");
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &playerSprite);
}