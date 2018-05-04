#pragma once
#include <SDL.h>
#include "Sprite.h"

class Player : public Sprite {
public:
	Player();
	Player(SDL_Renderer* rend);
	~Player();

	enum character_type {
		player,
		enemy
	};

	bool can_shoot;
	int reload_speed = 50;
	int reload_counter = 0;
	void MoveLeft(int rate);
	void MoveRight(int rate);
	void Update();
};

