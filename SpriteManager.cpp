// SpriteManager.cpp
#include "stdafx.h"
#include "Sprite.h"
#include "SpriteText.h"
#include "SpriteManager.h"

SpriteManager::SpriteManager(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

SpriteManager::~SpriteManager()
{
	// delete all remanining sprites
	auto it = m_sprites.begin();
	while (it != m_sprites.end())
	{
		delete (*it);
		++it;
	}
	m_sprites.clear();

	// destroy all loaded textures
	auto itr = m_textures.begin();
	while (itr != m_textures.end()) 
	{
		SDL_DestroyTexture(itr->second);
		++itr;
	}
	m_textures.clear();

	// destroy all loaded fonts
	auto itf = m_fonts.begin();
	while (itf != m_fonts.end())
	{
		TTF_CloseFont(itf->second);
		++itf;
	}
	m_textures.clear();
}

Sprite* SpriteManager::CreateSprite(const std::string& filename, int x, int y, int w, int h)
{
	// first we search for if the texture is already loaded
	auto it = m_textures.find(filename);
	if (it == m_textures.end())
	{
		// if not, we create a new one
		SDL_Surface* surface = IMG_Load(filename.c_str());
		SDL_Surface* optimizedSurface = nullptr;

		if (surface != nullptr)
		{
			optimizedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB4444, 0);
			SDL_FreeSurface(surface);
		}
		else
		{
			const char* error = SDL_GetError();
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, optimizedSurface);

		// we save the texture in the map for later reuse
		m_textures.insert(std::pair<std::string, SDL_Texture*>(filename, texture));

		// we can destroy the surface
		// since we now have a texture
		// that we use instead
		if (optimizedSurface != nullptr)
		{
			SDL_FreeSurface(optimizedSurface);
		}
		// now we get the texture so we can return it with a sprite
		it = m_textures.find(filename);
	}

	// then we create a new sprite 
	// with the texture associated
	Sprite* sprite = new Sprite(it->second);
	sprite->GetRegion()->x = x;
	sprite->GetRegion()->y = y;
	sprite->GetRegion()->w = w;
	sprite->GetRegion()->h = h;
	m_sprites.push_back(sprite);

	// return the newly newed sprite
	return sprite;
}

SpriteText* SpriteManager::CreateSprite(const std::string& fontfilename, char size, const std::string& text, int colorR, int colorG, int colorB)
{
	auto it = m_fonts.find((fontfilename + "_" + size));
	if (it == m_fonts.end())
	{
		TTF_Font* font = TTF_OpenFont(fontfilename.c_str(), size);
		if (font != nullptr)
		{
			m_fonts.insert(std::pair<std::string, TTF_Font*>((fontfilename + "_" + size), font));
		}
		else
		{
			const char* error = TTF_GetError();
		}
		it = m_fonts.find((fontfilename + "_" + size));
	}

	SpriteText* spritetext = new SpriteText(m_renderer, it->second, text, colorR, colorG, colorB); // Second = andra parametern
	m_sprites.push_back(spritetext);
	return spritetext;

}
void SpriteManager::DestroySprite(Sprite* sprite)
{
	// we look through all sprites
	auto it = m_sprites.begin();
	while (it != m_sprites.end())
	{
		// if we find the right one 
		if ((*it) == sprite)
		{
			// we delete the sprite
			delete sprite;
			// and remove it from the vector
			m_sprites.erase(it);
			break;
		}
		++it;
	}
}
