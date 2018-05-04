#pragma once
#include <SDL.h>
#include "Sprite.h"

class Player : public Sprite {
public:
	Player();
	Player(SDL_Renderer* renderer);
	~Player();
	
	void MoveLeft(int rate);
	void MoveRight(int rate);
	void Update();

	bool canShoot;
	int hitpoints;
private:
	int reloadSpeed = 50;
	int reloadCounter = 0;
};

