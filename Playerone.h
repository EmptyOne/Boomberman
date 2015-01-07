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


	void Reset();

	bool IsVisible();
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


	float m_timer;
	float m_playerSpeed;
	float m_bombTimer;




	std::vector<Entity*>* m_entities;


};


