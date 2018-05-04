#pragma once
#include "Sprite.h"

class Shield : public Sprite {
public:
	Shield();
	Shield(SDL_Renderer* rend, int health, int x, int y);
	~Shield();

	void TakeDamage();
	void Reset();
private:
	int maxHealth;
	int initialXPos;
};

