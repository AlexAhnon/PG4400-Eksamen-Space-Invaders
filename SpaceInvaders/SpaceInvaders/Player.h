#pragma once
#include <SDL.h>
#include "WindowManager.h"

class Player {
public:
	Player(SDL_Renderer* rend);

	Player();
	~Player();

	void Spawn();
	void Update();
	void moveLeft(int rate);
	void moveRight(int rate);

	int getX();
private:
	const char* playerIcon = "../Artwork/PlayerBody.bmp";

	SDL_Renderer* renderer;

	SDL_Rect coords;
	SDL_Surface* image;
	SDL_Texture* texture;
};

