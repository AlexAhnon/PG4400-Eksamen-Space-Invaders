#pragma once
#include <SDL.h>
#include "WindowManager.h"
#include "Player.h"
#include "Sprite.h"

class Projectile : public Sprite
{
public:
	Projectile();
	Projectile(SDL_Renderer * rend, Player player);
	~Projectile();
	
	void Update();
};

