//spritetext.h

#pragma once

#include "Sprite.h"

class SpriteText : public Sprite{
public:

	SpriteText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int r, int g, int b);
	~SpriteText();

	SDL_Color GetColor();
	std::string GetText();
	void Set(const std::string& text);
	void Set(int colorR, int colorG, int colorB);
	void Set(const std::string& text, int colorR, int colorG, int colorB);
private:
	void UpdateTexture();

	SDL_Renderer* m_renderer;
	TTF_Font* m_font;
	SDL_Color m_color;
	std::string m_text;

};