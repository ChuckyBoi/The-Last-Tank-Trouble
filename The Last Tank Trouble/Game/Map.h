#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"


class Map :public sf::Drawable
{

private:

	int typesOfMaps = 30;
	int numOfVerticalWalls=0, numOfHorizontalWalls=0;

	sf::RectangleShape box;

	sf::RectangleShape verticalWall;
	sf::RectangleShape horizontalWall;

	std::vector <sf::RectangleShape> verticalWalls;
	std::vector <sf::RectangleShape> horizontalWalls;

	//sf::SoundBuffer bufferWall;
	//sf::Sound wall;



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

public:

	Map();
	void setup(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	/*
	void playWallSound()
	{
		wall.play();
	}
	*/

  //void setHorizontalWalls(std::vector <sf::RectangleShape> horizontalWalls_){   horizontalWalls = horizontalWalls_; }
  //void setVerticalWalls(std::vector <sf::RectangleShape> verticallWalls_) {	verticalWalls = verticallWalls_;    }

	sf::RectangleShape getHorizontalWall() { return horizontalWall; }
	sf::RectangleShape getVerticalWall() { return verticalWall; }

	sf::RectangleShape getRight() { return right; }
	sf::RectangleShape getLeft() { return left; }
	sf::RectangleShape getTop() { return top; }
	sf::RectangleShape getDown() { return down; }





	std::vector<sf::RectangleShape>getHorizontalWalls() {	return std::vector<sf::RectangleShape>(horizontalWalls); }
	std::vector<sf::RectangleShape>getVerticalWalls() {	return std::vector<sf::RectangleShape>(verticalWalls);}

	sf::RectangleShape getBox() { return box; }

	std::vector<sf::RectangleShape>gethLefts() { return std::vector<sf::RectangleShape>(hLefts); }
	std::vector<sf::RectangleShape>gethRights() { return std::vector<sf::RectangleShape>(hRights); }
	std::vector<sf::RectangleShape>gethTops() { return std::vector<sf::RectangleShape>(hTops); }
	std::vector<sf::RectangleShape>gethDowns() { return std::vector<sf::RectangleShape>(hDowns); }

	std::vector<sf::RectangleShape>getvLefts() { return std::vector<sf::RectangleShape>(vLefts); }
	std::vector<sf::RectangleShape>getvRights() { return std::vector<sf::RectangleShape>(vRights); }
	std::vector<sf::RectangleShape>getvTops() { return std::vector<sf::RectangleShape>(vTops); }
	std::vector<sf::RectangleShape>getvDowns() { return std::vector<sf::RectangleShape>(vDowns); }

};