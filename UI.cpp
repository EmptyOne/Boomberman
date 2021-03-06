//UI.cpp

#include "stdafx.h"
#include "UI.h"
#include "Collider.h"
#include "Sprite.h"

UI::UI(Sprite* sprite, float x, float y){

	m_x = x;
	m_y = y;
	m_sprite = sprite;


	m_collider = new Collider(m_x, m_y);
	m_collider->SetParent(this);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	e = ENTITY_UI;

	m_active = true;
	m_visible = true;

}
UI::~UI(){

}

void UI::Update(float deltatime){

}
Sprite* UI::GetSprite(){

	return m_sprite;
}
Collider* UI::GetCollider(){

	return m_collider;
}
float UI::GetX(){

	return m_x;
}
float UI::GetY(){

	return m_y;
}
bool UI::IsVisible(){

	return m_visible;

}
EEntityType UI::GetType(){

	return e;
}
bool UI::IsActive(){

	return m_active;
}
void UI::SetType(int i)
{
	if (i == 1)
	{
		e = ENTITY_UI;
	}
	else if (i == 2)
	{
		e = ENTITY_LIV;
	}
	else if (i == 3)
	{
		e = ENTITY_MENU;
	}
	else if (i == 4)
	{
		e = ENTITY_OPTION;
	}
	else if (1 == 5)
	{
		e = ENTITY_PLAYERONEWIN;
	}
	else if (i == 6)
	{
		e = ENTITY_PLAYERTWOWIN;
	}

}