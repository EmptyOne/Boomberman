#include "stdafx.h"
#include "Explosion.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playerone.h"
#include "Bomb.h"

Explosion::Explosion(Sprite* sprite, float x, float y)
{
	m_sprite = sprite;
	m_x = x;
	m_y = y;
	

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w,
		m_sprite->GetRegion()->h);

	m_active = true;
}
Explosion::~Explosion()
{
	if (m_collider)
		delete m_collider;
}

void Explosion::Update(float deltatime)
{
	m_explosionTimer += deltatime;
	if (m_explosionTimer > 1)
	{
		m_active = false;
		m_explosionTimer = 0;
	}
}
float Explosion::GetTimer()
{
	return m_explosionTimer;
}
Sprite* Explosion::GetSprite()
{
	return m_sprite;
}

float Explosion::GetX()
{
	return m_x;
}

float Explosion::GetY()
{
	return m_y;
}

float Explosion::GetDir()
{
	return m_dir;
}
void Explosion::SetY(float y)
{
	m_y = y;
}
void Explosion::SetX(float x)
{
	m_x = x;
}

void Explosion::Reset()
{
	m_active = false;
}

bool Explosion::IsVisible()
{
	return true;
}
bool Explosion::IsActive()
{
	return m_active;
}
EEntityType Explosion::GetType()
{
	return ENTITY_EXPLOSION;
}
Collider* Explosion::GetCollider()
{
	return m_collider;
}
void Explosion::Setpos(float x, float y){
	m_x = x;
	m_y = y;

}
void Explosion::SetInvisible()
{
	m_visible = false;
}

void Explosion::DeActive()
{
	m_active = false;
}