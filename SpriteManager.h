// SpriteManager.h

#pragma once

class Sprite;
class SpriteText;

class SpriteManager
{
	friend class DrawManager;

public:
	SpriteManager(SDL_Renderer* renderer);
	~SpriteManager();

	Sprite* CreateSprite(const std::string& filename, int x, int y, int w, int h);
	SpriteText* CreateSprite(const std::string& fontfilename, char size, const std::string& text, int colorR, int colorG, int colorB);
	void DestroySprite(Sprite* sprite);

private:
	SDL_Renderer* m_renderer;
	std::vector<Sprite*> m_sprites;
	std::map<std::string, SDL_Texture*> m_textures;
	std::map<std::string, TTF_Font*> m_fonts;
};

