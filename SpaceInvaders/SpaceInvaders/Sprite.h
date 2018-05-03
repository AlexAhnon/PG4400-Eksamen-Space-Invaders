#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Sprite
{
public:
	Sprite();
	Sprite(SDL_Renderer *rend, const char* image, int height, int width, int x, int y);
	~Sprite();

	void Draw();
	void Update();

	int getX() { return rect.x; }
	int getY() { return rect.y; }
protected:
	const char* imagePath;
	SDL_Renderer* renderer;
	SDL_Rect rect;
	SDL_Surface* sprite;
	SDL_Texture* texture;

	void SetRect(int height, int width, int x, int y);
};

