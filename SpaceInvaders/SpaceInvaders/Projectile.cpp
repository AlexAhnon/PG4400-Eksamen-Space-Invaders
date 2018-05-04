#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(SDL_Renderer* rend, Player player) : Sprite(renderer, "../Artwork/PlayerPro.bmp", 15, 5, player.getX()+22, player.getY())
{
	renderer = rend;
	type = _player;
}

Projectile::Projectile(SDL_Renderer* rend, Enemy enemy) : Sprite(renderer, "../Artwork/PlayerPro.bmp", 15, 5, enemy.getX() + 22, enemy.getY())
{
	renderer = rend;
	type = _enemy;
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	if (type == _player) {
		rect.y -= 5;
	}
	else if (type == _enemy) {
		rect.y += 5;
	}
}
