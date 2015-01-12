// OptionState.h

#pragma once
#include "State.h"
#include <vector>

class Entity;
class Keyboard;

class OptionState : public State
{
public:
	OptionState(System& system);
	~OptionState();

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
	bool m_state;

};

