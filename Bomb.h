// Bomb.h

#pragma once

#include "Entity.h"

class Explosion;

class Bomb : public Entity
{

public:
	//Bomb();
	Bomb(Keyboard* keyboard, Sprite* sprite, float startX, float startY);
	~Bomb();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();
	float GetTimer();

	void Reset();

	bool IsVisible();
	void SetInvisible();

	EEntityType GetType();
	Collider* GetCollider();

	void Activate();
	void DeActivate();
	bool IsActive();
	
	void SetPosition(float x, float y);


private:
	Keyboard* m_keyboard;
	Sprite* m_sprite;
	Collider* m_collider;


	float m_speed;
	float m_offset;
	float m_position_x;
	float m_position_y;
	float m_timer;

	float m_start_x;
	float m_start_y;
	

	bool m_visible;
	bool m_active;

	std::vector<Entity*>* m_entities;
	
	float m_bombTimer;

	Explosion* m_explosion;
};

