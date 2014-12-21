//solidSolidBlock.cpp

#include "stdafx.h"
#include "SolidBlock.h"
#include "Sprite.h"
#include "Collider.h"

SolidBlock::SolidBlock(Sprite* sprite, float x, float y){

	m_sprite = sprite;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w,
		m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;

	
}
SolidBlock::~SolidBlock()
{
	if (m_collider)
		delete m_collider;
}
Sprite* SolidBlock::GetSprite()
{
	return m_sprite;
}
void SolidBlock::Update(float deltatime)
{
	// here be dragons
}
float SolidBlock::GetX()
{
	return m_x;
}

float SolidBlock::GetY()
{
	return m_y;
}
bool SolidBlock::IsVisible()
{
	m_visible = true;
	return m_visible;
}
EEntityType SolidBlock::GetType()
{
	return ENTITY_SOLIDBLOCK;
}

Collider* SolidBlock::GetCollider()
{
	return m_collider;
}
