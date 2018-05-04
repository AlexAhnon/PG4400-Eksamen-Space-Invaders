#include "Text.h"



Text::Text()
{
}

Text::Text(SDL_Renderer* rend, int x, int y, int height, int width)
{
	renderer = rend;

	font = TTF_OpenFont("../Fonts/Sans.ttf", 18); // Font type
	color = { 255, 255, 255 }; // White color

	rect.x = x;
	rect.y = y;
	rect.h = height;
	rect.w = width;
}


Text::~Text()
{
}

void Text::Update(const char* string)
{
	surfaceMessage = TTF_RenderText_Solid(font, string, color);
	message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_RenderCopy(renderer, message, NULL, &rect);
}
