#include "Icons.h"
#include "BulletSpeedPowerUp.h"
#include "SpeedPowerUp.h"
#include "BulletSizeIncrease.h"
#include <iostream>


Icons::Icons()
{
	
}
Icons* Icons::make_stooge()
{
	int random;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randomNumber(0, 2);
	random=randomNumber(rand);
	
	
		if (random == 0) {
			return new SpeedPowerUp();
		}
		else if (random == 1)
		{
			return new BulletSpeedPowerUp();
		}
		else if (random == 2)
		{
			return new BulletSizeIncrease();
		}
		
	
	
}
void Icons::setup()
{
}
void Icons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(powerUp);
}
void Icons::setEffect()
{
	std::cout << "ICons" << std::endl;
}

std::string Icons::getTypeOfPower()
{
	return typeOfPower;
}
bool Icons::getIfWasShot()
{
	return wasShot;
}
void Icons::setWasShot(bool shot_)
{
	wasShot = shot_;
}
sf::RectangleShape Icons::entity()
{
	return powerUp;
}
sf::RectangleShape Icons::getPowerUp()
{
	return powerUp;
}
std::string Icons::getTarget()
{
	return target;
}
void Icons::setTarget(std::string target_)
{
	target = target_;
}
bool Icons::getActive()
{
	return active;
}
void Icons::setActive(bool active_)
{
	active = active_;
}
void Icons::set_map(Map map)
{
	this->map = map;
}
float Icons::getLastingClock()
{
	return lastingClock.getElapsedTime().asSeconds();
}
void Icons::restartLastingClock()
{
	lastingClock.restart();
}
float Icons::getSpawnClock()
{
	return spawnClock.getElapsedTime().asSeconds();
}
void Icons::restartSpawnClock()
{
	spawnClock.restart();
}
void Icons::setPosition()
{
	box = map.getBox();
	verticalWalls = map.getVerticalWalls();
	horizontalWalls = map.getHorizontalWalls();

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> forX(box.getPosition().x, box.getPosition().x + box.getSize().x - powerUp.getSize().x); // define the range
	std::uniform_int_distribution<> forY(box.getPosition().y, box.getPosition().y + box.getSize().y - powerUp.getSize().y);
	intersectsWithVerticals = false;
	intersectsWithHorizontalls = false;

	powerUp.setPosition(forX(eng), forY(eng));
	for (size_t i = 0; i < verticalWalls.size(); i++)
	{
		if (powerUp.getGlobalBounds().intersects(verticalWalls[i].getGlobalBounds()))
		{
			intersectsWithVerticals = true;
		}
	}
	for (size_t i = 0; i < horizontalWalls.size(); i++)
	{
		if (powerUp.getGlobalBounds().intersects(horizontalWalls[i].getGlobalBounds()))
		{
			intersectsWithHorizontalls = true;
		}
	}
	if (intersectsWithHorizontalls || intersectsWithVerticals)
	{
		setPosition();
	}
}
void Icons::setCreated(bool string)
{
		itsCreated = string;
}
bool Icons::getCreated()
{
		return itsCreated;
}
