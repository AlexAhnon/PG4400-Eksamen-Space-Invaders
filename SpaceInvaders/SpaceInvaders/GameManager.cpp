#include "GameManager.h"

// Singleton
GameManager * GameManager::instance = NULL;

GameManager * GameManager::getInstance() {
	if (!instance)
		instance = new GameManager();

	return instance;
}

// Release singleton
void GameManager::Release() {
	delete instance;
	instance = NULL;
}

void GameManager::Initialize() {
	// Player and enemy class initializations
	player = Player(winManager->getRenderer());

	// Spawn initializations
	player.Draw();

	// Spawning and initializing all enemies
	for (int i = 0; i < enemyRows; i++) {
		for (int j = 0; j < maxEnemyPerRow; j++) {
			enemies.push_back(Enemy(winManager->getRenderer()));
			std::cout << "Creating a new enemy." << std::endl;
		}
	}

	int i = 0;
	int xPos = 0;
	int yPos = 0;

	// Iterate through the vector and set correct enemy position, and then draw them
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++, i++) {
		if (i == 0) {
			yPos = 0;
		} else if (i % maxEnemyPerRow == 0) {
			xPos = 0;
			yPos += 40;
		}

		enemies[i].SetPos(xPos, yPos);
		enemies[i].Draw();

		xPos += 40;
	}
}

void GameManager::Update() {
	// Update functions go here

	// Window buffer updates
	SDL_UpdateWindowSurface(winManager->getWindow());
	winManager->UpdateWindow();

	// Input update
	inputManager->Update();

	// Player and enemy updates
	player.RenderUpdate();

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].RenderUpdate();
	}

	// Projectile update
	projectile.RenderUpdate();
	projectile.Update();

	// Enemy hitbox update
	for (int i = 0; i < enemies.size(); i++) {
		if (SDL_HasIntersection(&projectile.getRect(), &enemies[i].getRect())) {
			enemies.erase(enemies.begin() + i);
		}
	}
}

// Game-loop function
void GameManager::Run()
{
	// Initialize spawns and variables
	Initialize();

	while (!gameOver) {
		// FPS regulator, source: https://www.youtube.com/watch?v=jzasDqPmtPI
		// Get frameStart at start of frame
		frameStart = SDL_GetTicks();

		// Update every frame
		Update();

		// Input functions go here
		// Exit controls
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					gameOver = true;
				}
			}
			else if (event.type == SDL_QUIT) {
				gameOver = true;
			}
		}

		// Player controls while making sure sprite can't go out of bounds
		if (inputManager->KeyStillDown(SDL_SCANCODE_A) && player.getX() > 0) {
			player.MoveLeft(3);
		}

		// Minus 50 to account for the width of the player sprite
		if (inputManager->KeyStillDown(SDL_SCANCODE_D) && player.getX() < winManager->screenWidth - 50) {
			player.MoveRight(3);
		}

		if (inputManager->KeyDown(SDL_SCANCODE_SPACE)) {
			if (projectile.can_shoot == true)
			{
				projectile = Projectile(winManager->getRenderer(), player);
				projectile.Draw();
				projectile.can_shoot = false;
			}

			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].MoveDown();
			}
		}

		// Get frameTime at end of frame
		frameTime = SDL_GetTicks() - frameStart;

		// Delay by the difference to regulate FPS
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

// Gets the singleton instances of the other classes and sets up the window
GameManager::GameManager()
{
	inputManager = InputManager::getInstance();
	winManager = WindowManager::getInstance();

	if (winManager->SetupWindow() != 0) {
		Release();
	}
}

// Releases everything once game manager is destroyed
GameManager::~GameManager()
{
	inputManager->Release();
	inputManager = NULL;

	winManager->Release();
	winManager = NULL;
}
