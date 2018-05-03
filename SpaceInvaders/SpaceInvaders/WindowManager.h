#pragma once
#include <SDL.h>
#include <iostream>

class WindowManager
{
public:
	static WindowManager* getInstance();
	static void Release();

	int SetupWindow();
	void DeleteWindow();
	void UpdateWindow();

	int screenWidth = 500;
	int screenHeight = 550;

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	SDL_Surface* getSurface();
	SDL_Texture* getTexture();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;

	const char* bgImage = "../Artwork/invaders.bmp";
	const char* gameTitle = "Space Invaders";

	int InitWindow();
	int InitRenderer();
	int InitSurface();
	int InitTexture();

	static WindowManager* instance;

	WindowManager();
	~WindowManager();
};