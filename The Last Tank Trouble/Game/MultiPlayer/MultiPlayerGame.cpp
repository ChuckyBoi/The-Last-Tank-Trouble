#include "MultiPlayerGame.h"


MultiPlayerGame::MultiPlayerGame()
{

	Players[1].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("RedTank"));
	Players[2].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("GreenTank"));
	Players[3].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("BlueTank"));
	Players[4].Tank.setTexture(ResourceManagement::GetInstance()->RequestedTexture("YellowTank"));

	deltaTime = clock.restart().asSeconds();

	srand(time(NULL));

	/*
	Players[pNumber].circleForBulletCreation.setRadius(15);
	Players[pNumber].circleForBulletCreation.setRadius(15);

	Players[pNumber].circleForBulletCreation.setOrigin(Players[pNumber].circleForBulletCreation.getRadius(),
		Players[pNumber].circleForBulletCreation.getRadius());

	Players[pNumber].bulletObj.set_map(map);
	Players[pNumber].bulletObj.setup(window);
	Players[pNumber].bulletObjects.clear();

	Players[pNumber].Tank.setOrigin(Players[pNumber].size.x / 2, Players[pNumber].size.y / 2);
//	Players[pNumber].Tank.setRotation(random);
	//Players[pNumber].Tank.setPosition(randPos);
	*/

}

void MultiPlayerGame::setup(sf::RenderWindow& window,std::list<sf::UdpSocket*> clients)
{


	horizontalWalls = map.getHorizontalWalls();
	verticalWalls = map.getVerticalWalls();
	box = map.getBox();

	currentNumberOfPlayers = clients.size();



	for (int numOfClient = 1; numOfClient <= 4; numOfClient++)
	{
		Players[numOfClient].circleForBulletCreation.setRadius(15);
		Players[numOfClient].circleForBulletCreation.setRadius(15);

		Players[numOfClient].circleForBulletCreation.setOrigin(Players[numOfClient].circleForBulletCreation.getRadius(),
			Players[numOfClient].circleForBulletCreation.getRadius());

		Players[numOfClient].bulletObj.set_map(map);
		Players[numOfClient].bulletObj.setup(window);
		Players[numOfClient].bulletObjects.clear();

		Players[numOfClient].Tank.setOrigin(Players[1].size.x / 2, Players[1].size.y / 2);
		
	}


	score.setup(window);
	//roles.clear();
}
void MultiPlayerGame::handleEvents(const sf::Event& event, sf::RenderWindow& window)
{
}
void MultiPlayerGame::update(sf::RenderWindow& window)
{
}

void MultiPlayerGame::setClientFirstPosition(sf::RectangleShape box,int pNumber)
{
	int random;
	sf::Vector2f randPos;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> rangex(box.getPosition().x, box.getPosition().x+box.getSize().x);
	randPos.x= rangex(generator);  
	std::uniform_int_distribution<> rangey(box.getPosition().y, box.getPosition().y + box.getSize().y);
	randPos.y = rangey(generator);  // generates number in the range 1..6

	std::cout << box.getSize().y << std::endl;
	random = rand() % 360;

	Players[pNumber].circleForBulletCreation.setRadius(15);
	Players[pNumber].circleForBulletCreation.setRadius(15);

	Players[pNumber].circleForBulletCreation.setOrigin(Players[pNumber].circleForBulletCreation.getRadius(),Players[pNumber].circleForBulletCreation.getRadius());

	//Players[pNumber].bulletObj.set_map(map);
	//Players[pNumber].bulletObj.setup(window);
	//Players[pNumber].bulletObjects.clear();

	Players[pNumber].Tank.setOrigin(Players[pNumber].size.x / 2, Players[pNumber].size.y / 2);
	Players[pNumber].Tank.setRotation(random);
	Players[pNumber].Tank.setPosition(randPos);
}

