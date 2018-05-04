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
	Projectile(SDL_Renderer * rend, Player player);
	Projectile(SDL_Renderer * rend, Enemy enemy);
	~Projectile();
	
	void Update();
private:
	enum character_type {
		_player,
		_enemy
	};
	character_type type;
};

