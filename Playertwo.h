// Playertwo.h

#pragma once

#include "Entity.h"

class Keyboard;

class Playertwo : public Entity
{
public:
	Playertwo(Keyboard* keyboard, Sprite* sprite, float x, float y);
	~Playertwo();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();
	void SetY(float y);
	void SetX(float x);

	float GetDir();


	void Reset();

	bool IsVisible();
	bool IsActive();
	EEntityType GetType();
	Collider* GetCollider();


private:

	Keyboard* m_keyboard;
	Sprite* m_sprite;
	Collider* m_collider;

	float m_x;
	float m_y;
	float m_dir;

	bool m_space;

	bool m_active;

	float m_timer;
	float m_playerSpeed;

};


