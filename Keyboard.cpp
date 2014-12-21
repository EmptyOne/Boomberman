// Keyboard.cpp

#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < sizeof(m_keys); i++)
		m_keys[i] = false;
}

bool Keyboard::IsKeyDown(int index)
{
	if (index < 0 || index >= sizeof(m_keys))
		return false;
	return m_keys[index];
}

void Keyboard::SetKeyboard(int index, bool state)
{
	//m_keys[index] = state;
	if (index == SDLK_w)
	{
		std::cout << "w";
	}

	if (index == SDLK_a)
	{
		std::cout << "a";
	}

	if (index == SDLK_s)
	{
		std::cout << "s";
	}

	if (index == SDLK_d)
	{
		std::cout << "d";
	}

	if (index == SDLK_SPACE)
	{
		std::cout << " ";
	}

}
