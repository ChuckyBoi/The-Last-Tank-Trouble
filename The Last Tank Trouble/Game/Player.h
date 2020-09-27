#pragma once
#include "Bullet.h"
#include "Explosion.h"
#include "Score.h"

#include "../Resources/ResourceManagement.h"

//#include "PowerUps/Speed.h"
//#include "PowerUps/BulletSpeed.h"
#include "..//Game/PowerUps/Icons.h"
#include "..//Game/PowerUps/SpeedPowerUp.h"
#include "..//Game/PowerUps/BulletSpeedPowerUp.h"






class Player : public sf::Drawable
{

protected:

	int playerNum=0;
	bool canRestart = false;

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

		int speed = 3;
		float bulletSpeed = 4;
		float rotation = 4;

		int shootTimer = 0;
		bool canShootV = true;
		bool canShootH = true;
		bool canShootB = true;

		bool alive = true;

		Explosion explosionS;
		Bullet bulletObj;
		std::vector<Bullet>bulletObjects;
		
	}Players[2];

	int number = 0;

	Icons role;
	std::vector<Icons*> roles;

	Map map;
	Score score;
	sf::Music music;
	sf::SoundBuffer bufferWall;
	sf::Sound wall;

	std::vector<sf::RectangleShape > verticalWalls;
	std::vector<sf::RectangleShape > horizontalWalls;
	sf::RectangleShape box;

public:
	Player();


	void setup(sf::RenderWindow& window);
	void handleInput(const sf::Event& event, const sf::Vector2f& mouse);
	void Update();
	void Move();

	void collideWithWalls();
	void collideWithBox();
	void createBullets();
	void collideWithBullets();
	void explosion();
	void restartFromPlayers();
	void checkIfYouCanShoot();
	bool getRestart();
	void setCantRestart();
	void setSpeed(int speed_, Tanks &Players_);
	void setDefaultSpeed(Tanks& Players_);
	void setBulletSpeed(int bulletSpeed_, Tanks& Players_);
	void setDefaultBulletSpeed(Tanks& Players_);
	void IncreaseBulletSize(int size,Tanks& players);
	void setDefaultBulletSize(Tanks& players);
	void set_map(Map map);
	void set_score(Score score);
	void restart();
	void createIcon();
	void intersectsWithIcon();

	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	


};