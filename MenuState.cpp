// MenuState.cpp

#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"
#include "EndState.h"
#include "OptionState.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include "SoundManager.h">
#include "SoundClip.h"

#include "UI.h"

#include <fstream>
#include <iostream>


MenuState::MenuState(System& system)
{


	m_systems = system;
	std::string menuimg = "../assets/menu.png";

	Sprite* sprite;

	sprite = m_systems.sprite_manager->CreateSprite(menuimg, 0, 0, 1080, 832);
	UI* menu = new UI(sprite, 0, 0);
	menu->SetType(3);
	m_entities.push_back(menu);


	std::cout << "MenuState" << std::endl;

	m_active = false;
}

MenuState::~MenuState()
{

}

bool MenuState::Update(float deltatime)
{
	Keyboard* m_keyboard;

	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(SDLK_q) == true)
	{

		std::string start = "../assets/start.wav";

		SoundClip* startS = m_systems.sound_manager->CreateSoundClip(start);
		startS->Play();

		m_state = true;
		NextState();
		return false;
	}
	else if (m_systems.input_manager->GetKeyboard()->IsKeyDown(SDLK_w) == true){
		m_state = false;
		NextState();
		return false;
	}
	else if (m_systems.input_manager->GetKeyboard()->IsKeyDown(SDLK_r) == true)
	{
		
		//Kalla på engine shutdown?
		SDL_Quit();
	}
	return true;
}

void MenuState::Draw()
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
State* MenuState::NextState()
{
	if (m_state == true){

		return new GameState(m_systems);
	}
	else if (m_state == false){

		return new OptionState(m_systems);
	}

}

void MenuState::CollisionChecking()
{

}