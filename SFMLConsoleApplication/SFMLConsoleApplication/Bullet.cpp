#pragma once
#include "Bullet.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

Bullet::Bullet(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, float iniDirX, float iniDirY, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId, texture)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	taken = false;
	dirX = iniDirX;
	dirY = iniDirY;
};

Bullet::~Bullet()
{
	UnloadGFX();
}

void Bullet::MovementManagement(float deltaTime)
{
	//Move downwards
	//If below bottom while taken == false, coin dies (game ends)

	float _dirY = dirY;
	float _dirX = dirX;

	posY += (_dirY * moveSpeed) * deltaTime;
	posX += (_dirX * moveSpeed) * deltaTime;

	mySprite->setPosition(posX, posY);

	if (posY > (boundryY + radius)) 
	{
		markedDead = true;
	}

	if (posY < (0 + radius))
	{
		markedDead = true;
	}
}

void Bullet::OnCollision(std::string CollisionId)
{
	if (this->myCollisionID == "PlayerBullet" && CollisionId == "Invader")
	{
		markedDead = true;
	}	
	
	if (this->myCollisionID == "InvaderBullet" && CollisionId == "Player")
	{
		markedDead = true;
	}
}

void Bullet::Update(float deltaTime)
{
	MovementManagement(deltaTime);
}