void MultiPlayerGame::movePlayer(int pNumber)
{

	const int pixelsToMovePerSec=100;
	const float frameMovement = pixelsToMovePerSec * deltaTime;
	//if (Players[pNumber].alive)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Players[pNumber].Tank.rotate(-Players[pNumber].rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Players[pNumber].Tank.rotate(Players[pNumber].rotation);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Players[pNumber].Tank.move(Players[pNumber].DFT.x, Players[pNumber].DFT.y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Players[pNumber].Tank.move(-Players[pNumber].DFT.x, -Players[pNumber].DFT.y);
		}

		Players[pNumber].DFT = sf::Vector2f(cos(Players[pNumber].Tank.getRotation() * 3.14159265f / 180.f) * frameMovement
			, sin(Players[pNumber].Tank.getRotation() * 3.14159265f / 180.f) * frameMovement);

		Players[pNumber].DFB = sf::Vector2f(cos(Players[pNumber].Tank.getRotation() * 3.14159265f / 180.f) *
			frameMovement, sin(Players[pNumber].Tank.getRotation() * 3.14159265f / 180.f) * frameMovement);


		Players[pNumber].ShootingHole = Players[pNumber].Tank.getTransform().transformPoint(Players[pNumber].Tank.getSize().x, Players[pNumber].Tank.getSize().y / 2);
		Players[pNumber].circleForBulletCreation.setPosition(sf::Vector2f(Players[pNumber].ShootingHole.x, Players[pNumber].ShootingHole.y));

	
	//}
}
sf::Vector2f MultiPlayerGame::playerGetBulletPos(int pNumber)
{
	return  Players[pNumber].bulletObj.getShape().getPosition();
}

sf::Vector2f MultiPlayerGame::playerGetDir(int pNumber)
{
	return  Players[pNumber].bulletObj.getDirection();
}

sf::Uint16 MultiPlayerGame::playerGetPositionX(int pNumber)
{
	
		return Players[pNumber].Tank.getPosition().x;
	
}

sf::Uint16 MultiPlayerGame::playerGetPositionY(int pNumber)
{
	return Players[pNumber].Tank.getPosition().y;
}

sf::Uint16 MultiPlayerGame::playerGetRotation(int pNumber)
{
	return Players[pNumber].Tank.getRotation();

}

void MultiPlayerGame::playerSetPosition(int pNumber, sf::Vector2f pos)
{
	Players[pNumber].Tank.setPosition(pos);
}
float MultiPlayerGame::getRotation(int pNumber)
{
	return Players[pNumber].Tank.getRotation();
}

void MultiPlayerGame::CalculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();

}

void MultiPlayerGame::setRotation(int pNumber, float rotation_)
{
	Players[pNumber].Tank.setRotation(rotation_);
}
void MultiPlayerGame::set_map(Map map)
{
	this->map = map;
}


