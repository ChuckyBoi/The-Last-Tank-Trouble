
#include "Options.h"


void Options::setup(sf::RenderWindow& window)
{
	BK.setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y - 2 * BK.getSize().y ));

}
void Options::handleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	BK.selectByMouse(mouse);
	BK.handleEvents(event);
}
void Options::update(sf::RenderWindow& window)
{



}
void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(OPS);
	target.draw(BK);
}


