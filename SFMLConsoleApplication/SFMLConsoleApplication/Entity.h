#pragma once
#include "Game.h"
#include <string>
#include "SFML/Graphics.hpp"

class Entity
{
public: 
	Entity(float iniX, float iniY, float iniRadius, std::string colId, sf::Texture* texture);
	~Entity();
	float posX;
	float posY;
	float radius;
	bool markedDead;
	std::string CollisionId;
	virtual void OnCollision(std::string CollisionId) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow &renderWindow);

protected:
	virtual void MovementManagement(float deltaTime) = 0;
	virtual void ReadyGFX(sf::Texture *texture);
	virtual void UnloadGFX();
	sf::Sprite* mySprite;
};
