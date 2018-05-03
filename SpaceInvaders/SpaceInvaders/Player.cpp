#include "Player.h"

Player::Player() {
}

Player::Player(SDL_Renderer* rend) : Sprite(renderer, "../Artwork/PlayerBody.bmp", height, width, initXPos, initYPos) {
	renderer = rend;
	height = 30;
	width = 50;
	initXPos = 225;
	initYPos = 500;
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
