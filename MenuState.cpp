// MenuState.cpp

//Inte riktigt säker på vad vi behöver ta med atm
#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

#include "Playerone.h"
#include "Block.h"
#include "Bomb.h"
#include "Playertwo.h"
#include "Explosion.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "SoundManager.h"
#include "SoundClip.h"

#include "UI.h"

#include <fstream>
#include <iostream>


MenuState::MenuState(System& system)
{
	m_systems = system;
	std::string liv = "../assets/Hearth.png";

	Sprite* sprite;


	std::cout << "MenuState" << std::endl;
	NextState();
	
}

MenuState::~MenuState()
{

}

bool MenuState::Update(float deltatime)
{
	return true;
}

void MenuState::Draw()
{

}

State* MenuState::NextState()
{
	return new GameState(m_systems);
}

void MenuState::CollisionChecking()
{

}