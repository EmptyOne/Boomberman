// Playertwo.cpp

#include "stdafx.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playertwo.h"
#include "Bomb.h"



Playertwo::Playertwo(Keyboard* keyboard, Sprite* sprite, float x, float y)
{

	m_keyboard = keyboard;
	m_sprite = sprite;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w,
		m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;


	m_active = true;
	Reset();

}

Playertwo::~Playertwo()
{
	if (m_collider)
		delete m_collider;
}

void Playertwo::Update(float deltatime)
{

	// axls movement
	m_timer += deltatime;
	m_playerSpeed = 0.25; //Borde vara samma som animations tiden

	if (m_keyboard->IsKeyDown(SDLK_i) == true)
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


	else if (m_keyboard->IsKeyDown(SDLK_k) == true)
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

	else if (m_keyboard->IsKeyDown(SDLK_l) == true)
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
	else if (m_keyboard->IsKeyDown(SDLK_j) == true)
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

	if (m_keyboard->IsKeyDown(SDLK_p) == true)
	{
		m_dir = 5;


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
float Playertwo::GetDir()
{
	return m_dir;
}
Sprite* Playertwo::GetSprite()
{
	return m_sprite;
}

Collider* Playertwo::GetCollider()
{
	return m_collider;
}

float Playertwo::GetX()
{
	return m_x;
}

float Playertwo::GetY()
{
	return m_y;
}

void Playertwo::SetX(float x)
{
	m_x = x;
}

void Playertwo::SetY(float y)
{
	m_y = y;
}


void Playertwo::Reset()
{

}

bool Playertwo::IsVisible()
{
	return true;
}

EEntityType Playertwo::GetType()
{
	return ENTITY_PLAYERTWO;
}
bool Playertwo::IsActive(){
	return m_active;
}


