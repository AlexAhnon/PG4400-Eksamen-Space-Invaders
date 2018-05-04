#include "Player.h"

Player::Player() {
}

Player::Player(SDL_Renderer* rend) : Sprite(renderer, "../Artwork/PlayerBody.bmp", 30, 50, 225, 500) {
	renderer = rend;
	can_shoot = true;
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
	if (reload_counter == reload_speed) {
		can_shoot = true;
		reload_counter = 0;
	}
	reload_counter++;
}

