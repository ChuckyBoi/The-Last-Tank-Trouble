#pragma once
#include "Map.h"

class Bullet : sf::Drawable
{


private:

	
	
	
	sf::Clock clock;
	sf::CircleShape bullet{ 5 };
	sf::Vector2f Direction;
	bool isOutsideTheTank = false;
	
	
	std::vector<sf::RectangleShape > verticalWalls;
	std::vector<sf::RectangleShape > horizontalWalls;
	
	sf::RectangleShape left;
	sf::RectangleShape right;
	sf::RectangleShape top;
	sf::RectangleShape down;

	std::vector<sf::RectangleShape > hLefts;
	std::vector<sf::RectangleShape > hRights;
	std::vector<sf::RectangleShape > hTops;
	std::vector<sf::RectangleShape > hDowns;

	std::vector<sf::RectangleShape > vLefts;
	std::vector<sf::RectangleShape > vRights;
	std::vector<sf::RectangleShape > vTops;
	std::vector<sf::RectangleShape > vDowns;
	

	sf::RectangleShape box;
	Map map;

public:
	Bullet();
	void setup(sf::RenderWindow& window);
	float getBulletSize()
	{
		return bullet.getRadius();
	}
	void setBulletSize(float radius_)
	{
		bullet.setRadius(radius_);
	}

	void setPosition(sf::Vector2f pos);
	void setDirection(sf::Vector2f dir);
	void startTimer();
	int getTime();
	void bulletMovement();
	void collisionWithWalls();
	void collisionWithBox();

	void multiPlayerCollisionWithWalls(
	std::vector<sf::RectangleShape>  horizontalWalls,
	std::vector<sf::RectangleShape>  verticalWalls,
	std::vector<sf::RectangleShape > hLefts,
	std::vector<sf::RectangleShape > hRights,
	std::vector<sf::RectangleShape > hTops,
	std::vector<sf::RectangleShape > hDowns,

	std::vector<sf::RectangleShape >vLefts,
	std::vector<sf::RectangleShape > vRights,
	std::vector<sf::RectangleShape > vTops,
	std::vector<sf::RectangleShape > vDowns
	);
	void multiPlayerCollisionWithBox(sf::RectangleShape box);
	void setOrigin();
	
	bool GetOutsideTheTank()
	{
		return isOutsideTheTank;
	}
	void setOutsideTheTank()
	{
		isOutsideTheTank = true;
	}
	
	sf::CircleShape getShape() 
	{
		return bullet;
	}

	
	void set_map(Map map);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};