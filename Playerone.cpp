// Playerone.cpp

#include "stdafx.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playerone.h"
#include "Bomb.h"



Playerone::Playerone(Keyboard* keyboard, Sprite* sprite, Sprite* bombSprite, std::vector<Entity*>* entities, float x, float y)
{

	m_keyboard = keyboard;
	m_sprite = sprite;
	m_bombSprite = bombSprite;
	m_entities = entities;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w,
		m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;




	Reset();

}

Playerone::~Playerone()
{
	if (m_collider)
		delete m_collider;
}

void Playerone::Update(float deltatime)
{
	std::string filename = "../assets/main.png";
	Sprite* sprite;


	// axls movement
	m_timer += deltatime;
	m_playerSpeed = 0.25; //Borde vara samma som animations tiden

	if (m_keyboard->IsKeyDown(SDLK_w) == true)
	{
		if (m_y != 0)
		{
			if (m_timer > m_playerSpeed)
			{
				m_y -= 64;
				m_timer = 0;
				m_dir = 0;
			}
		}
	}


	else if (m_keyboard->IsKeyDown(SDLK_s) == true)
	{
		if (m_y != 832.0f - 64.0f)
		{
			if (m_timer > m_playerSpeed)
			{
				m_y += 64;
				m_timer = 0;
				m_dir = 1;
			}
		}
	}

	else if (m_keyboard->IsKeyDown(SDLK_d) == true)
	{
		if (m_x != 1080.0f - 64.0f)
		{
			if (m_timer > m_playerSpeed)
			{
				m_x += 64;
				m_timer = 0;
				m_dir = 2;
			}
		}


	}
	else if (m_keyboard->IsKeyDown(SDLK_a) == true)
	{
		//För att man inte ska kunna glitcha utanför spelplanen
		if (m_x != 120)
		{
			if (m_timer > m_playerSpeed)
			{
				m_x -= 64;
				m_timer = 0;
				m_dir = 3;
			}
		}
	}

	if (m_keyboard->IsKeyDown(SDLK_SPACE) == true)
	{

		Bomb* bomb = new Bomb(m_keyboard, m_bombSprite, m_x, m_y);
		m_entities->push_back(bomb);
		std::cout << "Bomb" << std::endl;
		
		

	}

	//bomber?
	//if (m_keyboard->IsKeyDown(SDLK_SPACE) == true)
	//{
	//	if (m_timer > m_playerSpeed)
	//	{
	//		std::cout << "Space" << std::endl;
	//		
	//	
	//		m_timer = 0;
	//	}
	//}




	m_collider->SetPosition(m_x, m_y);

}
float Playerone::GetDir()
{
	return m_dir;
}
Sprite* Playerone::GetSprite()
{
	return m_sprite;
}

Collider* Playerone::GetCollider()
{
	return m_collider;
}

float Playerone::GetX()
{
	return m_x;
}

float Playerone::GetY()
{
	return m_y;
}

void Playerone::SetX(float x)
{
	m_x = x;
}

void Playerone::SetY(float y)
{
	m_y = y;
}


void Playerone::Reset()
{

}

bool Playerone::IsVisible()
{
	return true;
}

EEntityType Playerone::GetType()
{
	return ENTITY_PLAYERONE;
}



