// StateManager.h

#pragma once

// forward declare
class State;

class StateManager
{
	friend class Engine;

public:
	StateManager();
	~StateManager();

	bool Update();
	void Draw();

private:
	void SetState(State* state);

private:
	State* m_active_state;
	unsigned int m_tick;
};
