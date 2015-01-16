// Playerone.h

#pragma once

#include "Entity.h"


class Explosion : public Entity
{
public:
	
	Explosion(Sprite* sprite, float x, float y);
	~Explosion();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();
	float GetDir();
	void SetY(float y);
	void SetX(float x);
	void SetInvisible();
	void DeActive();
	float GetTimer();

	void Setpos(float x, float y);

	void Reset();

	bool IsVisible();
	bool IsActive();
	EEntityType GetType();
	void SetType(int i);
	Collider* GetCollider();


private:
	Sprite* m_sprite;
	Collider* m_collider;

	float m_x;
	float m_y;
	//float m_bombX;
	//float m_bombY;
	float m_dir;
	EEntityType e;

	
	float m_playerSpeed;
	float m_bombSpeed;

	float m_explosionTimer;

	bool m_active;
	bool m_visible;

};


