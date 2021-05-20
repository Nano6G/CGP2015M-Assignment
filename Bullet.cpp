#include "Bullet.h"
#include "GameWorld.h"

void Bullet::Init(double playerAngle, int playerX, int playerY, SDL_Renderer* mainRenderer)
{
    SDL_Log("[OBJECT] Bullet object initialised\n");
    renderer = mainRenderer;

    //Create surface from sprite file
    bulletSur = IMG_Load("res/Sprites/BulletSprite.png");
    //Convert surface to texture
    bulletTex = SDL_CreateTextureFromSurface(renderer, bulletSur);
    SDL_SetTextureAlphaMod(bulletTex, 128);

    //Free up surface data
    SDL_FreeSurface(bulletSur);

    bulletAngle = playerAngle;

    bulletSprite.x = playerX;
    bulletSprite.y = playerY;
    bulletSprite.w = 16;
    bulletSprite.h = 48;
}

void Bullet::Update()
{
    if (activeBullet)
    {
        if (bulletAngle == 0)
        {
            changeY = -bulletSpeed;
        }
        else if (bulletAngle == 45)
        {
            changeX = bulletSpreadSpeed;
            changeY = -bulletSpreadSpeed;
        }
        else if (bulletAngle == 90)
        {
            changeX = bulletSpeed;
        }
        else if (bulletAngle == 135)
        {
            changeX = bulletSpreadSpeed;
            changeY = bulletSpreadSpeed;
        }
        else if (bulletAngle == 180)
        {
            changeY = bulletSpeed;
        }
        else if (bulletAngle == 225)
        {
            changeX = -bulletSpreadSpeed;
            changeY = bulletSpreadSpeed;
        }
        else if (bulletAngle == 270)
        {
            changeX = -bulletSpeed;
        }
        else if (bulletAngle == 315)
        {
            changeX = -bulletSpreadSpeed;
            changeY = -bulletSpreadSpeed;
        }

        bulletSprite.x += changeX;
        bulletSprite.y += changeY;

        //Collision handling for the boundaries of the screen
        if (bulletSprite.x + bulletSprite.w > 1600)
        {
            SDL_Log("[COLLISION] Bullet is passed right screen boundary and now being ignored\n");
            activeBullet = false;
        }
        if (bulletSprite.x < 0)
        {
            SDL_Log("[COLLISION] Bullet is passed left screen boundary and now being ignored\n");
            activeBullet = false;
        }


        if (bulletSprite.y + bulletSprite.h > 900)
        {
            SDL_Log("[COLLISION] Bullet is passed lower screen boundary and now being ignored\n");
            activeBullet = false;
        }
        if (bulletSprite.y < 0)
        {
            SDL_Log("[COLLISION] Bullet is passed upper screen boundary and now being ignored\n");
            activeBullet = false;
        }
    }
}

void Bullet::Render()
{
    if (activeBullet)
    {
        SDL_RenderCopyEx(renderer, bulletTex, &spritePositionRect, &bulletSprite, bulletAngle, NULL, SDL_FLIP_NONE);
    }
}