// OptionState.cpp

//Inte riktigt säker på vad vi behöver ta med atm
#include "stdafx.h"
#include "OptionState.h"
#include "GameState.h"
#include "MenuState.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"


#include "SoundManager.h"
#include "SoundClip.h"

#include "UI.h"

#include <fstream>
#include <iostream>


OptionState::OptionState(System& system)
{
	m_systems = system;


	std::string optionimg = "../assets/option.png";
	Sprite* sprite;


	sprite = m_systems.sprite_manager->CreateSprite(optionimg, 0, 0, 1080, 832);
	UI* option = new UI(sprite, 0, 0);
	option->SetType(4);
	m_entities.push_back(option);

	m_active = false;


}

OptionState::~OptionState()
{

}

bool OptionState::Update(float deltatime)
{
	Keyboard* m_keyboard;
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(SDLK_b) == true){

		return false;
	}
	else
		return true;

}

void OptionState::Draw()
{
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		Sprite* sprite = m_entities[i]->GetSprite();
		if (sprite)
		{
			m_systems.draw_manager->Draw(sprite,
				m_entities[i]->GetX(),
				m_entities[i]->GetY());
		}
	}
}

State* OptionState::NextState()
{
	
		return new MenuState(m_systems);
}

void OptionState::CollisionChecking()
{

}