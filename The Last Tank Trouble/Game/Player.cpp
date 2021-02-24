#include "Player.h"
#include <string>

Player::Player()
{

	//Players[0].texture.loadFromFile("Images/RedTank.png");	
	//Players[1].texture.loadFromFile("Images/GreenTank.png");

	Players[0].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("RedTank"));
	//Players[0].Tank.setTexture(&Players[0].texture);

	Players[1].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("GreenTank"));
	//Players[1].Tank.setTexture(&Players[1].texture);
	//Players[1].set
	

	Players[0].circleForBulletCreation.setRadius(15);
	Players[1].circleForBulletCreation.setRadius(15);

	Players[0].circleForBulletCreation.setOrigin(Players[0].circleForBulletCreation.getRadius(), Players[0].circleForBulletCreation.getRadius());
	Players[1].circleForBulletCreation.setOrigin(Players[1].circleForBulletCreation.getRadius(), Players[1].circleForBulletCreation.getRadius());

	music.openFromFile("Audio/soviet.ogg");
	//music.play();
}
void Player::setup(sf::RenderWindow& window)
{
	horizontalWalls = map.getHorizontalWalls();
	verticalWalls = map.getVerticalWalls();
	box = map.getBox();

	for (int playerNum = 0; playerNum < 2; playerNum++)
	{
		Players[playerNum].bulletObj.set_map(map);
		Players[playerNum].bulletObj.setup(window);
		Players[playerNum].bulletObjects.clear();
	}

	Players[0].Tank.setOrigin(Players[0].size.x / 2, Players[0].size.y / 2);
	Players[0].Tank.setPosition(box.getPosition().x + Players[0].Tank.getSize().x/2 , box.getPosition().y + box.getSize().y / 2);
	Players[0].Tank.setRotation(0);

	Players[1].Tank.setOrigin(Players[1].size.x / 2, Players[1].size.y / 2);
	Players[1].Tank.setRotation(180);
	Players[1].Tank.setPosition(box.getPosition().x + box.getSize().x - Players[1].Tank.getSize().x/2, box.getPosition().y + box.getSize().y / 2);

	score.setup(window);
	roles.clear();
}
bool Player::getRestart()
{
	return canRestart;
}
void Player::setCantRestart()
{
	canRestart = false;
}
void Player::set_score(Score score)
{
	this->score = score;
}
void Player::handleInput(const sf::Event& event, const sf::Vector2f& mouse)
{
}
void Player::Update()
{
		Move();
		collideWithWalls();
		collideWithBox();
		createBullets();
		collideWithBullets();
		explosion();
		restartFromPlayers();
		checkIfYouCanShoot();
		intersectsWithIcon();
		createIcon();


		
}
void Player::Move()
{
	if (Players[0].alive && Players[1].alive) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Players[0].Tank.rotate(-Players[0].rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Players[0].Tank.rotate(Players[0].rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Players[0].Tank.move(Players[0].DFT.x, Players[0].DFT.y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Players[0].Tank.move(-Players[0].DFT.x, -Players[0].DFT.y);
		}

		Players[0].DFT = sf::Vector2f(cos(Players[0].Tank.getRotation() * 3.14159265f / 180.f) *
			Players[0].speed, sin(Players[0].Tank.getRotation() * 3.14159265f / 180.f) * Players[0].speed);

		Players[0].DFB = sf::Vector2f(cos(Players[0].Tank.getRotation() * 3.14159265f / 180.f) *
			Players[0].bulletSpeed, sin(Players[0].Tank.getRotation() * 3.14159265f / 180.f) * Players[0].bulletSpeed);


		Players[0].ShootingHole = Players[0].Tank.getTransform().transformPoint(Players[0].Tank.getSize().x, Players[0].Tank.getSize().y /2);
		Players[0].circleForBulletCreation.setPosition(sf::Vector2f(Players[0].ShootingHole.x, Players[0].ShootingHole.y));
		

	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Players[1].Tank.rotate(-Players[1].rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Players[1].Tank.rotate(Players[1].rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Players[1].Tank.move(Players[1].DFT.x, Players[1].DFT.y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Players[1].Tank.move(-Players[1].DFT.x, -Players[1].DFT.y);
		}

		Players[1].DFT = sf::Vector2f(cos(Players[1].Tank.getRotation() * 3.14159265f / 180.f) *
			Players[1].speed, sin(Players[1].Tank.getRotation() * 3.14159265f / 180.f) * Players[1].speed);

		Players[1].DFB = sf::Vector2f(cos(Players[1].Tank.getRotation() * 3.14159265f / 180.f) *
			Players[1].bulletSpeed, sin(Players[1].Tank.getRotation() * 3.14159265f / 180.f) * Players[1].bulletSpeed);


		Players[1].ShootingHole = Players[1].Tank.getTransform().transformPoint(Players[1].Tank.getSize().x , Players[1].Tank.getSize().y / 2);
		Players[1].circleForBulletCreation.setPosition(sf::Vector2f(Players[1].ShootingHole.x, Players[1].ShootingHole.y));

	}
}
void Player::collideWithWalls()
{
	for (int playerNum = 0; playerNum < 2; playerNum++)
	{
		for (size_t i = 0; i < horizontalWalls.size(); i++)
		{
			if (Players[playerNum].Tank.getGlobalBounds().intersects(horizontalWalls[i].getGlobalBounds()))
			{
				if (Players[playerNum].Tank.getPosition().y - Players[playerNum].Tank.getSize().y / 2 < horizontalWalls[i].getPosition().y)
				{
					if (Players[playerNum].DFT.y < 0)
					{
						Players[playerNum].Tank.move(0, Players[playerNum].DFT.y);
					}
					else
					{
						Players[playerNum].Tank.move(0, -Players[playerNum].DFT.y);
					}
					//PREVENTS INTERSECTION FROM up
				}
				else  if (Players[playerNum].Tank.getPosition().y + Players[playerNum].Tank.getSize().y > horizontalWalls[i].getPosition().y)
				{
					//if (Players[playerNum].DFT.y < 0) { Players[playerNum].DFT.y *= -1; }

					if (Players[playerNum].DFT.y < 0)
					{
						Players[playerNum].Tank.move(0, -Players[playerNum].DFT.y);
					}
					else {
						Players[playerNum].Tank.move(0, +Players[playerNum].DFT.y);
					}
					//PREVENTS INTERSECTION FROM Down
				}
				if (Players[playerNum].Tank.getPosition().y - Players[playerNum].Tank.getSize().y / 2 < horizontalWalls[i].getPosition().y &&
					Players[playerNum].Tank.getPosition().y + Players[playerNum].Tank.getSize().y / 2 > horizontalWalls[i].getPosition().y)

				{
					if (Players[playerNum].Tank.getPosition().x < horizontalWalls[i].getPosition().x) {
						if (Players[playerNum].DFT.x < 0)
						{
							Players[playerNum].Tank.move(Players[playerNum].DFT.x, 0);
						}
						else
						{
							Players[playerNum].Tank.move(-Players[playerNum].DFT.x, 0);
						}

						//Prevents intersection from left side
					}
					else
					{
						if (Players[playerNum].DFT.x < 0)
						{
							Players[playerNum].Tank.move(-Players[playerNum].DFT.x, 0);
						}
						else {

							Players[playerNum].Tank.move(+Players[playerNum].DFT.x, 0);
						}
						//Prevents intersection from right side
					}
				}
			}
		}
		for (size_t j = 0; j < verticalWalls.size(); j++)
		{
			
			if (Players[playerNum].Tank.getGlobalBounds().intersects(verticalWalls[j].getGlobalBounds()))
			{
				
				if (Players[playerNum].Tank.getPosition().x - Players[playerNum].Tank.getSize().x / 2 < verticalWalls[j].getPosition().x)
				{
					if (Players[playerNum].DFT.x < 0) {
						Players[playerNum].Tank.move(Players[playerNum].DFT.x, 0);
					}
					else {
						Players[playerNum].Tank.move(-Players[playerNum].DFT.x, 0);
					}
					//PREVENTS INTERSECTION FROM up
				}
				else  if (Players[playerNum].Tank.getPosition().x + Players[playerNum].Tank.getSize().x > verticalWalls[j].getPosition().x)
				{
					if (Players[playerNum].DFT.x < 0)
					{
						Players[playerNum].Tank.move(-Players[playerNum].DFT.x, 0);
					}
					else {
						Players[playerNum].Tank.move(+Players[playerNum].DFT.x, 0);
					}
					//PREVENTS INTERSECTION FROM Down
				}
				if (Players[playerNum].Tank.getPosition().x - Players[playerNum].Tank.getSize().x / 2 < verticalWalls[j].getPosition().x &&
					Players[playerNum].Tank.getPosition().x + Players[playerNum].Tank.getSize().x / 2 > verticalWalls[j].getPosition().x)
				{
					if (Players[playerNum].Tank.getPosition().y < verticalWalls[j].getPosition().y) {
						if (Players[playerNum].DFT.y < 0)
						{
							Players[playerNum].Tank.move(0, Players[playerNum].DFT.y);
						}
						else
						{
							Players[playerNum].Tank.move(0, -Players[playerNum].DFT.y);
						}
						//Prevents intersection from left side
					}
					else
					{
						if (Players[playerNum].DFT.y < 0)
						{
							Players[playerNum].Tank.move(0, -Players[playerNum].DFT.y);
						}
						else {

							Players[playerNum].Tank.move(0, Players[playerNum].DFT.y);
						}
						//Prevents intersection from right side
					}
				}
			}
		}
	}
}
void Player::collideWithBox()
{
	for (int playerNum = 0; playerNum < 2; playerNum++)
	{
		if (Players[playerNum].Tank.getPosition().x - Players[playerNum].Tank.getSize().x / 2 < box.getPosition().x)
		{
			if (Players[playerNum].DFT.x < 0)
			{
				Players[playerNum].Tank.move(-Players[playerNum].DFT.x, 0);
			}
			else {

				Players[playerNum].Tank.move(+Players[playerNum].DFT.x, 0);

			}

		}
		if (Players[playerNum].Tank.getPosition().x + Players[playerNum].Tank.getSize().x / 2 > box.getPosition().x + box.getSize().x)
		{
			
			if (Players[playerNum].DFT.x > 0) {

				Players[playerNum].Tank.move(-Players[playerNum].DFT.x, 0);
			}
			else {
				Players[playerNum].Tank.move(+Players[playerNum].DFT.x, 0);

			}
		}
		if (Players[playerNum].Tank.getPosition().y - Players[playerNum].Tank.getSize().y / 2 < box.getPosition().y)
		{
			
			if (Players[playerNum].DFT.y < 0)
			{
				Players[playerNum].Tank.move(0, -Players[playerNum].DFT.y);

			}
			else {
				Players[playerNum].Tank.move(0, +Players[playerNum].DFT.y);

			}

		}
		if (Players[playerNum].Tank.getPosition().y + Players[playerNum].Tank.getSize().y / 2 > box.getPosition().y + box.getSize().y)
		{
			
			if (Players[playerNum].DFT.y > 0)
			{
				Players[playerNum].Tank.move(0, -Players[playerNum].DFT.y);
			}
			else {
				Players[playerNum].Tank.move(0, +Players[playerNum].DFT.y);

			}
		}
	}
}
void Player::set_map(Map map)
{
	this->map = map;
}
void Player::restart()
{
	setDefaultBulletSpeed(Players[0]);
	setDefaultSpeed(Players[0]);
	setDefaultBulletSpeed(Players[1]);
	setDefaultSpeed(Players[1]);
	score.restart();
}
void Player::createBullets()
{
		Players[0].shootTimer = Players[0].clock.getElapsedTime().asMilliseconds();
		Players[1].shootTimer = Players[1].clock.getElapsedTime().asMilliseconds();

		if (Players[0].alive && Players[1].alive)
		{
		
			if (Players[0].shootTimer > 500 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Players[0].bulletObjects.size() < 5 && Players[0].alive
				&&Players[0].canShootH && Players[0].canShootV && Players[0].canShootB)
			{

				Players[0].bulletObj.setOrigin();
				Players[0].bulletObj.setPosition(Players[0].ShootingHole);
				Players[0].bulletObj.setDirection(Players[0].DFB);
				Players[0].bulletObj.startTimer();
				Players[0].bulletObjects.push_back(Bullet(Players[0].bulletObj));
				Players[0].clock.restart();
			}
			if (Players[0].bulletObjects.size() > 0)
			{
				for (size_t i = 0; i < Players[0].bulletObjects.size(); i++)
				{
					Players[0].bulletObjects[i].bulletMovement();
					Players[0].bulletObjects[i].collisionWithWalls();
					Players[0].bulletObjects[i].collisionWithBox();
					if (Players[0].bulletObjects[i].getTime() > 10)
					{
						Players[0].bulletObjects.erase(Players[0].bulletObjects.begin() + i);
					}
				}
			}
			if (Players[1].shootTimer > 500 && sf::Keyboard::isKeyPressed(sf::Keyboard::P) && Players[1].bulletObjects.size() < 5 && Players[1].alive
				&& Players[1].canShootH && Players[1].canShootV && Players[1].canShootB)
			{
				Players[1].bulletObj.setOrigin();
				Players[1].bulletObj.setPosition(Players[1].ShootingHole);
				Players[1].bulletObj.setDirection(Players[1].DFB);
				Players[1].bulletObj.startTimer();
				Players[1].bulletObjects.push_back(Bullet(Players[1].bulletObj));
				Players[1].clock.restart();
			}
			if (Players[1].bulletObjects.size() > 0)
			{
				for (size_t i = 0; i < Players[1].bulletObjects.size(); i++)
				{

					Players[1].bulletObjects[i].bulletMovement();
					Players[1].bulletObjects[i].collisionWithWalls();
					Players[1].bulletObjects[i].collisionWithBox();
					if (Players[1].bulletObjects[i].getTime() > 10)
					{
						Players[1].bulletObjects.erase(Players[1].bulletObjects.begin() + i);
					}
				}
			}
		}
}
void Player::collideWithBullets()
{

	for (size_t i = 0; i < Players[1].bulletObjects.size(); i++)
	{
		//is outside
		if (!Players[1].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[1].Tank.getGlobalBounds()))
		{
			Players[1].bulletObjects[i].setOutsideTheTank();
		}

		if (Players[1].bulletObjects.size() > 0)
		{
			if (Players[1].bulletObjects[i].GetOutsideTheTank())
			{
				if (Players[1].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[1].Tank.getGlobalBounds()))
				{
					Players[1].alive = false;
					Players[1].bulletObjects.erase(Players[1].bulletObjects.begin() + i);
					score.increaseScoreForPlayer(0);
				    Players[0].explosionS.playSound();


					//score.increaseScoreForPlayer1();
					//Players[0].score.increaseScore();
					//can work to fix this
				}
			}
		}
	}
	for (size_t i = 0; i < Players[1].bulletObjects.size(); i++)
	{
		if (Players[1].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[0].Tank.getGlobalBounds()))
		{
			Players[0].alive = false;
			Players[1].bulletObjects.erase(Players[1].bulletObjects.begin() + i);

			score.increaseScoreForPlayer(1);
			Players[1].explosionS.playSound();


		}
	}
	for (size_t i = 0; i < Players[0].bulletObjects.size(); i++)
	{

		if (!Players[0].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[0].Tank.getGlobalBounds()))
		{
			Players[0].bulletObjects[i].setOutsideTheTank();
		}
		if (Players[0].bulletObjects[i].GetOutsideTheTank())
		{
			if (Players[0].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[0].Tank.getGlobalBounds()))
			{
				Players[0].alive = false;
				Players[0].bulletObjects.erase(Players[0].bulletObjects.begin() + i);

				score.increaseScoreForPlayer(1);
				Players[1].explosionS.playSound();


			}
		}
	}
	for (size_t i = 0; i < Players[0].bulletObjects.size(); i++)
	{
		if (Players[0].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[1].Tank.getGlobalBounds()))
		{

			Players[1].alive = false;
			Players[0].bulletObjects.erase(Players[0].bulletObjects.begin() + i);
			score.increaseScoreForPlayer(0);
			Players[0].explosionS.playSound();
		}
	}
}
void Player::explosion()
{
	for (int playerNum = 0; playerNum < 2; playerNum++)
	{
		if (!Players[playerNum].alive)
		{
			Players[playerNum].explosionS.setPosition(sf::Vector2f(Players[playerNum].Tank.getPosition().x, Players[playerNum].Tank.getPosition().y));
			if (!Players[playerNum].explosionS.isEnd()) 
			{
				Players[playerNum].explosionS.update();
			}
		}
	}
}
void Player::restartFromPlayers()
{
		if (Players[0].explosionS.isEnd())
		{
			if (!Players[0].alive)
			{
				Players[0].explosionS.startAgain();
				Players[0].alive = true;
				canRestart = true;
				//setup(window);
			}
		}
		if (Players[1].explosionS.isEnd())
		{
			if (!Players[1].alive)
			{
				Players[1].explosionS.startAgain();
				Players[1].alive = true;
				canRestart = true;
				//setup(window);
			}
		}
	
}
void Player::checkIfYouCanShoot()
{
	for (playerNum = 0; playerNum < 2; playerNum++)
	{
		for (size_t i = 0; i < horizontalWalls.size(); i++)
		{

			if (Players[playerNum].circleForBulletCreation.getGlobalBounds().intersects(horizontalWalls[i].getGlobalBounds()))
			{
				Players[playerNum].canShootH = false;
				break;
			}
			else
			{
				Players[playerNum].canShootH = true;
			}
		}
		for (size_t i = 0; i < verticalWalls.size(); i++)
		{
			if (Players[playerNum].circleForBulletCreation.getGlobalBounds().intersects(verticalWalls[i].getGlobalBounds()))
			{
				Players[playerNum].canShootV = false;
				break;
			}
			else
			{
				Players[playerNum].canShootV = true;
			}
		}
		if (Players[playerNum].ShootingHole.x < box.getPosition().x + 10 || Players[playerNum].ShootingHole.x > box.getPosition().x + box.getSize().x - 10
			|| Players[playerNum].ShootingHole.y < box.getPosition().y + 10 || Players[playerNum].ShootingHole.y > box.getPosition().y + box.getSize().y - 10)
		{
			Players[playerNum].canShootB = false;
		}
		else
		{
			Players[playerNum].canShootB = true;
		}
	}
}

