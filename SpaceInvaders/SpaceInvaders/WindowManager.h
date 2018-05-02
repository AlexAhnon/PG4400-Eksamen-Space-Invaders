#pragma once
#include <SDL.h>
#include <iostream>

class WindowManager
{
public:
	static WindowManager* getInstance();
	static void Release();

	int InitializeWindow();
	SDL_Window* getWindow();

private:
	SDL_Window * window;
	const char* gameTitle;
	int screenWidth;
	int screenHeight;

	static WindowManager* instance;

	WindowManager();
	~WindowManager();
};