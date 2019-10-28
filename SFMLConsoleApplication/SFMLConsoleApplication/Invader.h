#pragma once
#include "Entity.h"

class Invader : public Entity 
{
public:	
	Invader(float iniX, float iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture, sf::Texture* textureExplosion, Game* game);
	~Invader();

	void OnCollision(std::string CollisionId) override;
	void Update(float deltaTime) override;

private:
	float moveSpeed;
	int dirY;
	int dirX;
	int boundryX;
	int boundryY;
	Game* myGame;

	float explosionDuration;
	bool exploded;

	float bulletCDMax;
	float bulletCDCurrent;

	void MovementManagement(float deltaTime) override;
	void ShootBullet();
	sf::Texture* txtExplosion;
};