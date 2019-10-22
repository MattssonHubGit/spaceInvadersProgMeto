#pragma once
#include "Entity.h"

class Player : public Entity 
{
public:
	Player(int iniX, int iniY, int boundX, int boundY, float iniRad, std::string colId, float speed, sf::Texture* texture);
	~Player();
	void OnCollision(std::string CollisionId) override;
	void Update(float deltaTime) override;

private:
	float moveSpeed;
	int boundryX;
	int boundryY;
	void MovementManagement(float deltaTime) override;
};