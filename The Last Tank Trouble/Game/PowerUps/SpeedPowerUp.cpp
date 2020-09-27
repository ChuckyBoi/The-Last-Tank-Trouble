#include "SpeedPowerUp.h"
#include <iostream>

std::string SpeedPowerUp::getTypeOfPower()
{
	return typeOfPower;
}

void SpeedPowerUp::setPos()
{
	setPosition();
}

void SpeedPowerUp::setEffect()
{
	std::cout << "speed" << std::endl;
}

void SpeedPowerUp::setActive(bool active_)
{
	active = active_;
}

bool SpeedPowerUp::getActive()
{
	return active;
}

std::string SpeedPowerUp::getTarget()
{
	return target;
}

void SpeedPowerUp::setTarget(std::string target_)
{
	target = target_;
}

void SpeedPowerUp::setup()
{
	powerUp.setPosition(sf::Vector2f(1, 1));
	powerUp.setSize(sf::Vector2f(35, 35));

	textureT.loadFromFile("Images/speedImage.png");
	powerUp.setTexture(&textureT);

	//setPosition();

}
float SpeedPowerUp::getLastingClock()
{
	return lastingClock.getElapsedTime().asSeconds();
}
void SpeedPowerUp::restartLastingClock()
{
	lastingClock.restart();
}
void SpeedPowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(powerUp);
}

