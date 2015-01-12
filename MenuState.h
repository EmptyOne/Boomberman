// MenuState.h

#pragma once
#include "State.h"
#include <vector>

class Entity;
//class Playerone;
class Bomb;
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
	//Playerone* m_player;
	Bomb* m_bomb;
	Keyboard* m_keyboard;

	bool m_active;
	float m_bombX;
	float m_bombY;
	float m_bombTimer;
};

