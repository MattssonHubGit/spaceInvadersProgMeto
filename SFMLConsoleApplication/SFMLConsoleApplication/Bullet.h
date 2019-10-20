#pragma once

#include "Entity.h"

class Bullet : public Entity 
{
public: 
	Bullet(int iniX, int iniY, int iniBoundryX, int iniBoundryY, float iniRad, std::string colId, float speed, sf::Texture* texture);
	~Bullet();
	void OnCollision(std::string CollisionId) override;
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	bool taken;

private:
	float moveSpeed;
	int dirY;
	int boundryX;
	int boundryY;
	void MovementManagement() override;
	void ReadyGFX(sf::Texture* texture) override;
	void UnloadGFX() override;
	void Teleport();
};
