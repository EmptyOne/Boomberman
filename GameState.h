// GameState.h

#pragma once
#include "State.h"
#include <vector>

class Entity;
class Playerone;

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
	Playerone* m_player;

	bool m_active;
};

