// Block.h

#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

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
	bool IsVisible();

	EEntityType GetType();
	Collider* GetCollider();

private:
	Sprite* m_sprite;
	Collider* m_collider;
	float m_x;
	float m_y;
	bool m_visible;
};

#endif // BLOCK_H_INCLUDED
