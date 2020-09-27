#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "MultiPlayerGame.h"
#include <thread>


class MultiPlayer :public sf::Drawable
{

	
private:
	int cases = 1;
	int casesForThem = 2;

	sf::Vector2f bulletPos, bulletDir;


	


	sf::UdpSocket client_;
	sf::UdpSocket socket_;


	sf::Vector2f previousPos;
	float previousRotation;






	char buffer[1024];

	std::size_t received = 0;
	sf::IpAddress sender;
	unsigned short port;





	


	bool isActive = false;

	bool isServer = false;
	bool isClient = false;

	bool isConnectedToClient = false;
	bool isConnectedToServer = false;



	bool keyIsPressed = false;
	bool SpaceIsPressed = false;


	Map map;
	MultiPlayerGame player1;



	sf::RectangleShape horizontalWall;
	sf::RectangleShape verticalWall;


	sf::RectangleShape box;

	std::vector <sf::RectangleShape> verticalWalls;
	std::vector <sf::RectangleShape> horizontalWalls;

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
	
	

	 void setup(sf::RenderWindow& window);
	 void set_map(Map map);
	 void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	 void update(sf::RenderWindow& window);

	 //SERVER
	 void sendMapAttributes(sf::UdpSocket& client);
	 void sendCases(sf::UdpSocket& client);
	void serverReceive(sf::UdpSocket& client);
	 void serverMovement(sf::UdpSocket& client);
	void  ServerSendBulletLoc(sf::UdpSocket& client);
	


	

	 void ServerThreadReceive();
	 void ClientThreadSend();
	 void ClientThreadReceive();
	 void ServerThreadSend();


	 //CLIENT
	  
	 void clientSend(sf::UdpSocket& socket);
	 void clientReceive(sf::UdpSocket& socket);
	 void clientMovement(sf::UdpSocket& socket);
	 void ClientSendBulletLoc(sf::UdpSocket& socket);
	 void clientSendCanReset(sf::UdpSocket& socket);
	 
	
	
	






	 void server();
	 void client();



	 bool getActive()
	 {
		 return isActive;
	 }
	 void setActive()
	 {
		 isActive = true;
	 }
	 void setInactive()
	 {
		 isActive = false;
	 }
	 bool getServerActive()
	 {
		 return isServer;
	 }
	 bool getClientActive()
	 {
		 return isClient;
	 }
	 void setServerActive(bool active_)
	 {
		 isServer = active_;
	 }
	 void setClientActive(bool active_)
	 {
		 isClient = active_;
	 }
	
	 void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};