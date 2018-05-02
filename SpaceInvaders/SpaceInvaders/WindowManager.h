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

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	SDL_Surface* getSurface();
	SDL_Texture* getTexture();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;

	const char* bgImage;
	const char* gameTitle;
	int screenWidth;
	int screenHeight;

	int InitializeWindow();
	int InitializeRenderer();
	int InitializeSurface();
	int InitializeTexture();

	static WindowManager* instance;

	WindowManager();
	~WindowManager();
};