void MultiPlayerGame::collideWithWalls(int pNumber, std::vector <sf::RectangleShape> verticalWalls, std::vector <sf::RectangleShape> horizontalWalls)
{
		for (size_t i = 0; i < horizontalWalls.size(); i++)
		{
			if (Players[pNumber].Tank.getGlobalBounds().intersects(horizontalWalls[i].getGlobalBounds()))
			{
				if (Players[pNumber].Tank.getPosition().y - Players[pNumber].Tank.getSize().y / 2 < horizontalWalls[i].getPosition().y)
				{
					if (Players[pNumber].DFT.y < 0)
					{
						Players[pNumber].Tank.move(0, Players[pNumber].DFT.y);
					}
					else
					{
						Players[pNumber].Tank.move(0, -Players[pNumber].DFT.y);
					}
					//PREVENTS INTERSECTION FROM up
				}
				else  if (Players[pNumber].Tank.getPosition().y + Players[pNumber].Tank.getSize().y > horizontalWalls[i].getPosition().y)
				{
					//if (Players[pNumber].DFT.y < 0) { Players[pNumber].DFT.y *= -1; }

					if (Players[pNumber].DFT.y < 0)
					{
						Players[pNumber].Tank.move(0, -Players[pNumber].DFT.y);
					}
					else {
						Players[pNumber].Tank.move(0, +Players[pNumber].DFT.y);
					}
					//PREVENTS INTERSECTION FROM Down
				}
				if (Players[pNumber].Tank.getPosition().y - Players[pNumber].Tank.getSize().y / 2 < horizontalWalls[i].getPosition().y &&
					Players[pNumber].Tank.getPosition().y + Players[pNumber].Tank.getSize().y / 2 > horizontalWalls[i].getPosition().y)

				{
					if (Players[pNumber].Tank.getPosition().x < horizontalWalls[i].getPosition().x) {
						if (Players[pNumber].DFT.x < 0)
						{
							Players[pNumber].Tank.move(Players[pNumber].DFT.x, 0);
						}
						else
						{
							Players[pNumber].Tank.move(-Players[pNumber].DFT.x, 0);
						}

						//Prevents intersection from left side
					}
					else
					{
						if (Players[pNumber].DFT.x < 0)
						{
							Players[pNumber].Tank.move(-Players[pNumber].DFT.x, 0);
						}
						else {

							Players[pNumber].Tank.move(+Players[pNumber].DFT.x, 0);
						}
						//Prevents intersection from right side
					}
				}
			}
		}
		for (size_t j = 0; j < verticalWalls.size(); j++)
		{

			if (Players[pNumber].Tank.getGlobalBounds().intersects(verticalWalls[j].getGlobalBounds()))
			{

				if (Players[pNumber].Tank.getPosition().x - Players[pNumber].Tank.getSize().x / 2 < verticalWalls[j].getPosition().x)
				{
					if (Players[pNumber].DFT.x < 0) {
						Players[pNumber].Tank.move(Players[pNumber].DFT.x, 0);
					}
					else {
						Players[pNumber].Tank.move(-Players[pNumber].DFT.x, 0);
					}
					//PREVENTS INTERSECTION FROM up
				}
				else  if (Players[pNumber].Tank.getPosition().x + Players[pNumber].Tank.getSize().x > verticalWalls[j].getPosition().x)
				{
					if (Players[pNumber].DFT.x < 0)
					{
						Players[pNumber].Tank.move(-Players[pNumber].DFT.x, 0);
					}
					else {
						Players[pNumber].Tank.move(+Players[pNumber].DFT.x, 0);
					}
					//PREVENTS INTERSECTION FROM Down
				}
				if (Players[pNumber].Tank.getPosition().x - Players[pNumber].Tank.getSize().x / 2 < verticalWalls[j].getPosition().x &&
					Players[pNumber].Tank.getPosition().x + Players[pNumber].Tank.getSize().x / 2 > verticalWalls[j].getPosition().x)
				{
					if (Players[pNumber].Tank.getPosition().y < verticalWalls[j].getPosition().y) {
						if (Players[pNumber].DFT.y < 0)
						{
							Players[pNumber].Tank.move(0, Players[pNumber].DFT.y);
						}
						else
						{
							Players[pNumber].Tank.move(0, -Players[pNumber].DFT.y);
						}
						//Prevents intersection from left side
					}
					else
					{
						if (Players[pNumber].DFT.y < 0)
						{
							Players[pNumber].Tank.move(0, -Players[pNumber].DFT.y);
						}
						else {

							Players[pNumber].Tank.move(0, Players[pNumber].DFT.y);
						}
						//Prevents intersection from right side
					}
				}
			}
		}
}
void MultiPlayerGame::collideWithBox(int pNumber, sf::RectangleShape box)
{
	
		if (Players[pNumber].Tank.getPosition().x - Players[pNumber].Tank.getSize().x / 2 < box.getPosition().x)
		{
			if (Players[pNumber].DFT.x < 0)
			{
				Players[pNumber].Tank.move(-Players[pNumber].DFT.x, 0);
			}
			else {

				Players[pNumber].Tank.move(+Players[pNumber].DFT.x, 0);

			}

		}
		if (Players[pNumber].Tank.getPosition().x + Players[pNumber].Tank.getSize().x / 2 > box.getPosition().x + box.getSize().x)
		{

			if (Players[pNumber].DFT.x > 0) {

				Players[pNumber].Tank.move(-Players[pNumber].DFT.x, 0);
			}
			else {
				Players[pNumber].Tank.move(+Players[pNumber].DFT.x, 0);

			}
		}
		if (Players[pNumber].Tank.getPosition().y - Players[pNumber].Tank.getSize().y / 2 < box.getPosition().y)
		{

			if (Players[pNumber].DFT.y < 0)
			{
				Players[pNumber].Tank.move(0, -Players[pNumber].DFT.y);

			}
			else {
				Players[pNumber].Tank.move(0, +Players[pNumber].DFT.y);

			}

		}
		if (Players[pNumber].Tank.getPosition().y + Players[pNumber].Tank.getSize().y / 2 > box.getPosition().y + box.getSize().y)
		{

			if (Players[pNumber].DFT.y > 0)
			{
				Players[pNumber].Tank.move(0, -Players[pNumber].DFT.y);
			}
			else {
				Players[pNumber].Tank.move(0, +Players[pNumber].DFT.y);

			}
		}
	
}
void MultiPlayerGame::createBullets(int pNumber,sf::RectangleShape box,
	std::vector<sf::RectangleShape> horizontalWalls,
	std::vector<sf::RectangleShape> verticalWalls,

	std::vector<sf::RectangleShape > hLefts,
	std::vector<sf::RectangleShape > hRights,
	std::vector<sf::RectangleShape > hTops,
	std::vector<sf::RectangleShape > hDowns,

	std::vector<sf::RectangleShape > vLefts,
	std::vector<sf::RectangleShape > vRights,
	std::vector<sf::RectangleShape > vTops,
	std::vector<sf::RectangleShape > vDowns)
{

	Players[pNumber].shootTimer = Players[pNumber].clock.getElapsedTime().asMilliseconds();

	if (Players[pNumber].alive)
	{

		if (Players[pNumber].shootTimer > 500 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Players[pNumber].bulletObjects.size() < 5 && Players[pNumber].alive
			&& Players[pNumber].canShootH && Players[pNumber].canShootV && Players[pNumber].canShootB)
		{
			bulletCreated = true;

			Players[pNumber].bulletObj.setOrigin();
			Players[pNumber].bulletObj.setPosition(Players[pNumber].ShootingHole);//
			Players[pNumber].bulletObj.setDirection(Players[pNumber].DFB);//
			Players[pNumber].bulletObj.startTimer();
			Players[pNumber].bulletObjects.push_back(Bullet(Players[pNumber].bulletObj));
			Players[pNumber].clock.restart();

		

			bulletCreatedPos[pNumber] = Players[pNumber].ShootingHole;
			bulletCreatedDir[pNumber] = Players[pNumber].DFB;
		}
	}
	
}






