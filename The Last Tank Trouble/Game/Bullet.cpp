#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{

	//bullet.setFillColor(sf::Color::Red);

	/*
	left.setFillColor(sf::Color::Red);
	right.setFillColor(sf::Color::Black);
	top.setFillColor(sf::Color::Red);
	down.setFillColor(sf::Color::Black);


	*/
}


void Bullet::setup(sf::RenderWindow& window)
{
	bullet.setFillColor(sf::Color::Black);
	bullet.setOrigin(bullet.getRadius() / 2, bullet.getRadius() / 2);

	
	verticalWalls = map.getVerticalWalls();
	horizontalWalls = map.getHorizontalWalls();

	box = map.getBox();

	hLefts = map.gethLefts();
	hRights = map.gethRights();
	hDowns = map.gethDowns();
	hTops = map.gethTops();

	vLefts = map.getvLefts();
	vRights = map.getvRights();
	vDowns = map.getvDowns();
	vTops = map.getvTops();
	
}
void Bullet::setPosition(sf::Vector2f pos)
{
	bullet.setPosition(pos);
}
void Bullet::setDirection(sf::Vector2f dir)
{
	Direction = dir;
}
void Bullet::startTimer()
{
	clock.restart();
}
int Bullet::getTime()
{
	//timer = clock.getElapsedTime().asSeconds();
	return clock.getElapsedTime().asSeconds();;
}
void Bullet::bulletMovement()
{
		bullet.move(Direction.x, Direction.y);
}
void Bullet::collisionWithWalls()
{
	
	for(size_t i=0;i<horizontalWalls.size();i++)
	{

		if (bullet.getGlobalBounds().intersects(hTops[i].getGlobalBounds()))
		{
			if (Direction.y > 0)
			{
				Direction.y *= -1;
				//std::cout << "top" << std::endl;

			}
			
		}

		else if (bullet.getGlobalBounds().intersects(hDowns[i].getGlobalBounds()))
		{
			if (Direction.y < 0)
			{
				Direction.y *= -1;
				//std::cout << "down" << std::endl;

			}
			

		}
 		if (bullet.getGlobalBounds().intersects(hLefts[i].getGlobalBounds()))
		{
			if (Direction.x > 0)
			{
				Direction.x *= -1;
				//std::cout << "left" << std::endl;

			}
			
		}
		else if (bullet.getGlobalBounds().intersects(hRights[i].getGlobalBounds()))
		{
			if (Direction.x < 0)
			{
				Direction.x *= -1;
				//std::cout << "right" << std::endl;

			}
			


		}
	}

		for (size_t i = 0; i < verticalWalls.size(); i++)
		{
			

			if (bullet.getGlobalBounds().intersects(vTops[i].getGlobalBounds()))
			{
				if (Direction.y > 0)
				{
					Direction.y *= -1;
					//std::cout << "top" << std::endl;

				}

			}
			else if (bullet.getGlobalBounds().intersects(vDowns[i].getGlobalBounds()))
			{
				if (Direction.y < 0)
				{
					Direction.y *= -1;
					//std::cout << "down" << std::endl;

				}
			}
			if (bullet.getGlobalBounds().intersects(vLefts[i].getGlobalBounds()))
			{
				if (Direction.x > 0)
				{
					Direction.x *= -1;
					//std::cout << "left" << std::endl;
				}

			}
			else if (bullet.getGlobalBounds().intersects(vRights[i].getGlobalBounds()))
			{
				if (Direction.x < 0)
				{
					Direction.x *= -1;
					//std::cout << "right" << std::endl;

				}
			}
		}
}
void Bullet::collisionWithBox()
{
	if (bullet.getPosition().x < box.getPosition().x + bullet.getRadius() || bullet.getPosition().x > box.getPosition().x + box.getSize().x - bullet.getRadius())
	{
		Direction.x = Direction.x * -1;
	}
	if (bullet.getPosition().y < box.getPosition().y + bullet.getRadius() || bullet.getPosition().y > box.getPosition().y + box.getSize().y - bullet.getRadius())
	{
		Direction.y = Direction.y * -1;
	}
}

void Bullet::multiPlayerCollisionWithWalls(
	std::vector<sf::RectangleShape> horizontalWalls,
	std::vector<sf::RectangleShape> verticalWalls,
	std::vector<sf::RectangleShape> hLefts,
	std::vector<sf::RectangleShape> hRights,
	std::vector<sf::RectangleShape> hTops,
	std::vector<sf::RectangleShape> hDowns,
	std::vector<sf::RectangleShape> vLefts,
	std::vector<sf::RectangleShape> vRights,
	std::vector<sf::RectangleShape> vTops,
	std::vector<sf::RectangleShape> vDowns)
{

	

	for (size_t i = 0; i < horizontalWalls.size(); i++)
	{

		if (bullet.getGlobalBounds().intersects(hTops[i].getGlobalBounds()))
		{
			if (Direction.y > 0)
			{
				Direction.y *= -1;
				//std::cout << "top" << std::endl;

			}

		}

		else if (bullet.getGlobalBounds().intersects(hDowns[i].getGlobalBounds()))
		{
			if (Direction.y < 0)
			{
				Direction.y *= -1;
				//std::cout << "down" << std::endl;

			}


		}
		if (bullet.getGlobalBounds().intersects(hLefts[i].getGlobalBounds()))
		{
			if (Direction.x > 0)
			{
				Direction.x *= -1;
				//std::cout << "left" << std::endl;

			}

		}
		else if (bullet.getGlobalBounds().intersects(hRights[i].getGlobalBounds()))
		{
			if (Direction.x < 0)
			{
				Direction.x *= -1;
				//std::cout << "right" << std::endl;

			}



		}
	}

	for (size_t i = 0; i < verticalWalls.size(); i++)
	{


		if (bullet.getGlobalBounds().intersects(vTops[i].getGlobalBounds()))
		{
			if (Direction.y > 0)
			{
				Direction.y *= -1;
				//std::cout << "top" << std::endl;

			}

		}
		else if (bullet.getGlobalBounds().intersects(vDowns[i].getGlobalBounds()))
		{
			if (Direction.y < 0)
			{
				Direction.y *= -1;
				//std::cout << "down" << std::endl;

			}
		}
		if (bullet.getGlobalBounds().intersects(vLefts[i].getGlobalBounds()))
		{
			if (Direction.x > 0)
			{
				Direction.x *= -1;
				//std::cout << "left" << std::endl;
			}

		}
		else if (bullet.getGlobalBounds().intersects(vRights[i].getGlobalBounds()))
		{
			if (Direction.x < 0)
			{
				Direction.x *= -1;
				//std::cout << "right" << std::endl;

			}
		}
	}




}
void Bullet::multiPlayerCollisionWithBox(sf::RectangleShape box)
{
	if (bullet.getPosition().x < box.getPosition().x + bullet.getRadius() || bullet.getPosition().x > box.getPosition().x + box.getSize().x - bullet.getRadius())
	{
		Direction.x = Direction.x * -1;
	}
	if (bullet.getPosition().y < box.getPosition().y + bullet.getRadius() || bullet.getPosition().y > box.getPosition().y + box.getSize().y - bullet.getRadius())
	{
		Direction.y = Direction.y * -1;
	}

}
void Bullet::setOrigin()
{
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());
}
void Bullet::set_map(Map map)
{
	this->map = map;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bullet);
}
