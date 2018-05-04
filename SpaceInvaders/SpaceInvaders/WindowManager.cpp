#include "WindowManager.h"

// Singleton
WindowManager * WindowManager::instance = NULL;

WindowManager * WindowManager::getInstance() {
	if (!instance)
		instance = new WindowManager();

	return instance;
}

// Release singleton
void WindowManager::Release() {
	delete instance;
	instance = NULL;
}

// Set up the window and initialize all the variables
int WindowManager::SetupWindow()
{
	// Initialize SDL, return error if failed
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}

	// Error checking for window
	if (InitWindow() != 0) {
		std::cerr << "Failed to create window. SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Error checking for renderer
	if (InitRenderer() != 0) {
		std::cerr << "Failed to create renderer. SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Error checking for surface
	if (InitSurface() != 0) {
		std::cerr << "Failed to create surface and textures. SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Error checking for texture
	if (InitTexture() != 0) {
		std::cerr << "Failed to create surface and textures. SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Render it to the screen
	UpdateWindow();

	return 0;
}

// Delete everything
void WindowManager::DeleteWindow()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void WindowManager::UpdateWindow() {
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

// Constructor
WindowManager::WindowManager()
{
	window = nullptr;
}

// Deconstructor
WindowManager::~WindowManager()
{
	DeleteWindow();
}

// Inintalize window
int WindowManager::InitWindow()
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

// Initialize renderer
int WindowManager::InitRenderer()
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

// Initialize surface
int WindowManager::InitSurface()
{
	surface = SDL_LoadBMP(bgImage);

	if (surface == nullptr) {
		return 1;
	}

	return 0;
}

// Initialize texture
int WindowManager::InitTexture()
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr) {
		return 1;
	}

	return 0;
}

// Get and sets for all the variables
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
