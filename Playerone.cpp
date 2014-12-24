// Playerone.cpp

#include "stdafx.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playerone.h"



Playerone::Playerone(Keyboard* keyboard,Sprite* sprite,float x, float y)
{
	
	m_keyboard = keyboard;
	m_sprite = sprite;

	m_collider = new Collider(x, y);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, 
		m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;
	

	/*
	m_screen_width = screen_width;
	m_screen_height = screen_height;
	*/
	m_speed = 2.0f;
	Reset();
	
}

Playerone::~Playerone()
{
	if (m_collider)
		delete m_collider;
}

void Playerone::Update(float deltatime)
{
	//Skärm limit
	if (m_x < 120)
	{
		m_x = 120;
	}
	else if (m_x > 1080.0f - 64.0f)
	{
		m_x = 1080.0f - 64.0f;
	}
	if (m_y < 0)
	{
		m_y = 0;
	}
	else if (m_y > 832.0f - 64.0f)
	{
		m_y = 832.0f - 64.0f;
	}

	// semihs snapp variabler
		int snappX;
		int snappY = 0;
		int timer = 0;
	

	// axls movement
		if (m_keyboard->IsKeyDown(SDLK_w) == true || snappY != 0)
	{
			if (m_keyboard->IsKeyDown(SDLK_w) == true)
			{
				m_y -= 2;
				snappY = (unsigned int)m_y % 64;
				
				std::cout <<"snappY first: " << snappY << std::endl;
				m_keyboard->IsKeyDown(300);
			}
			
			
			if (snappY != 0 || snappY != 62)
			{
				if (snappY > 32)
				{
					std::cout << "m_y " << m_y << std::endl;
					snappY -= 64;
					std::cout << "snappY, less than 32: " << snappY << std::endl;
					m_y -= snappY;
					std::cout << "m_y efter -: " << m_y << std::endl;
				}
				else if (snappY < 32)
				{
					std::cout << "m_y " << m_y << std::endl;
					snappY -= 64;
					std::cout << "more than 32: " << snappY << std::endl;
					m_y += snappY;
					std::cout << "m_y efter -: " << m_y << std::endl;
				}

				snappY = 0;
				
			}
			std::cout << "!!!!!!!!!!!" << std::endl;
	}


	if (m_keyboard->IsKeyDown(SDLK_s) == true || snappY )
	{
		m_y += 2;
	}

	else if (m_keyboard->IsKeyDown(SDLK_d) == true)
	{
		
		m_x += 2;
		
	}
	else if (m_keyboard->IsKeyDown(SDLK_a) == true)
	{
	
		m_x -= 2;
	}



//här trodde jag att de var bättre med SDL_KEYUP men den suger jag får den aldrig att funka.

	/*if (m_keyboard->IsKeyDown(SDLK_w) == false)
	{
	snappX = (int)m_x % 64;
	snappY = (int)m_y % 64;
	std::cout << snappY;

	m_y = (float)(snappY * 64);

	if (snappX > 32)
	{
	m_x = (float)(snappX * 64);
	}
	}*/
	/*if (m_keyboard->IsKeyDown(SDL_KEYUP) == false)
	{
		

		std::cout << snappY << std::endl;

		if (snappY != 64)
		{
		m_y += snappY;
		}
	
		}
		*/
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

void Playerone::Reset()
{
	//m_x = 1;
	//m_y = 1;

}

bool Playerone::IsVisible() 
{
	return true;
}

EEntityType Playerone::GetType()
{
	return ENTITY_PLAYERONE;
}
