// kommer vi använda denna?


#include "stdafx.h"
#include "Sprite.h"
#include "Collider.h"
#include "BreakableBlock.h"

BreakableBlock::BreakableBlock(Sprite* sprite, float x, float y)
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

BreakableBlock::~BreakableBlock()
{
	if (m_collider)
		delete m_collider;
}

void BreakableBlock::Update(float deltatime)
{
	// here be dragons
}

Sprite* BreakableBlock::GetSprite()
{
	return m_sprite;
}

float BreakableBlock::GetX()
{
	return m_x;
}

float BreakableBlock::GetY()
{
	return m_y;
}

void BreakableBlock::Reset()
{
	m_visible = true;
}

void BreakableBlock::SetInvisible()
{
	m_visible = false;
}

bool BreakableBlock::IsVisible()
{
	return m_visible;
}

EEntityType BreakableBlock::GetType()
{
	return ENTITY_BREAKABLEBLOCK;
}

Collider* BreakableBlock::GetCollider()
{
	return m_collider;
}
