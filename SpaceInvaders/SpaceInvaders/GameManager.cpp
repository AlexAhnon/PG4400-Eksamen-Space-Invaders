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
	// HighScore initialization
	scoreText = Text(winManager->getRenderer());
	highScore = 0;

	// Player and enemy class initializations
	player = Player(winManager->getRenderer());

	// Spawn initializations
	player.Draw();

	// Spawning and initializing all enemies
	for (int i = 0; i < enemyRows; i++) {
		for (int j = 0; j < maxEnemyPerRow; j++) {
			enemies.push_back(Enemy(winManager->getRenderer()));
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

bool EnemyHit(Enemy enemy, std::vector<Projectile> &projectiles) {
	for (std::vector<Projectile>::iterator proj = projectiles.begin(); proj != projectiles.end(); proj++) {
		// If projectile hits an enemy, remove enemy and projectile
		if (SDL_HasIntersection(&proj->getRect(), &enemy.getRect())) {
			proj = projectiles.erase(proj);
			return true;
		}
	}

	return false;
}

void GameManager::Update() {
	// Update functions go here
	// Text updates

	// Combine highscore into a const char
	std::string str;
	std::stringstream ss;
	ss << "Score: " << highScore;
	str = ss.str();

	scoreText.Update(str.c_str());


	// Update projectiles
	for (std::vector<Projectile>::iterator proj = projectiles.begin(); proj != projectiles.end();) {
		proj->Update();
		proj->RenderUpdate();

		// Delete projectiles if out of bounds
		if (proj->getY() == 0) {
			proj = projectiles.erase(proj);
		}
		else {
			++proj;
		}	
	}


	// Player update
	player.Update();

	// Window buffer updates
	SDL_UpdateWindowSurface(winManager->getWindow());
	winManager->UpdateWindow();

	// Input update
	inputManager->Update();

	// Projectile update


	// Player and enemy render updates
	player.RenderUpdate();

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].RenderUpdate();
	}

	// Enemy update
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {

		// Update enemy movement
		it->Update();

		// If an enemy reaches the bottom of the screen,  thengame over
		if (it->getY() > 490) {
			gameOver = true;
			std::cout << "You LOST the game! Boo!" << std::endl;
			break;
		}
		// If projectile hits an enemy, remove enemy and projectile
		if (EnemyHit(*it, projectiles) == true) {
			it = enemies.erase(it);
<<<<<<< HEAD
			projectile.Destroy();
			projectile.canShoot = true;
			highScore += 100;
=======
>>>>>>> cf210fe38152301892bd5783c38ec95a8c6b8823
		}
		else {
			++it;
		}
	}

	// Check if all enemies have been defeated
	if (enemies.size() == 0) {
		gameOver = true;
		std::cout << "You WON the game! Hurray!" << std::endl;
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

		// Run Update() function for every frame
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

		// Press Space to shoot
		if (inputManager->KeyDown(SDL_SCANCODE_SPACE)) {
			if (player.can_shoot == true)
			{
				Projectile projectile(Projectile(winManager->getRenderer(), player));
				projectile.Draw();
				projectiles.push_back(projectile);
				player.can_shoot = false;
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
