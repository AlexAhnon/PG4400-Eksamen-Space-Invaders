#pragma once
#include <SDL.h>
#include <string>

class Sprite
{
public:
	Sprite();
	Sprite(SDL_Renderer *rend, const char* image, int height, int width, int x, int y);
	~Sprite();

	void Draw();
	void RenderUpdate();

	int getX() { return rect.x; }
	int getY() { return rect.y; }

	SDL_Rect getRect() { return rect; }

	void SetPos(int x, int y);
protected:
	const char* imagePath;
	SDL_Renderer* renderer;
	SDL_Rect rect;
	SDL_Surface* sprite;
	SDL_Texture* texture;

	void SetRect(int height, int width, int x, int y);
};

