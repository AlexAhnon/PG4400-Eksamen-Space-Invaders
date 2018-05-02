// main.cpp : Defines the entry point for the console application.
#include "WindowManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	WindowManager* winManager = WindowManager::getInstance();

	if (winManager->InitializeWindow() != 0) {
		std::cerr << "Failed to create window. SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		winManager->Release();
		return EXIT_FAILURE;
	}

	winManager->Release();

	system("PAUSE");
	return EXIT_SUCCESS;
}