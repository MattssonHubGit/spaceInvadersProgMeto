#pragma once
#include "Invader.h"
#include "Bullet.h"
#include <iostream>

Invader::Invader(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* textureDefault, sf::Texture* textureExplosion, Game* game) : Entity(iniX, iniY, iniRad, colId, textureDefault)
{
	moveSpeed = speed;
	boundryX = iniBoundryX;
	boundryY = iniBoundryY;
	dirY = 1; //1 == down, -1 == up
	dirX = 1; //1 == right, -1 == left
	explosionDuration = 0.1;
	exploded = false;
	txtExplosion = textureExplosion;
	myGame = game;

	bulletCDMax = 1;
	bulletCDCurrent = 0;

};

Invader::~Invader() 
{
	UnloadGFX();
	delete txtExplosion;
	std::cout << "deallocated" << std::endl;
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
	std::cout << posX << ", " << posY << std::endl;
	mySprite->setPosition(posX, posY);

	//Check below screen
	if ((posY > (boundryY + (radius / 2))) && myCollisionID != "Exploded")
	{
		std::cout << "Below screen" << std::endl;
		markedDead = true;
	}
}

void Invader::Update(float deltaTime)
{
	MovementManagement(deltaTime);

	//Fire bullet on cd
	if (bulletCDCurrent <= 0)
	{
		ShootBullet();	
	}
	else
	{
		bulletCDCurrent -= deltaTime;
	}

	//If exploded, remove after timer
	if (exploded)
	{
		std::cout << "EXPLODED!" << std::endl;

		if (explosionDuration <= 0)
		{
			markedDead = true;
		}
		else
		{
			explosionDuration -= deltaTime;
		}
	}
}


void Invader::OnCollision(std::string CollisionId) 
{

	std::cout << CollisionId << std::endl;

	if (CollisionId == "PlayerBullet")
	{
		//std::cout << "Entered explosion state" << std::endl;
		myCollisionID = "Explosion";
		moveSpeed = 0;
		exploded = true;
		ReadyGFX(txtExplosion);
	}
}

void Invader::ShootBullet()
{
	bulletCDCurrent = bulletCDMax;

	float _bulletSpeed = 350;
	float _bulletRadius = 5;

	Entity* _bullet = new Bullet(posX, posY, boundryX, boundryY, _bulletRadius, 0, 1, "InvaderBullet", _bulletSpeed, myGame->bulletTexture);

	myGame->AddEntity(_bullet);


}