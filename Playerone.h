// Playerone.h

#pragma once

#include "Entity.h"

class Keyboard;

class Playerone : public Entity
{
public:
	Playerone(Keyboard* keyboard, Sprite* sprite, Sprite* bombSprite, std::vector<Entity*>* entities, float x, float y);
	~Playerone();
	
	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();
	void SetY(float y);
	void SetX(float x);

	float GetDir();

	void BombIncrease();

	void Reset();

	bool IsOnBomb();
	bool IsVisible();
	bool IsActive();
	EEntityType GetType();
	Collider* GetCollider();


private:
	
	Keyboard* m_keyboard;
	Sprite* m_sprite;
	Sprite* m_bombSprite;
	Collider* m_collider;

	float m_x;
	float m_y;
	float m_dir;

	bool m_space;

	bool m_onBomb;


	float m_timer;
	float m_playerSpeed;
	float m_bombSpeed;

	unsigned int m_bombAmount;
	float m_bombTimer;

	bool m_active;

	std::vector<Entity*>* m_entities;


};


