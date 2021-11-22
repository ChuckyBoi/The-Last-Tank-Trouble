#pragma once
#include "../Player.h"
#include <SFML/Network.hpp>
#include <list>

class MultiPlayerGame :public sf::Drawable
{

	

private:

	int nrMaxOfPlayers=5;
	int currentNumberOfPlayers;
	int clientID;

	struct Tanks
	{
		sf::Clock clock;

		sf::Vector2f size{ 40 ,30 };//the Size
		sf::RectangleShape Tank{ size };

		sf::Vector2f DFT;//DirectionForTank
		sf::Vector2f DFB;//DirectionForBullets
		sf::Vector2f ShootingHole;
		std::vector<sf::Vector2f> Directions;
		sf::CircleShape circleForBulletCreation;

		int speed = 1;
		int numOfBullets = 5;
		int speedOfShooting = 500;
		float bulletSpeed = 3;
		float rotation = 2;

		int shootTimer = 0;
		bool canShootV = true;
		bool canShootH = true;
		bool canShootB = true;

		bool alive = true;

		Explosion explosionS;

		Bullet bulletObj;
		std::vector<Bullet>bulletObjects;

	}Players[5];

	sf::Clock clock;
	float deltaTime;

	bool canRestart = false;
	sf::Music music;
	sf::SoundBuffer bufferWall;
	sf::Sound wall;
	bool bulletCreated = false;
	bool player0Alive = true;
	bool player1Alive = true;

	Map map;
	Score score;



	std::vector<sf::RectangleShape > verticalWalls;
	std::vector<sf::RectangleShape > horizontalWalls;
	sf::RectangleShape box;

	sf::Vector2f bulletCreatedPos[5];
	sf::Vector2f bulletCreatedDir[5];

	std::vector<sf::RectangleShape > hLefts;
	std::vector<sf::RectangleShape > hRights;
	std::vector<sf::RectangleShape > hTops;
	std::vector<sf::RectangleShape > hDowns;

	std::vector<sf::RectangleShape > vLefts;
	std::vector<sf::RectangleShape > vRights;
	std::vector<sf::RectangleShape > vTops;
	std::vector<sf::RectangleShape > vDowns;


public:

	 MultiPlayerGame();
	void setup(sf::RenderWindow& window, std::list<sf::UdpSocket*> clients);
	void setClientFirstPosition(sf::RectangleShape box, int pNumber);

	void set_map(Map map);

	void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawEverything(sf::RenderTarget& target, sf::RenderStates states,int nr) const;
	void drawPlayer(sf::RenderTarget& target, sf::RenderStates states, int nr) const;


//	void drawPlayer(sf::RenderTarget& target, sf::RenderStates states,int pNumber) const;


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


	sf::Vector2f getBulletStartingPos(int pNumber)
		{
			return  bulletCreatedPos[pNumber];
		}
	sf::Vector2f getBulletStartingDir(int pNumber)
		{
			return  bulletCreatedDir[pNumber];
		}
		
	void setCantRestart();


	void getOthersBullet();
	void checkIfYouCanShoot();
	bool getRestart();
	
	/*
	void setSpeed(int speed_, Tanks& Players_);
	void setDefaultSpeed(Tanks& Players_);
	void setBulletSpeed(int bulletSpeed_, Tanks& Players_);
	void setDefaultBulletSpeed(Tanks& Players_);
	void IncreaseBulletSize(int size, Tanks& players);
	void setDefaultBulletSize(Tanks& players);
	
	*/

	/*
	void set_score(Score score);
	void restart();
	void createIcon();
	void intersectsWithIcon();
	*/

	bool getCanRestart();
	void collisionWithBulletsForOtherPlayer(int pNumber);
	bool getIsAlive(int pNumber);
	int getShootingTimer(int pNumber);
	int getPlayersBulletSize(int pNumber);
	void createBulletsFor(int pNumber, sf::Vector2f bulletPos , sf::Vector2f Dir);



	sf::Vector2f playerGetBulletPos(int pNumber);
	sf::Uint16 playerGetPositionX(int pNumber);
	sf::Uint16 playerGetPositionY(int pNumber);
	sf::Uint16	playerGetRotation(int pNumber);

	sf::Vector2f playerGetDir(int pNumber);

	void movePlayer(int pNumber);
	void setRotation(int pNumber, float rotation_);
	void playerSetPosition(int pNumber, sf::Vector2f pos);
	float getRotation(int pNumber);
	

	


	void CalculateDeltaTime();

};