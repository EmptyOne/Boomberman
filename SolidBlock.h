//block.h

#pragma once

#include "Entity.h"

class SolidBlock : public Entity {

public:
	SolidBlock(Sprite* sprite, float x, float y);
	~SolidBlock();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();

	bool IsVisible();
	void SetInvisible();


	EEntityType GetType();
	Collider* GetCollider();

private:
	Sprite* m_sprite;
	Collider* m_collider;
	float m_x;
	float m_y;
	bool m_visible;
};