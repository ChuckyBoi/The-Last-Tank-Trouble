#pragma once
#include "../Player.h"

class MultiPlayerGame : public Player 
{



private:

	

	sf::Vector2f bulletCreatedPos;
	sf::Vector2f bulletCreatedDir;
	bool bulletCreated = false;
	bool player0Alive = true;
	bool player1Alive = true;



	std::vector<sf::RectangleShape > hLefts;
	std::vector<sf::RectangleShape > hRights;
	std::vector<sf::RectangleShape > hTops;
	std::vector<sf::RectangleShape > hDowns;

	std::vector<sf::RectangleShape > vLefts;
	std::vector<sf::RectangleShape > vRights;
	std::vector<sf::RectangleShape > vTops;
	std::vector<sf::RectangleShape > vDowns;





public:
	void setup(sf::RenderWindow& window);
	void set_map(Map map);
	void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void collideWithWalls(int pNumber, std::vector <sf::RectangleShape> verticalWalls, std::vector <sf::RectangleShape> horizontalWalls);
	void collideWithBox(int pNumber, sf::RectangleShape box);
	void createBullets(int pNumber,
		sf::RectangleShape box,
		std::vector<sf::RectangleShape> horizontalWalls,
		std::vector<sf::RectangleShape> verticalWalls,
		std::vector<sf::RectangleShape > hLefts,
		std::vector<sf::RectangleShape > hRights,
		std::vector<sf::RectangleShape > hTops,
		std::vector<sf::RectangleShape > hDowns,

		std::vector<sf::RectangleShape > vLefts,
		std::vector<sf::RectangleShape > vRights,
		std::vector<sf::RectangleShape > vTops,
		std::vector<sf::RectangleShape > vDowns);

	void moveBullet(int pNumber,
		sf::RectangleShape box,
		std::vector<sf::RectangleShape> horizontalWalls,
		std::vector<sf::RectangleShape> verticalWalls,
		std::vector<sf::RectangleShape > hLefts,
		std::vector<sf::RectangleShape > hRights,
		std::vector<sf::RectangleShape > hTops,
		std::vector<sf::RectangleShape > hDowns,

		std::vector<sf::RectangleShape > vLefts,
		std::vector<sf::RectangleShape > vRights,
		std::vector<sf::RectangleShape > vTops,
		std::vector<sf::RectangleShape > vDowns);


	void collideWithBullets(int pNumber);
	void explosion(int pNumber);
	void restartFromPlayers(int pNumber);


	sf::Vector2f getBulletStartingPos()
		{
			return  bulletCreatedPos;
		}
	sf::Vector2f getBulletStartingDir()
		{
			return  bulletCreatedDir;
		}
		
	void setCantRestart();


	void getOthersBullet();


	void checkIfYouCanShoot();
	bool getRestart();
	
	void setSpeed(int speed_, Tanks& Players_);
	void setDefaultSpeed(Tanks& Players_);
	void setBulletSpeed(int bulletSpeed_, Tanks& Players_);
	void setDefaultBulletSpeed(Tanks& Players_);
	void IncreaseBulletSize(int size, Tanks& players);
	void setDefaultBulletSize(Tanks& players);
	


	void set_score(Score score);
	void restart();
	void createIcon();
	void intersectsWithIcon();

	bool getCanRestart();
	void collisionWithBulletsForOtherPlayer(int pNumber);
	bool getIsAlive(int pNumber);
	int getShootingTimer(int pNumber);
	int getPlayersBulletSize(int pNumber);
	void createBulletsFor(int pNumber, sf::Vector2f bulletPos , sf::Vector2f Dir);







	sf::Vector2f playerGetBulletPos(int pNumber);
	sf::Vector2f playerGetPosition(int pNumber);
	void movePlayer(int pNumber);
	void setRotation(int pNumber, float rotation_);
	void playerSetPosition(int pNumber, sf::Vector2f pos);
	float getRotation(int pNumber);
	

	




};