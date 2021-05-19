#include "Player.h"
#include "GameWorld.h"



void Player::Init(int x, int y, int w, int h)
{
    SDL_Log("[OBJECT] Player object initialised\n");
    this->playerSprite.x = x;
    this->playerSprite.y = y;
    this->playerSprite.w = w;
    this->playerSprite.h = h;

    //Create surface from sprite file
    playerSur = IMG_Load("res/Sprites/PlayerSprite.png");
    //Convert surface to texture
    playerTex = SDL_CreateTextureFromSurface(renderer, playerSur);

    //Free up surface data
    SDL_FreeSurface(playerSur);
}

void Player::Input(bool pressedKeys[256], bool mouseClick)
{
    changeX = 0;
    changeY = 0;

    if (pressedKeys[SDLK_w] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeY -= dashSpeed;
            dashCooldown = 60;
        }
        else
        {
            changeY -= speed;
        }
        playerAngle = 0;
    }
    if (pressedKeys[SDLK_a] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeX -= dashSpeed;
            dashCooldown = 60;
        }
        else
        {
            changeX -= speed;
        }
        playerAngle = -90;
    }
    if (pressedKeys[SDLK_s] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeY += dashSpeed;
            dashCooldown = 60;
        }
        else
        {
            changeY += speed;
        }
        playerAngle = 180;
    }
    if (pressedKeys[SDLK_d] == true)
    {
        if (pressedKeys[SDLK_SPACE] == true && dashCooldown <= 0)
        {
            changeX += dashSpeed;
            dashCooldown = 60;
        }
        else
        {
            changeX += speed;
        }
        playerAngle = 90;
    }

    if (pressedKeys[SDLK_w] && pressedKeys[SDLK_d])
    {
        playerAngle = 45;
    }
    if (pressedKeys[SDLK_d] && pressedKeys[SDLK_s])
    {
        playerAngle = 135;
    }
    if (pressedKeys[SDLK_s] && pressedKeys[SDLK_a])
    {
        playerAngle = 225;
    }
    if (pressedKeys[SDLK_a] && pressedKeys[SDLK_w])
    {
        playerAngle = 315;
    }

    if (pressedKeys[SDLK_w] || pressedKeys[SDLK_a] || pressedKeys[SDLK_s] || pressedKeys[SDLK_d])
    {
        moving = true;
    }
    else
    {
        moving = false;
    }
}


void Player::Update()
{
    playerSprite.x += changeX;
    playerSprite.y += changeY;

    unsigned int ticks = SDL_GetTicks();
    unsigned int frameIndex = (ticks / changeTimeMS) % 2;

    if (moving)
    {
        spritePositionRect.x = (64 * frameIndex);
    }



    //Collision handling for the boundaries of the screen
    if (playerSprite.x + playerSprite.w > 1600)
    {
        SDL_Log("[PLAYER] Player is at right screen boundary\n");
        playerSprite.x = 1600 - playerSprite.w;
    }
    if (playerSprite.x < 0)
    {
        SDL_Log("[PLAYER] Player is at left screen boundary\n");
        playerSprite.x = 0;
    }


    if (playerSprite.y + playerSprite.h > 900)
    {
        SDL_Log("[PLAYER] Player is at lower screen boundary\n");
        playerSprite.y = 900 - playerSprite.h;
    }
    if (playerSprite.y < 0)
    {
        SDL_Log("[PLAYER] Player is at upper screen boundary\n");
        playerSprite.y = 0;
    }

    //Collision handling for the enemies
    //TODO

    dashCooldown--;
}

void Player::Render()
{
    SDL_RenderCopyEx(renderer, playerTex, &spritePositionRect, &playerSprite, playerAngle, NULL, SDL_FLIP_NONE);
}