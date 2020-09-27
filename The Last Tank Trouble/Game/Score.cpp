#include "Score.h"

void Score::setup(sf::RenderWindow& window)
{
//	board.setFillColor(sf::Color(220, 220, 220));
    board.setFillColor(sf::Color::White);

	board.setOutlineThickness(5);
	board.setOutlineColor(sf::Color::Black);
	board.setSize(sf::Vector2f(window.getSize().x / 4, window.getSize().y/10));
	board.setPosition(sf::Vector2f(window.getSize().x/2 - board.getSize().x/2,0));

	Player[0].Tank.setSize(sf::Vector2f(50, 40));
	Player[1].Tank.setSize(sf::Vector2f(50, 40));

	Player[0].Tank.setOrigin(sf::Vector2f(Player[0].Tank.getSize().x / 2, Player[0].Tank.getSize().y / 2));
	Player[1].Tank.setOrigin(sf::Vector2f(Player[1].Tank.getSize().x / 2, Player[1].Tank.getSize().y / 2));

	Player[0].Tank.setPosition(sf::Vector2f(board.getPosition().x + Player[0].Tank.getSize().x/2,board.getPosition().y + board.getSize().y/2));

	Player[1].Tank.setRotation(180);
	Player[1].Tank.setPosition(sf::Vector2f(board.getPosition().x + board.getSize().x - Player[1].Tank.getSize().x / 2, board.getPosition().y + board.getSize().y/2));

	Player[0].lblScoreForPlayer.setFillColor(sf::Color::Black);
	Player[1].lblScoreForPlayer.setFillColor(sf::Color::Black);

	Player[0].lblScoreForPlayer.setPosition(sf::Vector2f(Player[0].Tank.getPosition().x + Player[0].Tank.getSize().x ,Player[0].Tank.getPosition().y/2));
	Player[1].lblScoreForPlayer.setPosition(sf::Vector2f(Player[1].Tank.getPosition().x - Player[1].Tank.getSize().x - Player[1].lblScoreForPlayer.getCharacterSize(), Player[1].Tank.getPosition().y / 2));
}

void Score::increaseScoreForPlayer(int pNumber)
{
	Player[pNumber].scoreForPlayer++;
	Player[pNumber].lblScoreForPlayer.setString(std::to_string(Player[pNumber].scoreForPlayer));
}


void Score::restart()
{
	Player[0].scoreForPlayer=0;
	Player[1].scoreForPlayer=0;

}

void Score::update()
{

}

void Score::draw(sf::RenderTarget & target, sf::RenderStates states) const 
{
	target.draw(board);
	target.draw(Player[0].Tank);
	target.draw(Player[1].Tank);
	target.draw(Player[0].lblScoreForPlayer);
	target.draw(Player[1].lblScoreForPlayer);

}
