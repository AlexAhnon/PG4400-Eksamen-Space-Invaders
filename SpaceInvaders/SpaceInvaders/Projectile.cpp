#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(SDL_Renderer* rend, Player player) : Sprite(renderer, "../Artwork/PlayerPro.bmp", 15, 5, player.getX()+22, 485)
{
	renderer = rend;

}


Projectile::~Projectile()
{
}

void Projectile::Update()
{
	rect.y -= 5;
}
