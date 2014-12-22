// Playerone.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playerone.h"

Playerone::Playerone(Sprite* sprite,float x, float y)
{
	
	
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
	

	/*float deltaX = m_mouse->GetX() - (m_x + static_cast<float>(m_sprite->GetRegion()->w * 0.5f));
	if (static_cast<int>(deltaX) != 0)
	{
		float dirX = deltaX / abs(deltaX);
		m_x += m_speed * abs(deltaX) * deltatime * dirX;

		if (m_x < 0.0f)
			m_x = 0.0f;
		else if (m_x > m_screen_width - 80.0f)
			m_x = m_screen_width - 80.0f;

		m_collider->SetPosition(m_x, m_y);
	}*/
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
