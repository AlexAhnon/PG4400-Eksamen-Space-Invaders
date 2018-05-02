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

int WindowManager::SetupWindow()
{
	// Initialize SDL, return error if failed
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	// Error checking for window
	if (InitializeWindow() != 0) {
		std::cerr << "Failed to create window. SDL_Error: " << SDL_GetError() << std::endl;
		DeleteWindow();
		return EXIT_FAILURE;
	}

	// Error checking for renderer
	if (InitializeRenderer() != 0) {
		std::cerr << "Failed to create renderer. SDL_Error: " << SDL_GetError() << std::endl;
		DeleteWindow();
		return EXIT_FAILURE;
	}

	// Error checking for surface
	if (InitializeSurface() != 0) {
		std::cerr << "Failed to create surface and textures. SDL_Error: " << SDL_GetError() << std::endl;
		DeleteWindow();
		return EXIT_FAILURE;
	}

	// Error checking for texture
	if (InitializeTexture() != 0) {
		std::cerr << "Failed to create surface and textures. SDL_Error: " << SDL_GetError() << std::endl;
		DeleteWindow();
		return EXIT_FAILURE;
	}

	// Render it to the screen
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void WindowManager::DeleteWindow()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

WindowManager::WindowManager()
{
	window = nullptr;
	gameTitle = "Space Invaders";
	screenHeight = 550;
	screenWidth = 500;
	bgImage = "../Artwork/invaders.bmp";
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

int WindowManager::InitializeRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		return 1;
	}

	// Turn renderer background to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	return 0;
}

int WindowManager::InitializeSurface()
{
	surface = SDL_LoadBMP(bgImage);

	if (surface == nullptr) {
		return 1;
	}

	return 0;
}

int WindowManager::InitializeTexture()
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr) {
		return 1;
	}

	return 0;
}

SDL_Window * WindowManager::getWindow()
{
	return window;
}

SDL_Renderer * WindowManager::getRenderer()
{
	return renderer;
}

SDL_Surface * WindowManager::getSurface()
{
	return surface;
}

SDL_Texture * WindowManager::getTexture()
{
	return texture;
}
