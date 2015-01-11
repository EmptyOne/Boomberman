// EndState.cpp

//Inte riktigt säker på vad vi behöver ta med atm
#include "stdafx.h"
#include "EndState.h"

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


EndState::EndState(System& system)
{
	m_systems = system;

	std::cout << "EndState" << std::endl;
}

EndState::~EndState()
{

}

bool EndState::Update(float deltatime)
{
	return true;
}

void EndState::Draw()
{

}

State* EndState::NextState()
{
	return nullptr;
}

void EndState::CollisionChecking()
{

}