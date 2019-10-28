#pragma once
#include "Game.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include "string.h"
#include "Bullet.h"
#include "Player.h"
#include "Invader.h"
#include <iostream>


#pragma region NameSpaces and Settings
using namespace sf;
using namespace std;

//Settings
namespace {
	//Video
	const string WINDOW_TITLE = "Space Invaders";
	const VideoMode VIDEO_MODE = VideoMode((768/2), (1024/2));
	const Color BACKGROUND_COLOR = Color::Black;
	const int FRAMERATE_LIMIT = 60;

	//Radius
	const int PLAYER_RADIUS = 30;
	const int ASTEROID_RADIUS = 15;

	//Player
	const float PLAYER_SPEED_BASE = 200;


	//Asteroids
	const float INVADER_SPEED = 200;
	float invader_spawn_rate = 1;
	const float INVADER_ACCELERATION_RATE = 0.1f;
	const float INVADER_SPAWN_RATE_MAX = 20/2;
}
#pragma endregion

#pragma region HelpFunctions
//Taken from stack overflow, cba to do the math myself
float RandomNumberRange(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}
#pragma endregion


Game::Game() :
	gameWindow(VIDEO_MODE, WINDOW_TITLE, Style::Titlebar | Style::Close),
	playerTexture(LoadTextureFromPath("PlayerTexture.psd")),
	invaderTexture(LoadTextureFromPath("InvaderTexture.psd")),
	bulletTexture(LoadTextureFromPath("BulletTexture.psd")),
	explosionTexture(LoadTextureFromPath("ExplosionTexture.psd")),
	gameIsOver(false),
	entityList(),
	asteroidTimer(0)
{

}

Game::~Game()
{
	//Remove all spawned entites
	while (!entityList.empty()) 
	{
		delete entityList.back();
		entityList.pop_back();
	}

	delete playerTexture;
	delete invaderTexture;
	delete bulletTexture;
	delete explosionTexture;
}
;


void Game::Run() 
{
	//Create essential entities
	Player* player = new Player(VIDEO_MODE.width/2, VIDEO_MODE.height/2, VIDEO_MODE.width, VIDEO_MODE.height, PLAYER_RADIUS, "Player", PLAYER_SPEED_BASE, playerTexture, this);
	//Bullet* bullet = new Bullet(VIDEO_MODE.width / 2, 0, VIDEO_MODE.width, VIDEO_MODE.height, BULLET_RADIUS, "Coin", BULLET_SPEED_BASE, bulletTexture);

	entityList.push_back(player);

	//Ranomizer seed
	srand(std::time(NULL));

	//Frames
	Clock frameClock;
	while (gameWindow.isOpen() && !gameIsOver)
	{
		//Basic functionality
		float deltaTime = frameClock.restart().asSeconds();
		gameWindow.setFramerateLimit(FRAMERATE_LIMIT);
		WindowsEventManager();
		gameWindow.clear(BACKGROUND_COLOR);

#pragma region Debugging
		//---End on F
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			gameIsOver = true;
		}

		//---deltaTime
		//cout << deltaTime << endl;

#pragma endregion




		//Create, handle, draw, and clean
		InvaderSpawner(deltaTime);
		EntityUpdate(deltaTime);
		EntityRender();
		CollisionManagement();
		EntityCleaner();

		gameWindow.display();

		//End game?
		if (CheckGameOverState(player))
		{
			gameIsOver = true;
		}

	}

}

//Load texture from a file at a designated path
Texture* Game::LoadTextureFromPath(string path)
{
	Texture* outputTexture = new Texture();
	if (!outputTexture->loadFromFile(path))
	{
		cout << "Error getting sprite" << endl;
	}
	return outputTexture;
}

//Update entities (OBS - not based on deltaTime)
void Game::EntityUpdate(float deltaTime)
{
	for (EntityVector::size_type i = 0; i < entityList.size(); i++)
	{
		entityList[i]->Update(deltaTime);
	}
}

//Render entities
void Game::EntityRender()
{
	for (EntityVector::size_type i = 0; i < entityList.size(); i++)
	{
		entityList[i]->Render(gameWindow);
	}
}

//Remove entities that have been marked for death
	//ERROR: Removing one causes the list to fuck up for one cycle
void Game::EntityCleaner() 
{
	cout << entityList.size() << ": ";
	for (EntityVector::size_type i = 0; i < entityList.size(); i++) 
	{
		cout << i << " ";
		if (entityList[i]->markedDead)
		{
			delete entityList[i];
			entityList.erase(entityList.begin() + i);
		}
	}
	cout << endl;
}

//Close button
void Game::WindowsEventManager() 
{
	Event closeEvent;
	while (gameWindow.pollEvent(closeEvent))
	{
		if (closeEvent.type == Event::Closed)
		{
			gameWindow.close();
		}
	}
}


void Game::CollisionManagement()
{
	//Checks every entity against every other entity. 
	//If their radius overlaps, call their OnCollision functions...
	//...with their respective CollisionId passed as arguements.
	for (EntityVector::size_type i = 0; i < entityList.size(); i++) 
	{
		for (EntityVector::size_type j = i + 1; j < entityList.size(); j++) 
		{
			//Pythagora
			float dx = (entityList[i]->posX - entityList[j]->posX);
			float dy = (entityList[i]->posY - entityList[j]->posY);
			float distance = powf((dx * dx + dy * dy), 0.5);

			if (distance < (entityList[i]->radius + entityList[j]->radius)) 
			{
				entityList[i]->OnCollision(entityList[j]->CollisionId);
				entityList[j]->OnCollision(entityList[i]->CollisionId);
			}
		}
	}
}

void Game::InvaderSpawner(float deltaTime)
{
	//Spawn as many asteroids/s as the spawn rate allows
	if (asteroidTimer >= (1 / invader_spawn_rate)) 
	{
		//Reset timer
		asteroidTimer = 0;
	
		//Spawn a asteroid above window at random X,Y
		float _spawnPosX = rand() % (VIDEO_MODE.width - ASTEROID_RADIUS) + ASTEROID_RADIUS;
		float _spawnPosY = (0 - ASTEROID_RADIUS) - VIDEO_MODE.height;

		int _boundryX = VIDEO_MODE.width + ASTEROID_RADIUS;
		int _boundryY = VIDEO_MODE.height + ASTEROID_RADIUS;

		float _speed = INVADER_SPEED;

		Invader* _invader = new Invader(_spawnPosX, _spawnPosY, _boundryX, _boundryY, ASTEROID_RADIUS, "Invader", _speed, invaderTexture, explosionTexture, this);


		entityList.push_back(_invader);
	}
	else
	{
		asteroidTimer += deltaTime;
	}

	//Increase spawn rate
	if (invader_spawn_rate <= INVADER_SPAWN_RATE_MAX) invader_spawn_rate += (INVADER_ACCELERATION_RATE * deltaTime);
}

//Returns true if the game should end (player or coin is dead)
bool Game::CheckGameOverState(Entity* plyr) 
{
	bool _output = false;

	if (plyr->markedDead) 
	{
		_output = true;
	}

	return _output;
}

void Game::AddEntity(Entity* entToAdd) 
{
	entityList.push_back(entToAdd);
}
