// Block.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Block.h"

Block::Block(Sprite* sprite, float x, float y)
{
	m_sprite = sprite;
	m_x = x;
	m_y = y;

	m_collider = new Collider(m_x, m_y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	e = ENTITY_BLOCK;

	m_active = true;
	m_visible = true;
}

Block::~Block()
{
	if (m_collider)
		delete m_collider;
}

void Block::Update(float deltatime)
{

}

Sprite* Block::GetSprite()
{
	return m_sprite;
}

float Block::GetX()
{
	return m_x;
}

float Block::GetY()
{
	return m_y;
}

void Block::Reset()
{
	m_visible = true;
}

void Block::SetInvisible()
{
	m_visible = false;
}
void Block::SetActive()
{
	m_active = false;
}

bool Block::IsVisible()
{
	return m_visible;
}

EEntityType Block::GetType()
{
	return e;
}

void Block::SetType(int i)
{
	if (i == 1)
	{
		e = ENTITY_BACKGROUNDBLOCK;
	}
	else if (i == 2)
	{
		e = ENTITY_SOLIDBLOCK;
	}
	else if (i == 3)
	{
		e = ENTITY_BLOCK;
	}

}

Collider* Block::GetCollider()
{
	return m_collider;
}
bool Block::IsActive(){

	return m_active;
}