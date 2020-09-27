#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Animation : public sf::Drawable 
{
public:

	float frame, speed;
	sf::Sprite sprite;
	std::vector<sf::IntRect>frames;

public:
	Animation();
	Animation(sf::Texture& t, float x, float y, float w, float h, float count, float speed_);
	void update();
	bool isEnd();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	





};