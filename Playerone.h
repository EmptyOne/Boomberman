// Playerone.h

#pragma once

#include "Entity.h"

class Keyboard;

class Playerone : public Entity
{
public:
	Playerone(Sprite* sprite, float x, float y);
	~Playerone();
	
	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();

	void Reset();

	bool IsVisible();
	EEntityType GetType();
	Collider* GetCollider();


private:
	
	Sprite* m_sprite;
	Collider* m_collider;

	float m_x;
	float m_y;
	float m_speed;
	int m_screen_width;
	int m_screen_height;
;
};

