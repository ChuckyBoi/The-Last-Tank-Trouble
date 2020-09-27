#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "../Resources/ResourceManagement.h"

class Score : public sf::Drawable
{
private:

   
	sf::RectangleShape board;

/*
	int scoreForPlayer0;
	int scoreForPlayer1;

	

	sf::RectangleShape Tank0;
	sf::RectangleShape Tank1;

	sf::Text lblScoreForPlayer0 = { "Score: " + std::to_string(scoreForPlayer0),font,30 };
	sf::Text lblScoreForPlayer1 = { "Score: " + std::to_string(scoreForPlayer1),font,30 };
	*/

	struct Mystruct {

		int scoreForPlayer = 0;
		sf::RectangleShape Tank;
		sf::Texture TankT;
		sf::Font font;
		sf::Text lblScoreForPlayer = {std::to_string(scoreForPlayer),font,30 };

	}Player[2];



public:

	Score()
	{
	

		Player[0].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("RedTank"));
		Player[1].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("GreenTank"));

		Player[0].font.loadFromFile("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Fonts/crackman front.ttf");
		Player[1].font.loadFromFile("D:/SFML PROGRAM/The Last Tank Trouble/The Last Tank Trouble/Fonts/crackman front.ttf");

	}
	void setup(sf::RenderWindow& window);
	void increaseScoreForPlayer(int pNumber);
	
	void restart();


	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;















};