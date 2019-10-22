#pragma once

#include "Entity.h"

class Bullet : public Entity 
{
public: 
	Bullet(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture);
	~Bullet();
	void OnCollision(std::string CollisionId) override;
	void Update(float deltaTime) override;
	bool taken;

private:
	float moveSpeed;
	int dirY;
	int boundryX;
	int boundryY;
	void MovementManagement(float deltaTime) override;
	void Teleport();
};
