// Keyboard.h

#pragma once

class Keyboard
{
	friend class InputManager;

public:
	Keyboard();

	bool IsKeyDown(int index);

private:
	void SetKeyboard(int index, bool state);

private:
	bool m_keys[256];

};

