// Playerone.cpp

#include "stdafx.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playerone.h"
#include "Ball.h"



Playerone::Playerone(Keyboard* keyboard,Sprite* sprite,float x, float y)
{
	
	m_keyboard = keyboard;
	m_sprite = sprite;
	
	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
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
	//Skärm limit, kanske inte behövs om man gör limit där nere
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
			}
		}
	}


	if (m_keyboard->IsKeyDown(SDLK_s) == true)
	{
		if (m_y != 832.0f - 64.0f)
		{
			if (m_timer > m_playerSpeed)
			{
				m_y += 64;
				m_timer = 0;
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
			}
		}
	}
	if (m_keyboard->IsKeyDown(SDLK_SPACE) == true)
	{
		if (m_timer > m_playerSpeed)
		{
			//Ball* ball = new Ball(m_x, m_y);
			m_timer = 0;
		}
	}



//här trodde jag att de var bättre med SDL_KEYUP men den suger jag får den aldrig att funka.

	/*if (m_keyboard->IsKeyDown(SDLK_w) == false)
	{
	snappX = (int)m_x % 64;
	snappY = (int)m_y % 64;
	std::cout << snappY;

	m_y = (float)(snappY * 64) ;

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
