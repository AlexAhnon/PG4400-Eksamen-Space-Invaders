#include "Text.h"



Text::Text()
{
}

Text::Text(SDL_Renderer* rend)
{
	renderer = rend;

	font = TTF_OpenFont("../Fonts/Sans.ttf", 18);
	color = { 255, 255, 255 };
	rect.x = 10;
	rect.y = 5;
	rect.h = 34;
	rect.w = 150;
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
