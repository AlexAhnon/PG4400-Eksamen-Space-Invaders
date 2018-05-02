#include "WindowManager.h"

WindowManager * WindowManager::instance = NULL;

WindowManager * WindowManager::getInstance() {
	if (!instance)
		instance = new WindowManager();

	return instance;
}

void WindowManager::Release() {
	delete instance;
	instance = NULL;
}

WindowManager::WindowManager()
{
	window = nullptr;
	gameTitle = "Space Invaders";
	screenHeight = 550;
	screenWidth = 500;
}


WindowManager::~WindowManager()
{
}

int WindowManager::InitializeWindow()
{
	window = SDL_CreateWindow(
		gameTitle, // Title
		SDL_WINDOWPOS_UNDEFINED, // Initial x position
		SDL_WINDOWPOS_UNDEFINED, // Initial y position
		screenWidth, // Screen width in pixels
		screenHeight, // Screen height in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL // Flags
	);

	// Window exception in case something went wrong
	if (window == nullptr) {
		return 1;
	}

	return 0;
}

SDL_Window * WindowManager::getWindow()
{
	return window;
}
