#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(SDL_Renderer* rend) : Sprite(renderer, "../Artwork/GreenBody.bmp", 30, 30, 0, 0)
{
	renderer = rend;

	// Which direction to move in, 1 = right, 0 = left
	moveDirection = 1;

	// Horizontal movement counters
	moveCounter = 0;
	maxMovement = 100; // Divide by 60 (our current FPS) to get real seconds

	// Vertical movement counters
	downMoveCounter = 0;
	maxDownCounter = 1;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	// Change enemy's direction
	if (moveDirection == 0) {
		MoveLeft(1);
	}
	else if (moveDirection == 1) {
		MoveRight(1);
	}

	// Max amount of updates moving towards a side before switching
	if (moveCounter == maxMovement && moveDirection == 0) {
		moveDirection = 1;
		moveCounter = 0;
		downMoveCounter++;
	}
	else if (moveCounter == maxMovement && moveDirection == 1) {
		moveDirection = 0;
		moveCounter = 0;
		downMoveCounter++;
	}

	// Once a certain amount of switches has happened, move the enemy down one notch
	if (downMoveCounter == maxDownCounter) {
		MoveDown();
		downMoveCounter = 0;
	}

	moveCounter++;
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
