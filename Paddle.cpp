// Paddle.cpp

#include "stdafx.h"
#include "Mouse.h"
#include "Sprite.h"
#include "Collider.h"
#include "Paddle.h"

Paddle::Paddle(Mouse* mouse, Sprite* sprite, int screen_width, int screen_height)
{
	m_mouse = mouse;
	m_sprite = sprite;

	m_collider = new Collider(0, 0);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, 
		m_sprite->GetRegion()->h);

	m_x = 0.0f;
	m_y = 0.0f;
	m_screen_width = screen_width;
	m_screen_height = screen_height;

	m_speed = 2.0f;
	
	Reset();
}

Paddle::~Paddle()
{
	if (m_collider)
		delete m_collider;
}

void Paddle::Update(float deltatime)
{
	float deltaX = m_mouse->GetX() - (m_x + static_cast<float>(m_sprite->GetRegion()->w * 0.5f));
	if (static_cast<int>(deltaX) != 0)
	{
		float dirX = deltaX / abs(deltaX);
		m_x += m_speed * abs(deltaX) * deltatime * dirX;

		if (m_x < 0.0f)
			m_x = 0.0f;
		else if (m_x > m_screen_width - 80.0f)
			m_x = m_screen_width - 80.0f;

		m_collider->SetPosition(m_x, m_y);
	}
}

Sprite* Paddle::GetSprite()
{
	return m_sprite;
}

Collider* Paddle::GetCollider()
{
	return m_collider;
}

float Paddle::GetX()
{
	return m_x;
}

float Paddle::GetY()
{
	return m_y;
}

void Paddle::Reset()
{
	m_x = m_screen_width / 2 - 40;
	m_y = m_screen_height - 60 - 8;
	m_collider->SetPosition(m_x, m_y);
}

bool Paddle::IsVisible() 
{
	return true;
}

EEntityType Paddle::GetType()
{
	return ENTITY_PADDLE;
}
