// Bomb.cpp

#include "stdafx.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "Bomb.h"
#include "Playerone.h"
#include "Explosion.h"


Bomb::Bomb(Keyboard* keyboard, Sprite* sprite, float startX, float startY)
{
	
	m_keyboard = keyboard;
	m_sprite = sprite;
	//m_entities = entities;
	
	m_speed = 300.0f;
	m_offset = 1.0f;

	

	m_position_x = m_start_x = startX + m_offset;
	m_position_y = m_start_y = startY + m_offset;


	m_collider = new Collider(startX, startY);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w - m_offset,
	m_sprite->GetRegion()->h - m_offset);

	//m_active = true;
	m_active = false;


}

Bomb::~Bomb()
{
	if (m_collider)
		delete m_collider;
}

void Bomb::Update(float deltatime)
{
	std::string filename = "../assets/main.png";
	Sprite* sprite;


	if (!m_active)
		return;

	m_bombTimer += deltatime;

	
	if (m_bombTimer > 2.5){
		
		//m_explosion = new Explosion(m_sprite, m_entities, m_position_x, m_position_y);
		//m_entities->push_back(bomb);
		m_active = false;
		

		std::cout << "Bomb" << std::endl;
		m_bombTimer = 0;
		


	}

	m_collider->SetPosition(m_position_x, m_position_y);
}

Sprite* Bomb::GetSprite()
{
	return m_sprite;
}
float Bomb::GetX()
{
	return m_position_x;
}

float Bomb::GetY()
{
	return m_position_y;
}

void Bomb::Reset()
{
	
	m_active = false;


}

bool Bomb::IsVisible()
{
	return true;
}

void Bomb::SetInvisible()
{
	m_visible = false;
}
EEntityType Bomb::GetType()
{
	return ENTITY_BOMB;
}

void Bomb::SetPosition(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
	m_collider->Refresh();
}

Collider* Bomb::GetCollider()
{
	return m_collider;
}

void Bomb::Activate()
{
	// activate the Bomb
	m_active = true;
}

bool Bomb::IsActive()
{
	return m_active;
}

float Bomb::GetTimer()
{
	return m_bombTimer;
}

void Bomb::DeActivate()
{
	m_active = false;
}