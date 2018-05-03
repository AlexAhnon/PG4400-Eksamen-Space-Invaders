#pragma once
#include <SDL.h>
#include "WindowManager.h"
#include "Sprite.h"

class Player : public Sprite {
public:
	Player();
	Player(SDL_Renderer* rend);
	~Player();

	void MoveLeft(int rate);
	void MoveRight(int rate);
private:
	// SDL_Rect variabler
	int height;
	int width;
	int initXPos;
	int initYPos;
};

