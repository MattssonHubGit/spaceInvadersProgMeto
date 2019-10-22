#pragma once
#include "Invader.h"

Invader::Invader(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId, texture)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	dirY = 1; //1 == down, -1 == up
	dirX = 1; //1 == right, -1 == left
};

Invader::~Invader() 
{
	UnloadGFX();
}

void Invader::MovementManagement(float deltaTime) 
{
	//Move downwards
	//If touch side, invert dirX
	//If below bottom, invader dies

	int _dirY = dirY;

	//Sides
	if (posX > (boundryX + (radius / 2))) dirX = -1;
	if (posX < 0 + (radius / 2)) dirX = 1;

	int _dirX = dirX;

	//Apply movement
	posY += (_dirY * moveSpeed) * deltaTime;
	posX += (_dirX * moveSpeed) * deltaTime;
	mySprite->setPosition(posX, posY);

	//Check below screen
	if (posY > (boundryY + (radius / 2)))
	{
		markedDead = true;
	}
}

void Invader::Update(float deltaTime)
{
	MovementManagement(deltaTime);
}


void Invader::OnCollision(std::string CollisionId) 
{

}