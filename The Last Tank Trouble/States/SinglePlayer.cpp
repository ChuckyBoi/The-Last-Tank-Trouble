#include "SinglePlayer.h"
#include <iostream>




void SinglePlayer::setup(sf::RenderWindow& window)
{
	
	BK.setPosition(sf::Vector2f(0,window.getSize().y - BK.getSize().y));

	
	map.setup(window);
	players.set_map(map);
	players.setup(window);



}
void SinglePlayer::handleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	
	BK.selectByMouse(mouse);
	BK.handleEvents(event);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (!pressed)
		{
			map.setup(window);
			std::cout << "this supposed to happen many times" << std::endl;
			players.set_map(map);
			players.setup(window);

			players.set_score(score);
			players.restart();
			players.setup(window);
			pressed = true;
		}
	    
	}
	else 
	{
		pressed = false;
	}


	
		
	
}
void SinglePlayer::update(sf::RenderWindow& window)
{
	players.Update();
	if (players.getRestart()) 
	{
		setup(window);
		players.setCantRestart();
	}
}

void SinglePlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(BK);

	target.draw(map);
	
	target.draw(players);

	//target.draw(score);
	

}


