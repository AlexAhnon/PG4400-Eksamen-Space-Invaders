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
	sprite = IMG_Load(imagePath);
	texture = SDL_CreateTextureFromSurface(renderer, sprite);
}

void Sprite::RenderUpdate()
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Sprite::SetRect(int height, int width, int x, int y)
{
	rect.h = height;
	rect.w = width;
	rect.x = x;
	rect.y = y;
}
