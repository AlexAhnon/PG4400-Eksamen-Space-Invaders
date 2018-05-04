#pragma once
#include <SDL.h>
#include "WindowManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"

class Projectile : public Sprite
{
public:
	Projectile();
	Projectile(SDL_Renderer* renderer, Player player);
	Projectile(SDL_Renderer* renderer, Enemy enemy);
	~Projectile();
	
	void Update();

	enum CharacterType {
		playerType,
		enemyType
	};

	CharacterType type;
};

