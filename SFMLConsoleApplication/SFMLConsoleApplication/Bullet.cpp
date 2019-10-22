#pragma once
#include "Bullet.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

Bullet::Bullet(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId, texture)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	taken = false;
	dirY = 1; //1 == down, -1 == up
};

Bullet::~Bullet()
{
	UnloadGFX();
}

void Bullet::MovementManagement(float deltaTime)
{
	//Move downwards
	//If below bottom while taken == false, coin dies (game ends)

	int _dirY = dirY;

	posY += _dirY * moveSpeed;
	mySprite->setPosition(posX, posY);

	if (posY > (boundryY + radius)) 
	{
		markedDead = true;
	}
}

void Bullet::OnCollision(std::string CollisionId)
{
	//If hit by player, teleport to new position on top of screen
	if (CollisionId == "Player") 
	{
		markedDead = false;
		Teleport();
	}
}


void Bullet::Teleport()
{
	posX = (rand() % (int)(boundryX - (radius / 2)));
	posY = (0 - (radius / 2) - boundryY);
}

void Bullet::Update(float deltaTime)
{
	MovementManagement(deltaTime);
}

