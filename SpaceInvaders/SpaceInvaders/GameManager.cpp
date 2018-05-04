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
	// Initialize random seed based on time
	std::srand(std::time(nullptr));

	// HighScore initialization
	scoreText = Text(winManager->getRenderer(), 340, 520, 34, 150);
	highScore = 0;

	// Player Health text initilization
	playerHealthText = Text(winManager->getRenderer(), 10, 520, 34, 150);

	// Player initializations
	player = Player(winManager->getRenderer());
	player.Draw();

	// Spawn and initialize shields
	Shield shield = Shield(winManager->getRenderer(), 80, 20, 450);
	shield.Draw();
	shields.push_back(shield);

	shield = Shield(winManager->getRenderer(), 80, 150, 450);
	shield.Draw();
	shields.push_back(shield);

	shield = Shield(winManager->getRenderer(), 80, 280, 450);
	shield.Draw();
	shields.push_back(shield);

	shield = Shield(winManager->getRenderer(), 80, 410, 450);
	shield.Draw();
	shields.push_back(shield);

	// Spawn first wave of enemies
	SpawnEnemyWave(1);
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

	// Reset and reuse stringstream for player health text
	ss.str("");
	ss.clear();
	ss << "Hitpoints: " << player.hitpoints;
	str = ss.str();

	playerHealthText.Update(str.c_str());

	// Shields decrease in width if they take damage
	for (std::vector<Shield>::iterator it = shields.begin(); it != shields.end(); it++) {
		if (OnHitCollision(it->getRect(), playerProjectiles) == true || OnHitCollision(it->getRect(), enemyProjectiles) == true) {
			it->TakeDamage();
		}

		it->RenderUpdate();
	}

	// Update player-projectiles
	for (std::vector<Projectile>::iterator proj = playerProjectiles.begin(); proj != playerProjectiles.end();) {
		proj->Update();
		proj->RenderUpdate();

		// Delete projectiles if out of bounds
		if (proj->getY() < 0) {
			proj = playerProjectiles.erase(proj);
		}
		else {
			++proj;
		}	
	}

	// Update enemy-projectiles
	for (std::vector<Projectile>::iterator proj = enemyProjectiles.begin(); proj != enemyProjectiles.end();) {
		proj->Update();
		proj->RenderUpdate();

		// Delete projectiles if out of bounds
		if (proj->getY() > 550) {
			proj = enemyProjectiles.erase(proj);
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

	// Player and enemy render updates
	player.RenderUpdate();

	// Player takes damage if hit by an enemy projectile
	if (OnHitCollision(player.getRect(), enemyProjectiles) == true) {
		player.hitpoints--;
	}

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].RenderUpdate();
	}

	// Enemy update
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();) {

		// Update enemy movement
		it->Update();

		// Random seed to determine if the enemy can shoot
		int random = 1 + (std::rand() % 1000);

		// If conditions are met and enemy can shoot, then create projectile
		if (random <= 2 && it->canShoot == true) {
			// Enemies shooting projectiles and adding to enemy_projectiles vector
			Projectile projectile(Projectile(winManager->getRenderer(), *it));
			projectile.Draw();
			enemyProjectiles.push_back(projectile);
		}

		// If an enemy reaches the bottom of the screen,  thengame over
		if(it->getY() > 490) {
			gameOver = true;
			std::cout << "You LOST the game! Boo!" << std::endl;
			std::cout << "Your highscore was: " << highScore << " points." << std::endl;
			break;
		}
		// If projectile hits an enemy, remove enemy and projectile
		if(OnHitCollision(it->getRect(), playerProjectiles) == true) {
			it = enemies.erase(it);
			highScore += 100;
		}
		else {
			++it;
		}
	}

	// Winning and losing conditions, reset shields if going to next wave
	if (enemies.size() == 0 && enemyWaveNumber == 1) {
		std::cout << "You beat the first wave of enemies!" << std::endl;
		for (std::vector<Shield>::iterator it = shields.begin(); it != shields.end(); it++) {
			it->Reset();
		}
		SpawnEnemyWave(2);
	}
	else if (enemies.size() == 0 && enemyWaveNumber == 2) {
		std::cout << "You beat the second wave of enemies!" << std::endl;
		for (std::vector<Shield>::iterator it = shields.begin(); it != shields.end(); it++) {
			it->Reset();
		}
		SpawnEnemyWave(3);
	}
	else if (enemies.size() == 0 && enemyWaveNumber == 3) {
		gameOver = true;
		std::cout << "You WON the game! Hurray!" << std::endl;
		std::cout << "Your highscore was: " << highScore << " points." << std::endl;
	}
	else if (player.hitpoints == 0) {
		gameOver = true;
		std::cout << "You LOST the game! Boo!" << std::endl;
		std::cout << "Your highscore was: " << highScore << " points." << std::endl;
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
			if (player.canShoot == true)
			{
				Projectile projectile(Projectile(winManager->getRenderer(), player));
				projectile.Draw();
				playerProjectiles.push_back(projectile);
				player.canShoot = false;
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

void GameManager::SpawnEnemyWave(int level) {
	// Spawning and initializing all enemies

	int rowsOfEnemies;
	int maxPerRow = 10;

	// Spawns more enemies depending on level, adjust difficult and amount of enemies here
	if (level == 1) {
		enemyWaveNumber = 1;
		rowsOfEnemies = 2;
	}
	else if (level == 2) {
		enemyWaveNumber = 2;
		rowsOfEnemies = 3;
	}
	else if (level == 3) {
		enemyWaveNumber = 3;
		rowsOfEnemies = 4;
	}

	for (int i = 0; i < rowsOfEnemies; i++) {
		for (int j = 0; j < maxPerRow; j++) {
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
		}
		else if (i % maxPerRow == 0) {
			xPos = 0;
			yPos += 40;
		}

		enemies[i].SetPos(xPos, yPos);
		enemies[i].Draw();

		xPos += 40;
	}
}

// Checks for collision between an object and a projectile
bool GameManager::OnHitCollision(SDL_Rect rect, std::vector<Projectile>& projectiles) {
	for (std::vector<Projectile>::iterator proj = projectiles.begin(); proj != projectiles.end(); proj++) {
		// If projectile hits an enemy, remove enemy and projectile
		if (SDL_HasIntersection(&proj->getRect(), &rect)) {
			proj = projectiles.erase(proj);
			return true;
		}
	}

	return false;
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
	enemies.clear();

	playerProjectiles.clear();
	enemyProjectiles.clear();

	shields.clear();

	inputManager->Release();
	inputManager = NULL;

	winManager->Release();
	winManager = NULL;
}
