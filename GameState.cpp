// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "EndState.h"
#include "MenuState.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include "Playerone.h"
#include "Block.h"
#include "Bomb.h"
#include "Playertwo.h"
#include "Explosion.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "SoundManager.h"
#include "SoundClip.h"

#include "UI.h"

#include <fstream>
#include <iostream>


GameState::GameState(System& system)
{
	m_systems = system;

	std::string filename = "../assets/main.png";
	std::string kartan = "../assets/MAP.png";
	std::string txtname = "../assets/Map.txt";
	std::string soundname = "../assets/BOOM_MUSIC.wav";
	std::string UIimg = "../assets/UI.png";
	std::string liv = "../assets/playeronedeath.png";

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
	
	//UI
	sprite = m_systems.sprite_manager->CreateSprite(UIimg, 0, 0, 120, 832);
	UI* ui = new UI(sprite, 0,0);
	ui->SetType(1);
	m_entities.push_back(ui);

	//liv i UI
	sprite = m_systems.sprite_manager->CreateSprite(liv, 0, 0, 32, 32);
	UI* uiliv = new UI(sprite, 9, 169);
	uiliv->SetType(2);
	m_entities.push_back(uiliv);

	sprite = m_systems.sprite_manager->CreateSprite(liv, 0, 0, 32, 32);
	UI* uiliv2 = new UI(sprite, 44, 169);
	uiliv->SetType(2);
	m_entities.push_back(uiliv2);

	sprite = m_systems.sprite_manager->CreateSprite(liv, 0, 0, 32, 32);
	UI* m_liv3 = new UI(sprite, 79, 169);
	uiliv->SetType(2);
	m_entities.push_back(m_liv3);


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
					
					if (count == 1){

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


	//playerone

	int playeronex = 120;
	int playeroney = 0;

	//bomb
	sprite = m_systems.sprite_manager->CreateSprite(filename, 0, 66, 64, 64);
	Sprite* bombSprite = m_systems.sprite_manager->CreateSprite(filename, 0, 130, 64, 64);


	m_player = new Playerone(m_systems.input_manager->GetKeyboard(), sprite, bombSprite, &m_entities, playeronex, playeroney);
	playeronex = m_player->GetX();
	playeroney = m_player->GetY();

	m_entities.push_back(m_player);


	//playertwo
	
	int playertwox = 1016;
	int playertwoy = 768;
	sprite = m_systems.sprite_manager->CreateSprite(filename, 66, 66, 64, 64);


	Playertwo* playertwo = new Playertwo(m_systems.input_manager->GetKeyboard(), sprite, playertwox, playertwoy);
	playertwox = playertwo->GetX();
	playertwoy = playertwo->GetY();

	m_entities.push_back(playertwo);

	//musik
	SoundClip* music = m_systems.sound_manager->CreateSoundClip(soundname);
	music->Play();



	//explosion
	sprite = m_systems.sprite_manager->CreateSprite(filename, 66, 130, 64, 64);
	Sprite* explosionSprite = m_systems.sprite_manager->CreateSprite(filename, 130, 66, 64, 64);
	


	

	
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

		/*Entity* a = m_entities[i];
		EEntityType aType = a->GetType();
		if (aType == ENTITY_PLAYERONE){
		Playerone* playerone = static_cast<Playerone*>(a);
		playerone->BombIncrease();
		}*/

		if (!m_entities[i]->IsActive())
		{

			//	m_player->BombIncrease();


			if (m_entities[i]->GetType() == ENTITY_BOMB)
			{

				//std::cout << "ent bomb: " << std::endl;
				Sprite* spr;
				spr = m_systems.sprite_manager->CreateSprite("../assets/main.png", 0, 198, 64, 64);
				m_bombX = m_entities[i]->GetX();
				m_bombY = m_entities[i]->GetY();

				Explosion* explosion = new Explosion(spr, m_bombX - 1, m_bombY - 1);
				m_entities.push_back(explosion);


				//Y

				spr = m_systems.sprite_manager->CreateSprite("../assets/main.png", 66, 130, 64, 64);

				explosion = new Explosion(spr, m_bombX - 1, m_bombY + 64 - 1);
				m_entities.push_back(explosion);

				explosion = new Explosion(spr, m_bombX - 1, m_bombY - 64 - 1);
				m_entities.push_back(explosion);

				explosion = new Explosion(spr, m_bombX - 1, m_bombY + 128 - 1);
				m_entities.push_back(explosion);

				explosion = new Explosion(spr, m_bombX - 1, m_bombY - 128 - 1);
				m_entities.push_back(explosion);


				//X
				spr = m_systems.sprite_manager->CreateSprite("../assets/main.png", 130, 130, 64, 64);
				if (m_bombX - 1 > 120)
				{
					explosion = new Explosion(spr, m_bombX - 128 - 1, m_bombY - 1);
					m_entities.push_back(explosion);

					explosion = new Explosion(spr, m_bombX - 64 - 1, m_bombY - 1);
					m_entities.push_back(explosion);
				}
				explosion = new Explosion(spr, m_bombX + 64 - 1, m_bombY - 1);
				m_entities.push_back(explosion);



				explosion = new Explosion(spr, m_bombX + 128 - 1, m_bombY - 1);
				m_entities.push_back(explosion);


				m_player->BombIncrease();
				m_bombTimer = explosion->GetTimer();
				//std::cout << m_bombTimer << std::endl;

				delete m_entities[i];
				m_entities.erase(m_entities.begin() + i);
			}

			if (m_entities[i]->GetType() == ENTITY_EXPLOSION && m_entities[i]->IsActive() == false)
			{
				delete m_entities[i];
				m_entities.erase(m_entities.begin() + i);
			}





			////if (m_entities[38])
			//if (aType == ENTITY_BOMB)
			//{
			//	//	Playerone* playerone = static_cast<Playerone*>(m_entities[i]);
			//}

			continue;

		}

		// update
		m_entities[i]->Update(deltatime);




		// we always do collision checking after updating 
		// positions et al in entities

	}
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
	
	return new MenuState(m_systems);
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

			if (aType == ENTITY_PLAYERONE) //|| aType == ENTITY_PLAYERTWO)
			{
				Keyboard* keyboard = new Keyboard;


				Playerone* playerone = static_cast<Playerone*>(a);

				float px;
				float py;
				float pd;
				px = playerone->GetX();
				py = playerone->GetY();
				pd = playerone->GetDir();
			



			if (bType == ENTITY_SOLIDBLOCK || bType == ENTITY_BLOCK)
			{

				Block* solidblock = static_cast<Block*>(b);

				if (!solidblock->IsVisible())
					continue;
				if (CollisionManager::Check(playerone->GetCollider(), solidblock->GetCollider(), overlapX, overlapY))
				{
					//W
					if (pd == 0)
					{
						playerone->SetY(py + overlapY);
					}
					//S
					else if (pd == 1)
					{
						playerone->SetY(py - overlapY);
					}
					//D
					else if (pd == 2)
					{
						playerone->SetX(px - overlapX);
					}
					//A
					else if (pd == 3)
					{
						playerone->SetX(px + overlapX);
					}

					//std::cout << "px: " << px << std::endl << "py: " << py << std::endl;
				}
			
			}
			else if (bType == ENTITY_BOMB)
			{
				Bomb* bomb = static_cast<Bomb*>(b);
				if (playerone->IsOnBomb())
				{
					continue;
				}
				if (CollisionManager::Check(playerone->GetCollider(), bomb->GetCollider(), overlapX, overlapY))
				{
					//std::cout << "px: " << px << std::endl << "py: " << py << std::endl << "bombX: " << bomb->GetX() << std::endl << "bombY: " << bomb->GetY() << std::endl;
					if (bomb->GetX() != px && bomb->GetY() != py)
					{
						//std::cout << "bombx: " << bomb->GetX() << std::endl << "bomby: " << bomb->GetY() << std::endl << "px: " << px << std::endl << "py: " << py << std::endl;
						
							//W
							if (pd == 0)
							{
							
								playerone->SetY(py + 64);
							
							}
							//S
							else  if (pd == 1)
							{
								playerone->SetY(py - 64);
							
							}
							//d
							else  if (pd == 2)
							{
								playerone->SetX(px - 64);
						
							}
							//A
							else if (pd == 3)
							{
								playerone->SetX(px + 64);
						
							}
						
					}
				}
				
			}
			
			else if (bType == ENTITY_EXPLOSION)
			{
				Explosion* explosion = static_cast<Explosion*>(b);
				if (CollisionManager::Check(playerone->GetCollider(), explosion->GetCollider(), overlapX, overlapY))
				{
					if (playerone->GetLife() < 0)
					{
					playerone->SetActive(false);
					playerone->SetInvisible();

					NextState();
					}
					else
					{
						std::string dead = "../assets/dead.png";
						Sprite* sprite;
						sprite = m_systems.sprite_manager->CreateSprite(dead, 0, 0, 32, 32);
						UI* uiliv = new UI(sprite, 15, 200);
						uiliv->SetType(2);
						m_entities.push_back(uiliv);

						sprite = m_systems.sprite_manager->CreateSprite(dead, 0, 0, 32, 32);
						UI* uiliv2 = new UI(sprite, 47, 200);
						uiliv->SetType(2);
						m_entities.push_back(uiliv2);

						sprite = m_systems.sprite_manager->CreateSprite(dead, 0, 0, 32, 32);
						UI* m_liv3 = new UI(sprite, 79, 200);
						uiliv->SetType(2);
						m_entities.push_back(m_liv3);

						playerone->SetLife();
						std::cout << playerone->GetLife() << std::endl;
					}
					
				}
			}
		}
			if (aType == ENTITY_EXPLOSION)
			{
				Block* block = static_cast<Block*>(b);
				Explosion* explosion = static_cast<Explosion*>(a);
				
				if (bType == ENTITY_BLOCK)
				{
					if (CollisionManager::Check(block->GetCollider(), explosion->GetCollider(), overlapX, overlapY))
					{
						block->SetInvisible();
						block->SetActive();

					
					}
				}
				if (bType == ENTITY_BOMB)
				{
					Bomb* bomb = static_cast<Bomb*>(b);
					if (CollisionManager::Check(bomb->GetCollider(), explosion->GetCollider(), overlapX, overlapY))
					{
					
						bomb->SetInvisible();
						bomb->DeActivate();
					}
				}
					if (bType == ENTITY_SOLIDBLOCK)
						{
						if (CollisionManager::Check(explosion->GetCollider(), block->GetCollider(), overlapX, overlapY))
						{
						explosion->DeActive();
						explosion->SetInvisible();
						}
						
					}

			}
		
		}
	}
}