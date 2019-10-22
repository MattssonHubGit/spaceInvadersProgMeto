#include "Entity.h"
#include "SFML/Graphics.hpp"

using namespace sf;


Entity::Entity(int iniX, int iniY, float iniRadius, std::string colId, sf::Texture* texture) :
	posX(iniX),
	posY(iniY),
	radius(iniRadius),
	CollisionId(colId),
	markedDead(false)
{
	ReadyGFX(texture);
};

Entity::~Entity() 
{

};

void Entity::ReadyGFX(sf::Texture* texture)
{
	//Set up a sprite with the provided texture and center it's origin

	mySprite = new Sprite();
	mySprite->setTexture(*texture);

	float centerX = (mySprite->getLocalBounds().width / 2);
	float centerY = (mySprite->getLocalBounds().height / 2);

	mySprite->setOrigin(centerX, centerY);
}

void Entity::Render(RenderWindow& renderWindow)
{
	renderWindow.draw(*mySprite);
}

void Entity::UnloadGFX()
{
	delete mySprite;
}