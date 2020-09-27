#include "MultiPlayerMenu.h"


void MultiPlayerMenu::setup(sf::RenderWindow& window)
{
	BK.setPosition(sf::Vector2f(window.getSize().x / 2 - BK.getSize().x/2, window.getSize().y/2  ));
	Server.setPosition(sf::Vector2f(BK.getPosition().x, BK.getPosition().y + Server.getSize().y));
	Client.setPosition(sf::Vector2f(BK.getPosition().x, BK.getPosition().y + 2*Client.getSize().y));


	//multiPlayer.setup(window);

}
void MultiPlayerMenu::handleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	BK.selectByMouse(mouse);
	BK.handleEvents(event);

	Server.selectByMouse(mouse);
	Server.handleEvents(event);


	Client.selectByMouse(mouse);
	Client.handleEvents(event);

	//multiPlayer.handleEvents(event, window);

	/*
	if(serverbuttonWasPressed())
	{
		multiPlayer.server();
	}
	if(clientbuttonWasPressed())
	{
		multiPlayer.client();
	}
	*/
}
void MultiPlayerMenu::update(sf::RenderWindow& window)
{
	//multiPlayer.update(window);
	//multiPlayer.server();
	//multiPlayer.client();


}
void MultiPlayerMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(MPS);
	target.draw(BK);
	target.draw(Server);
	target.draw(Client);
	
}


