// GameState.h

#pragma once
#include "State.h"
#include <vector>

class Entity;
class Playerone;
class Playertwo;
class Bomb;

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
	Playertwo* m_playertwo;	
	Bomb* m_bomb;
	


	bool m_active;
	float m_bombX;
	float m_bombY;
	float m_bombTimer;
};

