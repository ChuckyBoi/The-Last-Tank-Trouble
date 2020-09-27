#include "BulletSpeedPowerUp.h"
#include <iostream>


void BulletSpeedPowerUp::setEffect()
{
	std::cout << "bullet speed" << std::endl;

}
std::string BulletSpeedPowerUp::getTypeOfPower()
{
	return typeOfPower;
}
void BulletSpeedPowerUp::setup()
{
	powerUp.setPosition(sf::Vector2f(1, 1));
	powerUp.setSize(sf::Vector2f(35, 35));

	textureT.loadFromFile("Images/bulletSpeedImage.png");
	powerUp.setTexture(&textureT);
}
void BulletSpeedPowerUp::setActive(bool active_)
{
	active = active_;
}
bool BulletSpeedPowerUp::getActive()
{
	return active;
}
void BulletSpeedPowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(powerUp);
}



float BulletSpeedPowerUp::getLastingClock()
{
	return lastingClock.getElapsedTime().asSeconds();
}
void BulletSpeedPowerUp::restartLastingClock()
{
	lastingClock.restart();
}

std::string BulletSpeedPowerUp::getTarget()
{
	return target;
}

void BulletSpeedPowerUp::setTarget(std::string target_)
{
	target = target_;
}

	

