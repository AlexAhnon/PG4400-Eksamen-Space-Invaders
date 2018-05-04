#include "Shield.h"



Shield::Shield() {
}

Shield::Shield(SDL_Renderer* rend, int health, int x, int y) : Sprite(rend, "../Artwork/shield.bmp", 20, health, x, y) {
	maxHealth = health;
	initialXPos = x;
}


Shield::~Shield() {
}

// Shrink the shield
void Shield::TakeDamage() {
	rect.w -= 10;
	rect.x += 5;
}

// Reset shields back to original
void Shield::Reset() {
	rect.w = maxHealth;
	rect.x = initialXPos;
}
