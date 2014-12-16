
#include "Entity.h"

class BreakableBlock : Entity
{
public:
	BreakableBlock(Sprite* sprite, float x, float y);
	~BreakableBlock();

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