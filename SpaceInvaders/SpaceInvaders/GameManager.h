#pragma once
#include <SDL.h>
#include "WindowManager.h"
#include "InputManager.h"
#include "Player.h"
#include <SDL_timer.h>

class GameManager
{
public:
	// Singleton
	static GameManager* getInstance();
	static void Release();

	// Game-loop function
	void Initialize();
	void Update();
	void Run();

private:
	InputManager* inputManager;
	WindowManager* winManager;
	Player player;

	bool gameOver = false;
	SDL_Event event;

	static GameManager* instance;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	GameManager();
	~GameManager();
};

