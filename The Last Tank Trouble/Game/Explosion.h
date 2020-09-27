#pragma once
#include "Animation.h"
#include "SFML/Audio.hpp"


class Explosion : public Animation
{
public:

	sf::SoundBuffer bufferExplosion;
	sf::Sound explosion;

	sf::Texture explosionT;
	Animation explosionS{ explosionT, 0, 0, 256, 256, 50, 0.2 };
	
	Explosion()
	{
		bufferExplosion.loadFromFile("Audio/bomb.ogg");
		explosion.setBuffer(bufferExplosion);

		explosionT.loadFromFile("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Images/type_C.png");
		
	}
	bool isEnd()
	{
		return explosionS.frame + explosionS.speed >= explosionS.frames.size();
	}
	void startAgain()
	{
		explosionS.frame = 0;
	}
	void update()
	{
		explosionS.update();
	}
	void setPosition(sf::Vector2f pos)
	{
		explosionS.sprite.setPosition(pos);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(explosionS, states);	
	}
	void playSound()
	{
		//explosion.play();
	}









};