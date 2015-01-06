// GameState.cpp

#include "stdafx.h"
#include "GameState.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include "Playerone.h"
#include "Block.h"
#include "Bomb.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "SoundManager.h"
#include "SoundClip.h"

#include <fstream>


GameState::GameState(System& system)
{
	m_systems = system;

	std::string filename = "../assets/main.png";
	std::string kartan = "../assets/MAP.png";
	std::string txtname = "../assets/Map.txt";
	std::string soundname = "../assets/BOOM_MUSIC.wav";

	Sprite* sprite;

	//map

	//variabler som är hur många blocks vi ska ha i x och y led.

	const int xNumBlocks = 15;
	const int yNumBlocks = 13;

	// varnågonstans spelplanen börjar ritas ut
	int xOffset = 120;
	int yOffset = 0;

	// hard coded block coordinates
	SDL_Rect blockCoords[]
	{
		{ 0, 0, 64, 64 }, // Breakable 0
		{ 66, 0, 64, 64 }, // Solid 1 
		{ 0, 0, 0, 0 }, // Non-visible 2
		{ 132, 0, 64, 64 }, // Background 3

	};

	//background 
	sprite = m_systems.sprite_manager->CreateSprite(kartan, 0, 0, 1080 - xOffset, 832);
	Block* backgroundBlock = new Block(sprite, xOffset, yOffset);
	backgroundBlock->SetType(1);

	m_entities.push_back(backgroundBlock);


	std::ifstream stream;
	stream.open(txtname);
	if (stream.is_open()){

		std::string line;

		while (!stream.eof()){

			int count;
			for (int y = 0; y < yNumBlocks; y++){

				for (int x = 0; x < xNumBlocks; x++){

					stream >> count;
					//den här raden skriver ut allt atm 
					SDL_Rect& rect = blockCoords[count];

					if (x % 2 == 1 && y % 2 == 1){

						// solidblock					
						sprite = m_systems.sprite_manager->CreateSprite(filename, rect.x, rect.y, rect.w, rect.h);
						Block* solidblock = new Block(sprite, xOffset + x * 64, yOffset + y * 64);
						solidblock->SetType(2);
				
						m_entities.push_back(solidblock);
					
						continue;
					}
					else
					{
		
						if (count == 0)
						{
							//breakableblock
							rect = blockCoords[0];
							sprite = m_systems.sprite_manager->CreateSprite(filename, rect.x, rect.y, rect.w, rect.h);
							Block* breakableBlock = new Block(sprite, xOffset + x * 64, yOffset + y * 64);
					
					
							m_entities.push_back(breakableBlock);
						}
					}
				}
			}
		}
	}



	//player
	int playerx = 120;
	int playery = 0;

	sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 66, 64, 64);

	Playerone* playerone = new Playerone(m_systems.input_manager->GetKeyboard(), sprite, playerx, playery);
	playerx = playerone->GetX();
	playery = playerone->GetY();

	m_entities.push_back(playerone);


	//musik
	SoundClip* music = m_systems.sound_manager->CreateSoundClip(soundname);
	music->Play();


	sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 130, 64, 64);
	Bomb* bomb = new Bomb(sprite, 64, 64, playerx, playery);


	m_entities.push_back(bomb);


	m_active = false;
}

GameState::~GameState()
{
	int c = 0;
	auto it = m_entities.begin();
	while (it != m_entities.end())
	{
		Sprite* sprite = (*it)->GetSprite();
		if (sprite)
			m_systems.sprite_manager->DestroySprite(sprite);
		delete (*it);
		++it;
		c++;
	}
	m_entities.clear();
}

bool GameState::Update(float deltatime)
{

	for (unsigned int i = 0; i < m_entities.size(); i++){


		if (!m_entities[i]->IsVisible())
			continue;

		// update
		m_entities[i]->Update(deltatime);


	}


	// tommis update jag antar att de här här saker rör sig så jag sparar den så kan vi kolla om de behövs

	/*
	// update all entities
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
	if (!m_entities[i]->IsVisible())
	continue;

	// update
	m_entities[i]->Update(deltatime);

	// note(tommi): special treatment for the ball
	if (m_entities[i]->GetType() == ENTITY_BALL)
	{
	// note(tommi): we static_cast the ball from entity
	//   to ball we know that it is a ball since
	//   we check for entity type
	Ball* ball = static_cast<Ball*>(m_entities[i]);

	if (!ball->IsActive() && m_active)
	{
	// reset the game
	m_active = false;
	}
	else if (!ball->IsActive())
	{
	// here the ball follows the Playerone
	// note(tommi): we can do this because we always
	//   add the Playerone first in the vector of entities


	Playerone* playerone = static_cast<Playerone*>(m_entities[0]);

	float PlayeroneHalfWidth = playerone->GetSprite()->GetRegion()->w * 0.5f;
	float PlayeroneHalfHeight = playerone->GetSprite()->GetRegion()->h * 0.5f;

	float PlayeronePosX = playerone->GetX();
	float PlayeronePosY = playerone->GetY();

	float ballHalfWidth = ball->GetSprite()->GetRegion()->w	* 0.5f;
	float ballHalfHeight = ball->GetSprite()->GetRegion()->h	* 0.5f;

	float ballNewX = PlayeronePosX + PlayeroneHalfWidth - ballHalfWidth;
	float ballNewY = PlayeronePosY - PlayeroneHalfHeight - ballHalfHeight;

	ball->SetPosition(ballNewX, ballNewY);

	Mouse* mouse = m_systems.input_manager->GetMouse();
	if (mouse->IsButtonDown(0) && !m_active)
	{
	ball->Activate();
	m_active = true;
	}

	}
	}
	}*/



	// we always do collision checking after updating 
	// positions et al in entities

	CollisionChecking();

	return true;
}

void GameState::Draw()
{
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		Sprite* sprite = m_entities[i]->GetSprite();
		if (sprite)
		{
			m_systems.draw_manager->Draw(sprite,
				m_entities[i]->GetX(),
				m_entities[i]->GetY());
		}
	}
}

State* GameState::NextState()
{
	return nullptr;
}


// private
void GameState::CollisionChecking()
{

	int overlapX = 0, overlapY = 0;

	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		Entity* a = m_entities[i];

		for (unsigned int j = 0; j < m_entities.size(); j++)
		{
			if (i == j)
				continue;

			Entity* b = m_entities[j];

			EEntityType aType = a->GetType();
			EEntityType bType = b->GetType();

			if (aType == ENTITY_PLAYERONE)
			{
				
				Playerone* playerone = static_cast<Playerone*>(a);

				if (bType == ENTITY_SOLIDBLOCK)
				{

					Block* solidblock = static_cast<Block*>(b);

					if (CollisionManager::Check(playerone->GetCollider(), solidblock->GetCollider(), overlapX, overlapY))
					{
						std::cout << "Collision" << std::endl;

						//collison funkar meeeeeeeeeen
						//jag vet inte hur vi ska göra för att
						//player "inte" ska kunna gå till blocksen

					}
				}
				else if (bType == ENTITY_BLOCK){


					Block* block = static_cast<Block*>(b);

					if (CollisionManager::Check(playerone->GetCollider(), block->GetCollider(), overlapX, overlapY))
					{
						std::cout << "Collision" << std::endl;

						//collison funkar meeeeeeeeeen
						//jag vet inte hur vi ska göra för att
						//player "inte" ska kunna gå till blocksen

					}
				}
			}
		}
	}
}