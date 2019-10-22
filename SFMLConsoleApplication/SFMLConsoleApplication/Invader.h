#pragma once
#include "Entity.h"

class Invader : public Entity 
{
public:	
	Invader(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture);
	~Invader();

	void OnCollision(std::string CollisionId) override;
	void Update(float deltaTime) override;

private:
	float moveSpeed;
	int dirY;
	int dirX;
	int boundryX;
	int boundryY;
	void MovementManagement(float deltaTime) override;

};