// Playerone.h

#pragma once

#include "Entity.h"

class Keyboard;

class Playerone : public Entity
{
public:
	Playerone(Keyboard* keyboard, Sprite* sprite, float x, float y);
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
	
	Keyboard* m_keyboard;
	Sprite* m_sprite;
	Collider* m_collider;

	float m_x;
	float m_y;
	float m_speed;
	int m_screen_width;
	int m_screen_height;

	// tror inte vi kommer behöva använda dom här
	// semih sa typ att man kan göra fake tiles med modulus sjukt lätt
	int m_keypress;
	int m_numMax;
	int m_numMin;

	
};


