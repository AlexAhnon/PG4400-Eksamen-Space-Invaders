#pragma once
#include <SDL.h>
#include "WindowManager.h"
#include "InputManager.h"

class GameManager
{
public:
	// Singleton
	static GameManager* getInstance();
	static void Release();

	// Game-loop function
	void Update();

private:
	InputManager* inputManager;
	WindowManager* winManager;

	bool gameOver;
	SDL_Event event;

	static GameManager* instance;

	GameManager();
	~GameManager();
};

