// Playertwo.cpp

#include "stdafx.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "Playertwo.h"
#include "Bomb.h"
#include "SoundClip.h"
#include "SoundManager.h"

Playertwo::Playertwo(Keyboard* keyboard, Sprite* sprite, Sprite* bombSprite, std::vector<Entity*>* entities, float x, float y, SoundClip* Fuse, SoundClip* Hurt)
{

	m_keyboard = keyboard;
	m_sprite = sprite;
	m_bombSprite = bombSprite;
	m_entities = entities;
	m_soundclip = Fuse;
	m_soundcliptwo = Hurt;

	m_collider = new Collider(x, y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w,
		m_sprite->GetRegion()->h);

	m_x = x;
	m_y = y;

	m_active = true;
	m_visible = true;
	m_bombAmount = 3;
	m_life = 2;

	Reset();

}

Playertwo::~Playertwo()
{
	if (m_collider)
		delete m_collider;
}

void Playertwo::Update(float deltatime)
{
	std::string filename = "../assets/main.png";
	Sprite* sprite;


	// axls movement
	m_timer += deltatime;
	m_playerSpeed = 0.25; //Borde vara samma som animations tiden
	m_bombSpeed += deltatime;
	m_bombTimer += deltatime;
	m_lifeTimer += deltatime;


	if (m_timer > m_playerSpeed)
	{
		if (m_keyboard->IsKeyDown(SDLK_i) == true)
		{
			if (m_y != 0)
			{
				m_y -= 64;
				m_timer = 0;
				m_dir = 0;
				m_onBomb = false;
			}
		}
		else if (m_keyboard->IsKeyDown(SDLK_k) == true)
		{
			if (m_y != 832.0f - 64.0f)
			{

				m_y += 64;
				m_timer = 0;
				m_dir = 1;
				m_onBomb = false;

			}
		}

		else if (m_keyboard->IsKeyDown(SDLK_l) == true)
		{
			if (m_x != 1080.0f - 64.0f)
			{
				m_x += 64;
				m_timer = 0;
				m_dir = 2;
				m_onBomb = false;
			}


		}
		else if (m_keyboard->IsKeyDown(SDLK_j) == true)
		{
			//För att man inte ska kunna glitcha utanför spelplanen
			if (m_x != 120)
			{

				m_x -= 64;
				m_timer = 0;
				m_dir = 3;
				m_onBomb = false;

			}
		}
	}

	if (m_keyboard->IsKeyDown(SDLK_h) == true)
	{
		if (m_bombSpeed > m_playerSpeed && 0 < m_bombAmount)
		{

			SoundClip* fuse = new SoundClip(*m_soundcliptwo);
			fuse->Play();

			Bomb* bomb = new Bomb(m_keyboard, m_bombSprite, m_x, m_y);
			bomb->Activate();
			m_entities->push_back(bomb);

			// när bomben skrivs ut är de rätt men när vi skickar den blire fel typ :S
			//std::cout << "bombx" << m_x << "bomby" << m_y << std::endl;
			m_bombAmount -= 1;

			m_bombSpeed = 0;

			m_onBomb = true;
		}


	}



	m_collider->SetPosition(m_x, m_y);

}
bool Playertwo::IsOnBomb()
{
	return m_onBomb;
}
float Playertwo::GetDir()
{
	return m_dir;
}
Sprite* Playertwo::GetSprite()
{
	return m_sprite;
}

Collider* Playertwo::GetCollider()
{
	return m_collider;
}

float Playertwo::GetX()
{
	return m_x;
}

float Playertwo::GetY()
{
	return m_y;
}

void Playertwo::SetX(float x)
{
	m_x = x;
}

void Playertwo::SetY(float y)
{
	m_y = y;
}

void Playertwo::SetActive(bool state)
{
	m_active = state;

}
void Playertwo::Reset()
{

}

bool Playertwo::IsVisible()
{
	return m_visible;
}
void Playertwo::SetInvisible()
{
	m_visible = false;
}
EEntityType Playertwo::GetType()
{
	return ENTITY_PLAYERTWO;
}
bool Playertwo::IsActive(){

	return m_active;
}
void Playertwo::BombIncrease(){

	std::cout << m_bombAmount << std::endl;
	m_bombAmount += 1;
	std::cout << m_bombAmount << std::endl;
}

void Playertwo::SetLife()
{
	if (m_lifeTimer > 2)
	{
		SoundClip* hurt = new SoundClip(*m_soundclip);
		hurt->Play();

		m_life -= 1;
		m_lifeTimer = 0;
	}
}

int Playertwo::GetLife()
{
	return m_life;
}