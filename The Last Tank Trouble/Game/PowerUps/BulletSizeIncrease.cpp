#include "BulletSizeIncrease.h"
#include <iostream>

std::string BulletSizeIncrease::getTypeOfPower()
{
	return typeOfPower;
}

void BulletSizeIncrease::setPos()
{
	setPosition();
}
void BulletSizeIncrease::setActive(bool active_)
{
	active = active_;
}
bool BulletSizeIncrease::getActive()
{
	return active;
}
std::string BulletSizeIncrease::getTarget()
{
	return target;
}
void BulletSizeIncrease::setTarget(std::string target_)
{
	target = target_;
}
void BulletSizeIncrease::setup()
{
	powerUp.setPosition(sf::Vector2f(1, 1));
	powerUp.setSize(sf::Vector2f(35, 35));

	textureT.loadFromFile("Images/BulletSizeIncrease.png");
	powerUp.setTexture(&textureT);
}
float BulletSizeIncrease::getLastingClock()
{
	return lastingClock.getElapsedTime().asSeconds();
}
void BulletSizeIncrease::restartLastingClock()
{
	lastingClock.restart();
}
void BulletSizeIncrease::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(powerUp);
}
bool BulletSizeIncrease::getIfWasShot()
{
	return wasShot;
}
void BulletSizeIncrease::setWasShot(bool shot_)
{
	wasShot = shot_;
}
