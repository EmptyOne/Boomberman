// Ball.h

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(Sprite* sprite, int width, int height, float startX, float startY);
	~Ball();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();

	void Reset();

	bool IsVisible();
	EEntityType GetType();
	Collider* GetCollider();

	void Activate();
	bool IsActive();
	void SetPosition(float x, float y);

	void InvertDirectionX();
	void InvertDirectionY();

private:
	Sprite* m_sprite;
	Collider* m_collider;

	int m_screen_width;
	int m_screen_height;

	float m_speed;
	float m_offset;
	float m_position_x;
	float m_position_y;
	float m_direction_x;
	float m_direction_y;

	float m_start_x;
	float m_start_y;
	
	bool m_active;
};

#endif // BALL_H_INCLUDED
