// MenuState.h

#pragma once
#include "State.h"
#include <vector>

class Entity;
class Keyboard;

class MenuState : public State
{
public:
	MenuState(System& system);
	~MenuState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:
	void CollisionChecking();

private:
	System m_systems;
	std::vector<Entity*> m_entities;

	Keyboard* m_keyboard;

	bool m_active;
	int m_state;

};

