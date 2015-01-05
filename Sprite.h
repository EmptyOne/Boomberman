// Sprite.h

#pragma once
class Sprite
{
public:
	Sprite(SDL_Texture* texture);
	~Sprite();

	SDL_Rect* GetRegion();
	SDL_Texture* GetTexture();

protected:
	SDL_Rect m_region;
	SDL_Texture* m_texture;
};
