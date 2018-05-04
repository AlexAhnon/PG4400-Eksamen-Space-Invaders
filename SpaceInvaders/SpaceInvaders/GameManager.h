#pragma once
#include <SDL.h>
#include <SDL_timer.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "WindowManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Shield.h"
#include "Text.h"

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
	void SpawnEnemyWave(int level);
	bool OnHitCollision(SDL_Rect rect, std::vector<Projectile> &projectiles);

	InputManager* inputManager;
	WindowManager* winManager;
	Player player;

	int enemyWaveNumber;
	std::vector<Enemy> enemies;

	std::vector<Projectile> playerProjectiles;
	std::vector<Projectile> enemyProjectiles;

	std::vector<Shield> shields;

	bool gameOver = false;
	SDL_Event event;

	static GameManager* instance;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Text scoreText;
	int highScore;

	Text playerHealthText;

	GameManager();
	~GameManager();
};

