#include "ResourceManagement.h"

ResourceManagement::ResourceManagement()
{
	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/type_C.png","explosion");

	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/RedTank.png", "RedTank");
	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/GreenTank.png", "GreenTank");
	//LoadFromFile("Fonts/crackman front.ttf");
	//music.openFromFile("Audio/generals.ogg");
	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/Button.png","Button");
	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/MM.jpg","MM");
	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/MP.jpg","MP");
	LoadTexture("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/OP.jpg","OP");


	//LoadSoundBuffer("Audio/ButtonPush.wav", "ButtonSound");
}
void ResourceManagement::LoadTexture(std::string path, std::string name)
{
	sf::Texture* t = new sf::Texture();
	t->loadFromFile(path);

	m_textures[name] = t;
}
void ResourceManagement::LoadSoundBuffer(std::string path, std::string name)
{
	sf::SoundBuffer* t = new sf::SoundBuffer();
	t->loadFromFile(path);

	m_BufferSounds[name] = t;

}
void ResourceManagement::CleanUp()
{
	for (auto item : m_textures)
	{
		delete item.second;
		item.second = nullptr;
	}
}

sf::Texture* ResourceManagement::RequestedTexture(std::string name)
{
	if (m_textures[name]) return m_textures[name];

	return nullptr;
}
sf::SoundBuffer* ResourceManagement::RequestedSound(std::string name)
{
	if (m_BufferSounds[name]) return m_BufferSounds[name];

	return nullptr;

}