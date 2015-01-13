// EndState.h

#pragma once
#include "State.h"
#include <vector>

class Entity;
class Keyboard;
class Playerone;
class Playertwo;

class EndState : public State
{
public:
	EndState(System& system, Playerone* playerone, Playertwo* playertwo);
	~EndState();

	bool Update(float deltatime);
	void Draw();
	
	State* NextState();

private:
	void CollisionChecking();

private:
	System m_systems;
	std::vector<Entity*> m_entities;

	Keyboard* m_keyboard;
	Playerone* m_playerone;
	Playertwo* m_playertwo;

	bool m_active;

	bool m_state;
};

