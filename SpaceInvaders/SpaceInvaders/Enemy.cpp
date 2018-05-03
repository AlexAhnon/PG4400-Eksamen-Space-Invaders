#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(SDL_Renderer* rend) : Sprite(renderer, "../Artwork/GreenBody.bmp", 30, 30, 0, 0)
{
	renderer = rend;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::MoveLeft(int rate)
{
	rect.x -= rate;
}

void Enemy::MoveRight(int rate)
{
	rect.x += rate;
}

void Enemy::MoveDown()
{
	rect.y += 35;
}
