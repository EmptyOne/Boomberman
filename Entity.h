// Entity.h

#pragma once

enum EEntityType
{
	ENTITY_UNKNOWN,
	ENTITY_PLAYERONE,
	ENTITY_BLOCK,
	ENTITY_BOMB,
	ENTITY_SOLIDBLOCK,
	ENTITY_BACKGROUNDBLOCK,
	ENTITY_PLAYERTWO,
	ENTITY_EXPLOSION,
	ENTITY_UI,
	ENTITY_LIV
};

class Sprite;
class Collider;

class Entity
{
public:
	virtual ~Entity() {}
	virtual void Update(float deltatime) = 0;
	virtual Sprite* GetSprite() = 0;
	virtual Collider* GetCollider() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual bool IsVisible() = 0;
	virtual EEntityType GetType() = 0;
	virtual bool IsActive() = 0;
};

