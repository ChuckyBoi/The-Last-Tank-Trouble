#pragma once
#include <SFML/Graphics.hpp>
#include "..//Bullet.h"
#include <string>
#include <random>

//#include "BulletSpeedPowerUp.h"
//#include "SpeedPowerUp.h"

class Icons : sf::Drawable
{
private :
	bool active = true;
	bool wasShot = false;
	std::string target;
	std::string typeOfPower;
 protected:
	sf::Vector2f size{ 50,50 };
	sf::Texture textureT;
	sf::RectangleShape powerUp{ size };
	sf::Clock spawnClock;
	sf::Clock lastingClock;
	Map map;
	std::vector <sf::RectangleShape> verticalWalls;
	std::vector <sf::RectangleShape> horizontalWalls;
	sf::RectangleShape box;

	


	bool itsCreated = false;//to make only one
	bool intersectsWithVerticals = false;
	bool intersectsWithHorizontalls = false;

public:
	Icons();
	static Icons* make_stooge();
	virtual void setup();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void setEffect();
	virtual bool getActive();
	virtual void setActive(bool active_);
	virtual std::string getTarget();
	virtual void setTarget(std::string target_);
	virtual std::string getTypeOfPower();
	virtual bool getIfWasShot();
	virtual void setWasShot(bool shot_);
	void setPosition();
	void setCreated(bool string);
	bool getCreated();
	void set_map(Map map);
	sf::RectangleShape entity();
	sf::RectangleShape getPowerUp();
    float getLastingClock();
	float getSpawnClock();
	void restartLastingClock();
	void restartSpawnClock();










};