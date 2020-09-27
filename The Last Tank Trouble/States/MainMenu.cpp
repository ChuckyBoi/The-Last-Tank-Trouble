#include "MainMenu.h"

void MainMenu::setup(sf::RenderWindow &window)
{
	SP.setPosition(sf::Vector2f(window.getSize().x - 1.25 * SP.getSize().x, window.getSize().y/5));
	MP.setPosition(sf::Vector2f(window.getSize().x - 1.25 * MP.getSize().x, window.getSize().y/5 + 1.5 *window.getSize().y/10));
	OP.setPosition(sf::Vector2f(window.getSize().x - 1.25 * OP.getSize().x, window.getSize().y/5 + 3.0 *window.getSize().y/10));
	EX.setPosition(sf::Vector2f(window.getSize().x - 1.25 * EX.getSize().x, window.getSize().y/5 + 4.5 *window.getSize().y/10));

	
}


void MainMenu::handleEvents(const sf::Event& event,sf::RenderWindow &window)
{
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 

	SP.selectByMouse(mouse);
	SP.handleEvents(event);

	MP.selectByMouse(mouse);
	MP.handleEvents(event);

	OP.selectByMouse(mouse);
	OP.handleEvents(event);

	EX.selectByMouse(mouse);
	EX.handleEvents(event);

}
void MainMenu::update(sf::RenderWindow& window)
{



}
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	

	target.draw(MMS);
	target.draw(SP);
	target.draw(OP);
	target.draw(MP);
	target.draw(EX);

}


