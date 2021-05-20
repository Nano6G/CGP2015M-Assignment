#include "Enemy.h"
#include "GameWorld.h"

void Enemy::Init(int x, int y, SDL_Renderer* mainRenderer, int spriteNumber)
{
    renderer = mainRenderer;

	SDL_Log("[OBJECT] Enemy object initialised\n"); //Logs enemy initialisation

	this->enemySprite.x = x;
	this->enemySprite.y = y;
	this->enemySprite.w = 64;
	this->enemySprite.h = 64;


    //Choose between the two enemy sprites
    if (spriteNumber == 0)
    {
        enemySur = IMG_Load("res/Sprites/EnemySprite1.png");
    }
    else if (spriteNumber == 1)
    {
        enemySur = IMG_Load("res/Sprites/EnemySprite2.png");
    }
	
	//Convert surface to texture
	enemyTex = SDL_CreateTextureFromSurface(renderer, enemySur);

	//Clean up surface data
	SDL_FreeSurface(enemySur);
}

void Enemy::Update()
{
    //Collision handling for the boundaries of the screen
    if (enemySprite.x + enemySprite.w > 1600)
    {
        SDL_Log("[PLAYER] Player is at right screen boundary\n");
        enemySprite.x = 1600 - enemySprite.w;
    }
    if (enemySprite.x < 0)
    {
        SDL_Log("[PLAYER] Player is at left screen boundary\n");
        enemySprite.x = 0;
    }


    if (enemySprite.y + enemySprite.h > 900)
    {
        SDL_Log("[PLAYER] Player is at lower screen boundary\n");
        enemySprite.y = 900 - enemySprite.h;
    }
    if (enemySprite.y < 0)
    {
        SDL_Log("[PLAYER] Player is at upper screen boundary\n");
        enemySprite.y = 0;
    }
}

void Enemy::Render()
{
    //Renders the enemy
	SDL_RenderCopyEx(renderer, enemyTex, &spritePositionRect, &enemySprite, enemyAngle, NULL, SDL_FLIP_NONE);
}