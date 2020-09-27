#pragma once
#include "Button.h"


class Window:public sf::Drawable
{
public:

	virtual void setup(sf::RenderWindow& window)=0;
	virtual void handleEvents(const sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void update(sf::RenderWindow& window)=0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const=0;


private:



};