void Player::setSpeed(int speed_, Tanks &Players_)
{
		Players_.speed = speed_;
}
void Player::setDefaultSpeed(Tanks& Players_)
{
	Players_.speed = 3;
}
void Player::setBulletSpeed(int bulletSpeed_, Tanks& Players_)
{
	Players_.bulletSpeed = bulletSpeed_;
}
void Player::setDefaultBulletSpeed(Tanks& Players_)
{
	Players_.bulletSpeed = 4;
}
void Player::IncreaseBulletSize(int size, Tanks& players)
{
	players.bulletObj.setBulletSize(size);
}
void Player::setDefaultBulletSize(Tanks& players)
{
	players.bulletObj.setBulletSize(5);
}
void Player::createIcon()
{
	if (roles.size() < 50 && role.getSpawnClock() > 5)
	{
		roles.push_back(Icons::make_stooge());
		role.restartSpawnClock();
	}
	for (size_t i = 0; i < roles.size(); i++)
	{
		if (!roles[i]->getCreated())
		{
			roles[i]->set_map(map);
			roles[i]->setup();
			roles[i]->setPosition();
			roles[i]->setCreated(true);
		}
	}
}
void Player::intersectsWithIcon()
{
	for (size_t i = 0; i < roles.size(); i++)
	{
		if (roles[i]->getActive()) {
			if (Players[0].Tank.getGlobalBounds().intersects(roles[i]->entity().getGlobalBounds()))
			{
				roles[i]->setTarget("P0");
				if (roles[i]->getTypeOfPower() == "speed")
				{
					setSpeed(6, Players[0]);
				}
				else if (roles[i]->getTypeOfPower() == "bulletSpeed")
				{
					setBulletSpeed(8, Players[0]);
				}
				else if (roles[i]->getTypeOfPower() == "bulletSizeIncrease")
				{
					IncreaseBulletSize(27, Players[0]);
				}
				roles[i]->setActive(false);
			}
			if (Players[1].Tank.getGlobalBounds().intersects(roles[i]->entity().getGlobalBounds()))
			{
				roles[i]->setTarget("P1");
				if (roles[i]->getTypeOfPower() == "speed")
				{
					setSpeed(6, Players[1]);
				}
				else if (roles[i]->getTypeOfPower() == "bulletSpeed")
				{
					setBulletSpeed(8, Players[1]);
				}
				else if (roles[i]->getTypeOfPower() == "bulletSizeIncrease")
				{
					IncreaseBulletSize(27, Players[1]);
				}
				roles[i]->setActive(false);
			}
		}
		if (roles[i]->getActive())
		{
			roles[i]->restartLastingClock();
		}
		if (roles[i]->getLastingClock() > 10)
		{
			if (roles[i]->getTarget() == "P0") {
				if (roles[i]->getTypeOfPower() == "speed")
				{
					setDefaultSpeed(Players[0]);
				}
				if (roles[i]->getTypeOfPower() == "bulletSpeed")
				{
					setDefaultBulletSpeed(Players[0]);
				}
			}
			if (roles[i]->getTarget() == "P1") {

				if (roles[i]->getTypeOfPower() == "speed")
				{
					setDefaultSpeed(Players[1]);
				}
				if (roles[i]->getTypeOfPower() == "bulletSpeed")
				{
					setDefaultBulletSpeed(Players[1]);
				}
			}
			roles.erase(roles.begin() + i);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||(sf::Keyboard::isKeyPressed(sf::Keyboard::P)))
		{
			if (roles[i]->getTypeOfPower() == "bulletSizeIncrease")
			{
				if (roles[i]->getTarget() == "P0")
				{
					setDefaultBulletSize(Players[0]);
				}
				if (roles[i]->getTarget() == "P1")
				{
					setDefaultBulletSize(Players[1]);
				}
			}
		}
	}
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto &i :roles)
	{
		if (i->getActive())
		{
			i->draw(target, states);
		}
	}
	for (auto& i : Players[0].bulletObjects)
	{
		i.draw(target, states);
	}
	for (auto& i : Players[1].bulletObjects)
	{
		i.draw(target, states);
	}
	
	target.draw(score);
	
	if (!Players[0].alive)
	{	
		target.draw(Players[0].explosionS);
	}
	else 
	{
		target.draw(Players[0].Tank, states);
	}
	if (!Players[1].alive)
	{
		target.draw(Players[1].explosionS);
	}
	else 
	{
		target.draw(Players[1].Tank, states);
	}
	
}