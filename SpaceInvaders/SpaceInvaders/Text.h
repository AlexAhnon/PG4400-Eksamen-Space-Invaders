#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
public:
	Text();
	Text(SDL_Renderer* rend);
	~Text();

	void Update(const char* string);

private:
	TTF_Font * font;
	SDL_Color color;
	SDL_Renderer* renderer;
	SDL_Surface* surfaceMessage;
	SDL_Texture* message;
	SDL_Rect rect;
};

