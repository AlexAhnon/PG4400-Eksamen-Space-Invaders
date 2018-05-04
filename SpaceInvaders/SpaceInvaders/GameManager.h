#pragma once
#include <SDL.h>
#include <SDL_timer.h>
#include <vector>
#include <memory>
#include <iostream>

#include "WindowManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

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
	Projectile projectile;

	std::vector<Enemy> enemies;
	int maxEnemyPerRow = 10;
	int enemyRows = 2;

	std::vector<Projectile> projectiles;

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

