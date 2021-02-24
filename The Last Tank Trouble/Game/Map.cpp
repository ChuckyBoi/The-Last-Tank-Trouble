#include "Map.h"
#include <iostream>



Map::Map()
{

	box.setOutlineThickness(6);
	box.setOutlineColor(sf::Color::Black);

	verticalWall.setFillColor(sf::Color::Black);
	horizontalWall.setFillColor(sf::Color::Black);

	horizontalWall.setSize(sf::Vector2f(70, 6));
	verticalWall.setSize(sf::Vector2f(6, 70));

	//bufferWall.loadFromFile("Audio/wall.ogg");
	//wall.setBuffer(bufferWall);

}

void Map::setup(sf::RenderWindow& window)
{
	//srand(time(NULL));

	int randomX, randomY;

	verticalWalls.clear();
	horizontalWalls.clear();

	hLefts.clear();
	hDowns.clear();
	hTops.clear();
	hRights.clear();

	vLefts.clear();
	vDowns.clear();
	vTops.clear();
	vRights.clear();

	left.setFillColor(sf::Color::Black);
	right.setFillColor(sf::Color::Black);
	top.setFillColor(sf::Color::Black);
	down.setFillColor(sf::Color::Black);

	//if restarted;

	randomX = rand() % typesOfMaps;
	randomY = rand() % typesOfMaps;

	if (randomX < 10) { randomX += 10; }
	if (randomY < 10) { randomY += 10; }

	box.setSize(sf::Vector2f(randomX * window.getSize().x / typesOfMaps, randomY * window.getSize().y / typesOfMaps));
		
	numOfHorizontalWalls = randomX;
	numOfVerticalWalls = randomY;

	box.setPosition(sf::Vector2f(window.getSize().x / 2 - box.getSize().x / 2, window.getSize().y / 2 - box.getSize().y / 2));


	
	sf::Vector2f boxPos = box.getPosition();

	
	for (size_t i = 0; i < numOfHorizontalWalls; i++)
	{
		boxPos.x = box.getPosition().x;
		boxPos.y += verticalWall.getSize().y;

		for (size_t j = 0; j < numOfHorizontalWalls; j++)
		{
			boxPos.x += horizontalWall.getSize().x;

			if (boxPos.x + horizontalWall.getSize().x > box.getPosition().x + box.getSize().x - horizontalWall.getSize().x)
			{
				continue;
			}
			if (boxPos.y > box.getPosition().y + box.getSize().y - verticalWall.getSize().y)
			{
				continue;
			}
			if ((rand() % 2 == 0))
			{
				horizontalWall.setPosition(boxPos.x + horizontalWall.getSize().y, boxPos.y);
				horizontalWalls.push_back(sf::RectangleShape(horizontalWall));
			}
		}
	}
	boxPos = box.getPosition();

	for (size_t i = 0; i < numOfVerticalWalls; i++)
	{
		boxPos.x = box.getPosition().x;
		boxPos.y += verticalWall.getSize().y;

		for (size_t j = 0; j < numOfVerticalWalls; j++)
		{
			boxPos.x += horizontalWall.getSize().x;

			if (boxPos.x + horizontalWall.getSize().x > box.getPosition().x + box.getSize().x- horizontalWall.getSize().x)
			{
				continue;
			}
			if (boxPos.y > box.getPosition().y + box.getSize().y - 1.5* verticalWall.getSize().y)
			{
				continue;
			}
			if ((rand() % 2 == 0))
			{
				//something important here
				verticalWall.setPosition(boxPos.x, boxPos.y);
				verticalWalls.push_back(sf::RectangleShape(verticalWall));
			}
		}
		boxPos.y += verticalWall.getSize().y;
	}

	for (size_t i = 0; i < horizontalWalls.size(); i++)
	{
		horizontalWalls[i].setSize(sf::Vector2f(70, 6));
	}

	for (size_t i = 0; i < verticalWalls.size(); i++)
	{
		verticalWalls[i].setSize(sf::Vector2f(6, 76));
	}
	for (size_t i = 0; i < horizontalWalls.size(); i++)
	{
		left.setSize(sf::Vector2f(1, horizontalWalls[i].getSize().y));
		right.setSize(sf::Vector2f(1, horizontalWalls[i].getSize().y));
		top.setSize(sf::Vector2f(horizontalWalls[i].getSize().x, 1));
		down.setSize(sf::Vector2f(horizontalWalls[i].getSize().x, 1));

		left.setPosition(horizontalWalls[i].getPosition().x + 3, horizontalWalls[i].getPosition().y);
		right.setPosition(horizontalWalls[i].getPosition().x + horizontalWalls[i].getSize().x - 3, horizontalWalls[i].getPosition().y);
		top.setPosition(horizontalWalls[i].getPosition().x, horizontalWalls[i].getPosition().y - 5);
		down.setPosition(horizontalWalls[i].getPosition().x, horizontalWalls[i].getPosition().y + horizontalWalls[i].getSize().y + 5);

		hLefts.push_back(sf::RectangleShape(left));
		hRights.push_back(sf::RectangleShape(right));
		hDowns.push_back(sf::RectangleShape(down));
		hTops.push_back(sf::RectangleShape(top));
	}
	for (size_t i = 0; i < verticalWalls.size(); i++)
	{
		left.setSize(sf::Vector2f(1, verticalWalls[i].getSize().y));
		right.setSize(sf::Vector2f(1, verticalWalls[i].getSize().y));
		top.setSize(sf::Vector2f(verticalWalls[i].getSize().x, 1));
		down.setSize(sf::Vector2f(verticalWalls[i].getSize().x, 1));

		left.setPosition(verticalWalls[i].getPosition().x - 5, verticalWalls[i].getPosition().y);
		right.setPosition(verticalWalls[i].getPosition().x + verticalWalls[i].getSize().x + 5, verticalWalls[i].getPosition().y);
		top.setPosition(verticalWalls[i].getPosition().x, verticalWalls[i].getPosition().y + 3);
		down.setPosition(verticalWalls[i].getPosition().x, verticalWalls[i].getPosition().y + verticalWalls[i].getSize().y - 3);

		vLefts.push_back(sf::RectangleShape(left));
		vRights.push_back(sf::RectangleShape(right));
		vTops.push_back(sf::RectangleShape(top));
		vDowns.push_back(sf::RectangleShape(down));
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(box, states);
	
	for (auto& i : verticalWalls)
	{
		target.draw(i);
	}
	for (auto& i : horizontalWalls)
	{
		target.draw(i);
	}
	
	/*for (size_t i = 0; i < verticalWalls.size(); i++)
	{
		target.draw(verticalWalls[i]);
	}
	*/
	
	/*
	for (size_t j = 0; j < horizontalWalls.size(); j++)
	{
		target.draw(horizontalWalls[j]);
	}
	*/
	
	
	/*
	for (size_t i = 0; i < horizontalWalls.size(); i++)
	{
		target.draw(hLefts[i]);
		target.draw(hRights[i]);
		target.draw(hDowns[i]);
		target.draw(hTops[i]);

	}
	for (size_t i = 0; i < verticalWalls.size(); i++)
	{
		target.draw(vLefts[i]);
		target.draw(vRights[i]);
		target.draw(vDowns[i]);
		target.draw(vTops[i]);

	}
	*/
	
	
	
}

