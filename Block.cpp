// Block.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "Block.h"

Block::Block(Sprite* sprite, float x, float y)
{
	m_sprite = sprite;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, 
		m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;

	m_visible = true;
}

Block::~Block()
{
	if (m_collider)
		delete m_collider;
}

void Block::Update(float deltatime)
{
	// here be dragons
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

bool Block::IsVisible()
{
	return m_visible;
}

EEntityType Block::GetType()
{
	return ENTITY_BLOCK;
}

Collider* Block::GetCollider()
{
	return m_collider;
}
