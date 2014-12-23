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

	m_collider = new Collider(0, 0);
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
	if (m_keyboard->IsKeyDown(SDLK_w) == true)
	{
		m_y -= 10;
	}

	if (m_keyboard->IsKeyDown(SDLK_s) == true)
	{
		m_y += 10;
	}

	if (m_keyboard->IsKeyDown(SDLK_d) == true)
	{
		m_x += 10;
	}
	if (m_keyboard->IsKeyDown(SDLK_a) == true)
	{
		m_x -= 10;
	}

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
