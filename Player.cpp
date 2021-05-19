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

void Player::Input(bool pressedKeys[256])
{
    //printf("Checking inputs for the player...\n");

    changeX = 0;
    changeY = 0;

    if (pressedKeys[SDLK_w] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeY -= 50;
            dashCooldown = 20;
        }
        else
        {
            changeY -= 10;
        }
    }
    if (pressedKeys[SDLK_a] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeX -= 50;
            dashCooldown = 20;
        }
        else
        {
            changeX -= 10;
        }
    }
    if (pressedKeys[SDLK_s] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeY += 50;
            dashCooldown = 20;
        }
        else
        {
            changeY += 10;
        }
    }
    if (pressedKeys[SDLK_d] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeX += 50;
            dashCooldown = 20;
        }
        else
        {
            changeX += 10;
        }
    }
}

void Player::Update()
{
    //printf("Updating the player...\n");

    playerSprite.x += changeX;
    playerSprite.y += changeY;

    dashCooldown--;
}

void Player::Render(SDL_Renderer* renderer)
{
	//printf("Player object drawn\n");
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &playerSprite);
}