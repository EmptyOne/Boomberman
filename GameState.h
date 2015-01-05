// GameState.h

#pragma once
#include "State.h"

class Entity;

class GameState : public State
{
public:
	GameState(System& system);
	~GameState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:
	void CollisionChecking();

private:
	System m_systems;
	std::vector<Entity*> m_entities;

	bool m_active;
};

