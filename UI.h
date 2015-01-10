//UI.h

#pragma once

#include "Entity.h"

class UI : public Entity{
public:

	UI(Sprite* sprite, float x, float y);
	~UI();

	void Update(float deltatime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EEntityType GetType();
	bool IsActive();

	void SetType(int i);

private:
	Sprite* m_sprite;
	Collider* m_collider;
	EEntityType e;
	
	float m_x;
	float m_y;
	

	bool m_visible;
	bool m_active;

};