void MultiPlayerGame::moveBullet(int pNumber, sf::RectangleShape box, std::vector<sf::RectangleShape> horizontalWalls, 
	std::vector<sf::RectangleShape> verticalWalls, std::vector<sf::RectangleShape> hLefts, std::vector<sf::RectangleShape> hRights,
	std::vector<sf::RectangleShape> hTops, std::vector<sf::RectangleShape> hDowns, std::vector<sf::RectangleShape> vLefts, 
	std::vector<sf::RectangleShape> vRights, std::vector<sf::RectangleShape> vTops, std::vector<sf::RectangleShape> vDowns)
{
	if (Players[pNumber].bulletObjects.size() > 0)
	{
		for (size_t i = 0; i < Players[pNumber].bulletObjects.size(); i++)
		{
			Players[pNumber].bulletObjects[i].bulletMovement();
			Players[pNumber].bulletObjects[i].multiPlayerCollisionWithWalls(horizontalWalls,verticalWalls,hLefts,hRights,hTops,hDowns,vLefts,vRights,vTops,vDowns);
			Players[pNumber].bulletObjects[i].multiPlayerCollisionWithBox(box);
			if (Players[pNumber].bulletObjects[i].getTime() > 10)
			{
				Players[pNumber].bulletObjects.erase(Players[pNumber].bulletObjects.begin() + i);
			}

		
		}
	
	}
}
bool MultiPlayerGame::getCanRestart()
{
	return canRestart;
}
void MultiPlayerGame::collisionWithBulletsForOtherPlayer(int pNumber)
{
	int theOtherOne = 0;
	if (pNumber == 1) { theOtherOne = 0; }
	else if (pNumber == 0) { theOtherOne = 1; }
	for (size_t i = 0; i < Players[pNumber].bulletObjects.size(); i++)
	{
		//is outside
		if (!Players[pNumber].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[pNumber].Tank.getGlobalBounds()))
		{
			Players[pNumber].bulletObjects[i].setOutsideTheTank();
		}

		if (Players[pNumber].bulletObjects.size() > 0)
		{
			if (Players[pNumber].bulletObjects[i].GetOutsideTheTank())
			{
				if (Players[pNumber].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[pNumber].Tank.getGlobalBounds()))
				{
					Players[pNumber].alive = false;
					Players[pNumber].bulletObjects.erase(Players[pNumber].bulletObjects.begin() + i);
					score.increaseScoreForPlayer(theOtherOne);
					Players[pNumber].explosionS.playSound();


					//score.increaseScoreForPlayer1();
					//Players[0].score.increaseScore();
					//can work to fix this
				}
			}
		}
	}
	for (size_t i = 0; i < Players[pNumber].bulletObjects.size(); i++)
	{
		if (Players[pNumber].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[theOtherOne].Tank.getGlobalBounds()))
		{
			Players[theOtherOne].alive = false;
			Players[pNumber].bulletObjects.erase(Players[pNumber].bulletObjects.begin() + i);

			score.increaseScoreForPlayer(pNumber);
			Players[pNumber].explosionS.playSound();




		}
	}
}
bool MultiPlayerGame::getIsAlive(int pNumber)
{
	return Players[pNumber].alive;
}
int MultiPlayerGame::getShootingTimer(int pNumber)
{
	return Players[pNumber].shootTimer;
}
int MultiPlayerGame::getPlayersBulletSize(int pNumber)
{
	return Players[pNumber].bulletObjects.size();
}
void MultiPlayerGame::createBulletsFor(int pNumber, sf::Vector2f bulletPos, sf::Vector2f Dir)
{
	Players[pNumber].shootTimer = Players[pNumber].clock.getElapsedTime().asMilliseconds();

			Players[pNumber].bulletObj.setOrigin();
			Players[pNumber].bulletObj.setPosition(bulletPos);//
			Players[pNumber].bulletObj.setDirection(Dir);//
			Players[pNumber].bulletObj.startTimer();
			Players[pNumber].bulletObjects.push_back(Bullet(Players[pNumber].bulletObj));
			Players[pNumber].clock.restart();

}
void MultiPlayerGame::collideWithBullets(int pNumber)
{
	int theOtherOne=0;
	if (pNumber == 1) { theOtherOne = 0; }
	else if (pNumber == 0) { theOtherOne = 1; }
	for (size_t i = 0; i < Players[pNumber].bulletObjects.size(); i++)
	{
		//is outside
		if (!Players[pNumber].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[pNumber].Tank.getGlobalBounds()))
		{
			Players[pNumber].bulletObjects[i].setOutsideTheTank();
		}

		if (Players[pNumber].bulletObjects.size() > 0)
		{
			if (Players[pNumber].bulletObjects[i].GetOutsideTheTank())
			{
				if (Players[pNumber].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[pNumber].Tank.getGlobalBounds()))
				{
					Players[pNumber].alive = false;
					Players[pNumber].bulletObjects.erase(Players[pNumber].bulletObjects.begin() + i);
					score.increaseScoreForPlayer(theOtherOne);
					Players[pNumber].explosionS.playSound();


					//score.increaseScoreForPlayer1();
					//Players[0].score.increaseScore();
					//can work to fix this
				}
			}
		}
	}
	for (size_t i = 0; i < Players[pNumber].bulletObjects.size(); i++)
	{
		if (Players[pNumber].bulletObjects[i].getShape().getGlobalBounds().intersects(Players[theOtherOne].Tank.getGlobalBounds()))
		{
			Players[theOtherOne].alive = false;
			Players[pNumber].bulletObjects.erase(Players[pNumber].bulletObjects.begin() + i);

			score.increaseScoreForPlayer(pNumber);
			Players[pNumber].explosionS.playSound();

			


		}
	}
	
}
void MultiPlayerGame::explosion(int pNumber)
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
void MultiPlayerGame::restartFromPlayers(int pNumber)
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
void MultiPlayerGame::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	/*
	for (auto& i : roles)
	{
		if (i->getActive())
		{
			i->draw(target, states);
		}
	}
	*/
	for (int player = 1; player <= 4; player++) {

		for (auto& i : Players[player].bulletObjects)
		{
			i.draw(target, states);
		}

	}
	target.draw(score);

	/*
	for (int numOfClient = 1; numOfClient <= nr; numOfClient++)
	{
		target.draw(Players[numOfClient].Tank, states);

		std::cout << "HEY" << nr << std::endl;
	}
	*/


}

void MultiPlayerGame::drawEverything(sf::RenderTarget& target, sf::RenderStates states,int nr) const
{
	

	for (int numOfClient = 1; numOfClient <= nr; numOfClient++)
	{
		target.draw(Players[numOfClient].Tank, states);
	}
}

void MultiPlayerGame::drawPlayer(sf::RenderTarget& target, sf::RenderStates states, int nr) const
{

	target.draw(Players[nr].Tank, states);
}



void MultiPlayerGame::setCantRestart()
{
	canRestart = false;
}
