#pragma once
#include <SDL.h>
#include "Sprite.h"

class Enemy : public Sprite
{
public:
	Enemy();
	Enemy(SDL_Renderer* rend);
	~Enemy();

	void Update();

	void MoveLeft(int rate);
	void MoveRight(int rate);
	void MoveDown();
private:
	// Movement direction
	int moveDirection;

	// Side by side movement
	int moveCounter;
	int maxMovement;

	// Movement down screen
	int downMoveCounter;
	int maxDownCounter;
};

