#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
class Entity;

typedef std::vector<Entity*> EntityVector;


class Game
{
public:
	Game();
	~Game();
	void Run();
	void AddEntity(Entity* entToAdd);

	sf::Texture* bulletTexture;

private:
	bool CheckGameOverState(Entity* plyr);
	void CollisionManagement();
	void InvaderSpawner(float deltaTime);
	void EntityUpdate(float deltaTime);
	void EntityRender();
	void EntityCleaner();
	void WindowsEventManager();
	sf::Texture* LoadTextureFromPath(std::string path);

	sf::Texture* playerTexture;
	sf::Texture* invaderTexture;
	sf::Texture* explosionTexture;

	sf::RenderWindow gameWindow;
	bool gameIsOver;
	float asteroidTimer;

	EntityVector entityList;
};