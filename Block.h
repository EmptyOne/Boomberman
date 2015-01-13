// Block.h

#pragma once

#include "Entity.h"

class Block : public Entity
{
public:
	Block(Sprite* sprite, float x, float y);
	~Block();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();

	void Reset();

	void SetInvisible();
	void Block::SetActive();
	bool IsVisible();
	bool IsActive();

	void SetType(int i);
	EEntityType GetType();
	Collider* GetCollider();

private:
	Sprite* m_sprite;
	Collider* m_collider;
	float m_x;
	float m_y;
	bool m_visible;
	EEntityType e; 
	bool m_active;
};