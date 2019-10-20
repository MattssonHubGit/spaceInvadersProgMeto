#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <vector>
#include "Player.h"
#include "Bullet.h"

typedef std::vector<Entity*> EntityVector;

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	bool CheckGameOverState(Player* plyr, Bullet* cn);
	void CollisionManagement();
	void InvaderSpawner(float deltaTime);
	void EntityUpdate();
	void EntityRender();
	void EntityCleaner();
	void WindowsEventManager();
	sf::Texture* LoadTextureFromPath(std::string path);

	sf::Texture* playerTexture;
	sf::Texture* invaderTexture;
	sf::Texture* bulletTexture;

	sf::RenderWindow gameWindow;
	bool gameIsOver;
	float asteroidTimer;

	EntityVector entityList;
};