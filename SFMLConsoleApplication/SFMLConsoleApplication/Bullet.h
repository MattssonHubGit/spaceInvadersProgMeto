#pragma once

#include "Entity.h"

class Bullet : public Entity 
{
public: 
	Bullet(float iniX, float iniY, int iniBoundryX, int iniBoundryY, float iniRad, float dirX, float dirY, std::string colId, float speed, sf::Texture* texture);
	~Bullet();
	void OnCollision(std::string CollisionId) override;
	void Update(float deltaTime) override;
	bool taken;

private:
	float moveSpeed;
	float dirX;
	float dirY;
	int boundryX;
	int boundryY;
	void MovementManagement(float deltaTime) override;
};
