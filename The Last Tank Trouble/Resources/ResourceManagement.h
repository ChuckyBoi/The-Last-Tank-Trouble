#pragma once
#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class ResourceManagement {
public:
	static ResourceManagement* GetInstance()
	{

		static ResourceManagement instance;
		return &instance;
	}

	void CleanUp();

	sf::Texture* RequestedTexture(std::string name);
	sf::SoundBuffer* RequestedSound(std::string name);
private:
	ResourceManagement();
	void LoadTexture(std::string path, std::string name);
	void LoadSoundBuffer(std::string path, std::string name);
	std::map<std::string, sf::Texture*>m_textures;
	std::map<std::string, sf::SoundBuffer*>m_BufferSounds;

};