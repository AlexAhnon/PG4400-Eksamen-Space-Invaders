#include "Player.h"

Player::Player() {
}

Player::Player(SDL_Renderer* rend) {
	renderer = rend;

	// Initialize player sprite size and coords
	// Size
	coords.h = 30;
	coords.w = 50;

	// Coords
	coords.x = 225;
	coords.y = 500;
}


Player::~Player() {
}

// Spawn the player sprite
void Player::Spawn() {
	image = SDL_LoadBMP(playerIcon);
	texture = SDL_CreateTextureFromSurface(renderer, image);
}

// Update the player
void Player::Update() {
	SDL_RenderCopy(renderer, texture, NULL, &coords);
}

// Move player left
void Player::MoveLeft(int rate) {
	coords.x = coords.x - rate;
}

// Move player right
void Player::MoveRight(int rate) {
	coords.x = coords.x + rate;
}

// Returns players x position
int Player::getX() {
	return coords.x;
}
