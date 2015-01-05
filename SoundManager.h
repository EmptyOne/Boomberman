#pragma once

class SoundClip;

class SoundManager{

public:
	SoundManager();
	~SoundManager();

	bool initialize();
	void Shutdown();

	SoundClip* CreateSoundClip(std::string p_sFilename);


private:
	std::map<std::string, Mix_Chunk*> m_axSounds;
	std::vector<SoundClip*> m_axSoundClips;

};