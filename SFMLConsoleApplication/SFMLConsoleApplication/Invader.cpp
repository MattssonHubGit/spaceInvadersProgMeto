#pragma once
#include "Invader.h"
#include "Bullet.h"

Invader::Invader(float iniX, float iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* textureDefault, sf::Texture* textureExplosion, Game* game) : Entity(iniX, iniY, iniRad, colId, textureDefault)
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
	if (CollisionId == "PlayerBullet")
	{
		CollisionId = "Explosion";
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