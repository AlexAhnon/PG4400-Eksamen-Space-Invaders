#include "Player.h"

Player::Player() {
}

Player::Player(SDL_Renderer* renderer) : Sprite(renderer, "../Artwork/PlayerBody.bmp", 30, 50, 225, 500) {
	canShoot = true;
	hitpoints = 3;
}

Player::~Player() {
}

// Move player left
void Player::MoveLeft(int rate) {
	rect.x -= rate;
}

// Move player right
void Player::MoveRight(int rate) {
	rect.x += rate;
}

void Player::Update()
{
	if (reloadCounter == reloadSpeed) {
		canShoot = true;
		reloadCounter = 0;
	}
	reloadCounter++;
}

