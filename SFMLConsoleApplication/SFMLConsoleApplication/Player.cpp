#pragma once
#include "Player.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

Player::Player(int iniX, int iniY, int boundX, int boundY, float iniRad, std::string colId, float speed, Texture* texture, Game* game) : Entity(iniX, iniY, iniRad, colId, texture)
{
	moveSpeed = speed;
	boundryX = boundX;
	boundryY = boundY;
	bulletCDCurrnet = 0;
	bulletCDMax = 0.5;
	myGame = game;
	ReadyGFX(texture);
};

Player::~Player() 
{
	UnloadGFX();
}

void Player::OnCollision(std::string CollisionId) 
{
	if (CollisionId == "Invader") 
	{
		markedDead = true;
	}

	if (CollisionId == "InvaderBullet")
	{
		markedDead = true;
	}
}


void Player::MovementManagement(float deltaTime) 
{
	//Input
	int _xInput = 0;
	int _yInput = 0;

		//Horizontal
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		_xInput++;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		_xInput--;
	}

		//Vertical
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		_yInput--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		_yInput++;
	}

	//Output
	posX += (_xInput * moveSpeed) * deltaTime;
	posY += (_yInput * moveSpeed) * deltaTime;

	//Boundries
	if (posX > (boundryX - (radius / 2))) posX = (boundryX - (radius / 2));
	if (posY > (boundryY - (radius / 2))) posY = (boundryY - (radius / 2));
	if (posX < (0 + (radius / 2))) posX = 0 + (radius / 2);
	if (posY < (0 + (radius / 2))) posY = 0 + (radius / 2);

	//Execute
	mySprite->setPosition(posX, posY);
}


void Player::Update(float deltaTime)
{
	MovementManagement(deltaTime);

	if (bulletCDCurrnet <= 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			ShootBullets();
		}
	}
	else 
	{
		bulletCDCurrnet -= deltaTime;
	}

}

void Player::ShootBullets() 
{
	bulletCDCurrnet = bulletCDMax;

	float _bulletSpeed = 350;
	float _bulletRadius = 5;

	Entity* _bulletRight = new Bullet(posX, posY, boundryX, boundryY, _bulletRadius, 0.5, -1, "PlayerBullet", _bulletSpeed, myGame->bulletTexture);
	Entity* _bulletMiddle = new Bullet(posX, posY, boundryX, boundryY, _bulletRadius, 0, -1, "PlayerBullet", _bulletSpeed, myGame->bulletTexture);
	Entity* _bulletLeft = new Bullet(posX, posY, boundryX, boundryY, _bulletRadius, -0.5, -1, "PlayerBullet", _bulletSpeed, myGame->bulletTexture);

	myGame->AddEntity(_bulletRight);
	myGame->AddEntity(_bulletMiddle);
	myGame->AddEntity(_bulletLeft);


}


