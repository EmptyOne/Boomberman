// Ball.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Ball.h"

// to enable random
#include <ctime>
#include <cstdlib>

// note(tommi): this below will automatically initialize srand
struct Random
{
	Random() { srand((unsigned int)time(0)); }
};
static Random randInitCaller;

float randf()
{
	return (float)rand() / (float)RAND_MAX;
}

float random(float min, float max)
{
	return min + (max - min) * randf();
}

Ball::Ball(Sprite* sprite, int width, int height, float startX, float startY)
{
	m_screen_width = width;
	m_screen_height = height;

	m_sprite = sprite;

	m_speed = 300.0f;
	m_offset = 1.0f;
	m_position_x = m_start_x = startX + m_offset;
	m_position_y = m_start_y = startY + m_offset;

	m_collider = new Collider(startX, startY);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w - m_offset,
		m_sprite->GetRegion()->h - m_offset);

	m_direction_x = 0.0f;
	m_direction_y = 0.0f;

	m_active = false;
}

Ball::~Ball()
{
	if (m_collider)
		delete m_collider;
}

void Ball::Update(float deltatime)
{
	if (!m_active)
		return;

	m_position_x += m_direction_x * m_speed * deltatime;
	m_position_y += m_direction_y * m_speed * deltatime;

	if (m_position_x < 0.0f)
	{
		m_position_x = 0.0f;
		m_direction_x = -m_direction_x;
	}
	else if (m_position_x > (m_screen_width - m_sprite->GetRegion()->w))
	{
		m_position_x = (m_screen_width - m_sprite->GetRegion()->w);
		m_direction_x = -m_direction_x;
	}

	if (m_position_y < 0.0f)
	{
		m_position_y = 0.0f;
		m_direction_y = -m_direction_y;
	}
	else if (m_position_y > m_screen_height)
	{
		Reset();
		m_direction_y = -m_direction_y;
	}

	m_collider->SetPosition(m_position_x, m_position_y);
}

Sprite* Ball::GetSprite()
{
	return m_sprite;
}
float Ball::GetX()
{
	return m_position_x;
}

float Ball::GetY()
{
	return m_position_y;
}

void Ball::Reset()
{
	m_position_x = m_start_x;
	m_position_y = m_start_y;
	m_active = false;

	m_collider->SetPosition(m_position_x, m_position_y);
}

bool Ball::IsVisible()
{
	return true;
}

EEntityType Ball::GetType()
{
	return ENTITY_BALL;
}

void Ball::SetPosition(float x, float y)
{
	m_position_x = x;
	m_position_y = y;
	m_collider->Refresh();
}

Collider* Ball::GetCollider()
{
	return m_collider;
}

void Ball::Activate()
{
	// activate the ball
	m_active = true;

	// randomize an direction for the ball
	m_direction_x = random(-2.0f, 2.0f);
	m_direction_y = -1.0f;

	// since we treat direction as being a unit vector
	// we normalize it so the length of the vector is 1.0f
	// think: c = squareroot(a^2 + b^2)
	// pythagoras theorem
	float length = sqrtf(m_direction_x * m_direction_x + m_direction_y * m_direction_y);

	// the universe will colapse if we divide by zero
	// reason: i72.servimg.com/u/f72/09/02/00/05/divide10.jpg
	if (length > 0.0f)
	{
		m_direction_x /= length;
		m_direction_y /= length;
	}
}

bool Ball::IsActive()
{
	return m_active;
}

void Ball::InvertDirectionX()
{
	m_direction_x = -m_direction_x;
}

void Ball::InvertDirectionY()
{
	m_direction_y = -m_direction_y;
}
