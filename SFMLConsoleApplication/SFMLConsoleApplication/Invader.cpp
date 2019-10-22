#pragma once
#include "Invader.h"

Invader::Invader(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture) : Entity(iniX, iniY, iniRad, colId, texture)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	dirY = 1; //1 == down, -1 == up
};

Invader::~Invader() 
{
	UnloadGFX();
}

void Invader::MovementManagement(float deltaTime) 
{
	//Move downwards
	//If below bottom while taken == false, asteroid dies

	int _dirY = dirY;

	posY += _dirY * moveSpeed;
	mySprite->setPosition(posX, posY);

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