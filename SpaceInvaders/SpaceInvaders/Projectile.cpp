#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(SDL_Renderer* renderer, Player player) : Sprite(renderer, "../Artwork/PlayerPro.bmp", 15, 5, player.getX() + 22, player.getY())
{
	type = playerType;
}

Projectile::Projectile(SDL_Renderer* renderer, Enemy enemy) : Sprite(renderer, "../Artwork/EnemyPro.bmp", 15, 5, enemy.getX() + 22, enemy.getY())
{
	type = enemyType;
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	if (type == playerType) {
		rect.y -= 5;
	}
	else if (type == enemyType) {
		rect.y += 3;
	}
}
