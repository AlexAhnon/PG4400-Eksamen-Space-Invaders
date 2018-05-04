#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(SDL_Renderer *rend, const char* image, int height, int width, int x, int y)
{
	imagePath = image;
	renderer = rend;
	SetRect(height, width, x, y);
}


Sprite::~Sprite()
{
}

void Sprite::Draw()
{
	sprite = SDL_LoadBMP(imagePath);
	texture = SDL_CreateTextureFromSurface(renderer, sprite);
}

void Sprite::RenderUpdate()
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Sprite::Destroy() {
	// Destroy the texture and free the surface
	SDL_DestroyTexture(texture);
	//SDL_FreeSurface(sprite);

	// Set it to a random point outside of screen to get rid of rect
	rect.x = -50;
	rect.y = -50;
}

void Sprite::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Sprite::SetRect(int height, int width, int x, int y)
{
	rect.h = height;
	rect.w = width;
	rect.x = x;
	rect.y = y;
}
