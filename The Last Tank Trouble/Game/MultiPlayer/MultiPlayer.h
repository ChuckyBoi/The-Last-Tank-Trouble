#pragma once
#include "MultiPlayerGame.h"
#include <thread>


class MultiPlayer :public sf::Drawable
{

	
private:
	int cases = 1;
	int casesForThem = 1;
	int nrMaxPlayers = 4;
	int currentNrPlayers = 1;
	int clientID=1;


	bool sentClientID = false;
	bool sentNrOfPlayers = false;
	

	sf::UdpSocket client_;
	sf::SocketSelector selector;
	std::list<sf::UdpSocket*> clients; // notice: no pointers...


	sf::UdpSocket socket_;
	

	sf::Clock BetaClock;


	
	
	
	sf::Vector2f bulletPos, bulletDir;
	sf::Vector2f previousPos;
	float previousRotation;



	char buffer[1024];

	std::size_t received = 0;
	sf::IpAddress sender;

	unsigned short port;
	unsigned short ClientsPort;






	
	bool setupOnce = false;

	bool isActive = false;

	bool isServer = false;
	bool isClient = false;

	bool isConnectedToServer = false;

	bool sentMapsToAll = false;
	






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


	std::thread t;
	std::thread c;

	std::thread Ssend;
	std::thread Sreceive;

	std::thread Csend;
	std::thread Creceive;
	


public:
	void listen();
	
	
	void make_foo_func_thread();
	void make_c_func_thread();


	void make_sending(sf::UdpSocket& client);
	void make_receiving(sf::UdpSocket& client);


	void Make_clientSend(sf::UdpSocket& socket);
	void Make_clientReceive(sf::UdpSocket& socket);

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
	void serverSendNrOfClients(sf::UdpSocket& client);
	void ServerSendClientID(sf::UdpSocket& client);

	int getClientsSize();
	




	 //CLIENT
	void clientReceiveClientID(sf::UdpSocket& client);

	 void clientSend(sf::UdpSocket& socket);
	 void clientReceive(sf::UdpSocket& socket);

	 void clientMovement(sf::UdpSocket& socket);
	 void ClientSendBulletLoc(sf::UdpSocket& socket);
	 void clientSendCanReset(sf::UdpSocket& socket);
	 void clientSendReceivedClientID(sf::UdpSocket& socket);
	 void clientSendReceivedNrOfPlayers(sf::UdpSocket& socket);
	 
	
	
	






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