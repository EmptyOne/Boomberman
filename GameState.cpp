// GameState.cpp

#include "stdafx.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "GameState.h"

#include "Playerone.h"
#include "Block.h"
#include "Ball.h"
#include "SolidBlock.h"

#include "Collider.h"
#include "CollisionManager.h"

#include <fstream>


GameState::GameState(System& system)
{
	m_systems = system;

	std::string filename = "../assets/main.png";
	std::string txtname = "../assets/Map.txt";



	Sprite* sprite;
	
	/*
	sprite = m_systems.sprite_manager->CreateSprite(
		filename, 66, 0, 64, 64);
	Ball* ball = new Ball(sprite,
		m_systems.width,
		m_systems.height,
		m_systems.width / 2 - 8, 
		m_systems.height - 68 - 16);
	m_entities.push_back(ball);*/

	// hard coded block coordinates
	SDL_Rect blockCoords[] 
	{
		{ 0,  0, 64, 64 }, // Breakable
		{ 66,  0, 64, 64 }, // Solid
		{ 0, 0, 0, 0}, // Non-visible
		{ 132, 0, 64, 64}, // Background

	};

	// create all blocks for level
	
	//variabler som är hur många blocks vi ska ha i x och y led.
	//int xNumBlocks = m_systems.width / (64 + padding);
	const int xNumBlocks = 15;
	const int yNumBlocks = 13;

	//märkte att denna rad används typ inte 
	//int NumBlocks[xNumBlocks][yNumBlocks];

	
	//padding är onödig för oss. de den gör är mellan rum mellan blocks.
	//int xOffset = (m_systems.width % (64 + padding) / 2);
	//dom här variablerna är var någonstans på skärmen de ska börja skriva ut.
	int xOffset = 120;
	int yOffset = 0;
	
	

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

					//block
					sprite = m_systems.sprite_manager->CreateSprite(filename, rect.x, rect.y, rect.w, rect.h);
					Block* block = new Block(sprite, xOffset + x * 64, yOffset + y * 64);
					m_entities.push_back(block);

					// jag kommer lägga till en klass för background
					// då kommer de bli nice tror jag 
	
					//bakground
					sprite = m_systems.sprite_manager->CreateSprite(filename, rect.x, rect.y, rect.w, rect.h);
					SolidBlock* solidblock = new SolidBlock(sprite, xOffset + x * 64, yOffset + y * 64);
					m_entities.push_back(solidblock);

					
					
					if (x % 2 == 1 && y % 2 == 1){

						// solidblock					
						sprite = m_systems.sprite_manager->CreateSprite(filename, rect.x, rect.y, rect.w, rect.h);
						SolidBlock* solidblock = new SolidBlock(sprite, xOffset + x * 64, yOffset + y * 64);
						m_entities.push_back(solidblock);
					}
				
				}
			}
		}
	}

	
	int playerx = 120;
	int playery = 0;

	sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 66, 64, 64);

	Playerone* playerone = new Playerone(sprite, playerx , playery);
	playerx = playerone->GetX();
	playery = playerone->GetY();


	m_entities.push_back(playerone);



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

	// här har jag försökt göra movment
	// jag kollade på tommis movment under och försökte få den att bli lika dan typ

	// de andra nya sakerna är paddle är nu playerone 
	// och lite små grejer bara

	for (unsigned int i = 0; i < m_entities.size(); i++){

		if (!m_entities[i]->IsVisible())
			continue;

		// update
		m_entities[i]->Update(deltatime);

		if (m_entities[i]->GetType() == ENTITY_PLAYERONE)
		{

			Playerone* playerone = static_cast<Playerone*>(m_entities[0]);

			

				Keyboard* keyboard = m_systems.input_manager->GetKeyboard();
				if (keyboard->IsKeyDown(SDLK_s)){

					float PlayeronePosY = playerone->GetY();
					playerone->GetY() + 64;
				}
				else if (keyboard->IsKeyDown(SDLK_w)){

					float PlayeronePosY = playerone->GetY();
					PlayeronePosY - 64;
				}
				else if (keyboard->IsKeyDown(SDLK_a)){

					float PlayeronePosX = playerone->GetX();
					PlayeronePosX - 64;
				}
				else if (keyboard->IsKeyDown(SDLK_d)){

					float PlayeronePosX = playerone->GetX();
					PlayeronePosX + 64;
				}
			}
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
	}
	*/


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

	/*
<<<<<<< HEAD
=======
*/

	/*
>>>>>>> origin/master
	Playerone* Playerone = static_cast<Playerone*>(m_entities[0]);
	Ball* ball = static_cast<Ball*>(m_entities[1]);

	int overlapX = 0, overlapY = 0;
	if (CollisionManager::Check(Playerone->GetCollider(), Playerone->GetCollider(), overlapX, overlapY))
	{
		if (overlapX != 0)
			ball->InvertDirectionX();
		if (overlapY != 0)
			ball->InvertDirectionY();

		ball->SetPosition(ball->GetX() + overlapX, ball->GetY() + overlapY);
	}
	else
	{
		for (unsigned int i = 2; i < m_entities.size(); i++)
		{
			Block* block = static_cast<Block*>(m_entities[i]);
			if (!block->IsVisible())
				continue;

			if (CollisionManager::Check(block->GetCollider(), Playerone->GetCollider(), overlapX, overlapY))
			{
				block->SetInvisible();

				if (overlapX != 0)
					ball->InvertDirectionX();
				if (overlapY != 0)
					ball->InvertDirectionY();

				ball->SetPosition(ball->GetX() + overlapX, ball->GetY() + overlapY);
			}
		}
	}
<<<<<<< HEAD
=======
	*/

	/*
>>>>>>> origin/master
	*/
}
