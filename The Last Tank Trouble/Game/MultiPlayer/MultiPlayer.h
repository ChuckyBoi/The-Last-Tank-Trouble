#pragma once
#include "MultiPlayerGame.h"
#include <thread>
#include <mutex>


class MultiPlayer :public sf::Drawable
{

	
private:
	

	int nrMaxPlayers = 4;
	int currentNrPlayers = 1;
	int clientID=1;

	int clientWhoShotTheBullet=0;


	sf::Uint16 SavedPositionSX[5];
	sf::Uint16 SavedPositionSY[5];
	sf::Uint16 SavedRotationS[5];

	sf::Uint16 SavedPositionXC, SavedPositionYC, rotationCC;
	//sf::Uint16 SavedPositionSX, SavedPositionSY, rotationSS;


	//sf::Uint16 SavedPositionX[5], SavedPositionY[5], rotationC[5];
	sf::Uint16 posx[5], posy[5], rotation[5];
	


	

	sf::UdpSocket client_;
	sf::SocketSelector selector;
	std::list<sf::UdpSocket*> clients; // notice: no pointers...


	sf::UdpSocket socket_;
	

	sf::Clock BetaClock;


	
	
	
	sf::Vector2f bulletPos, bulletDir;



	char buffer[1024];
	std::size_t received = 0;
	sf::IpAddress sender;

	unsigned short port;
	unsigned short ClientsPort;

	int packetsSent = 0;


	int packet_counter = 0;
	int packet_storage = 0;
	sf::Clock Clock;
	sf::Clock Packet_Clock;
	sf::Time time;


	bool setupOnce = false;


	bool isActive = false;
	bool isServer = false;
	bool isClient = false;

	bool isConnectedToServer = false;


	bool sentMapsToAll =false ;
	bool sentClientID = false;
	bool sentNrOfPlayers =  false ;
	bool bulletShot = false;

	

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


	std::mutex ServerMutexSend;
	std::mutex ServerMutexReceive;
	std::mutex ClienterverMutexSend;
	std::mutex ClienterverMutexReceive;


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
	 void sendMapAttributes(sf::UdpSocket& client, int &x);

	 void sendCases(sf::UdpSocket& client,int &x);

	void serverReceive(sf::UdpSocket& client,int &x);

	 void serverMovement(sf::UdpSocket& client, int &x);
	void  ServerSendBulletLoc(sf::UdpSocket& client, int& x);
	void serverSendNrOfClients(sf::UdpSocket& client, int &x);
	void ServerSendClientID(sf::UdpSocket& client, int &x);

	void ServerSendStandBy(sf::UdpSocket& client, int& x);

	int getClientsSize();
	




	 //CLIENT
	void clientReceiveClientID(sf::UdpSocket& client,int &x);

	 void clientSend(sf::UdpSocket& socket, int &x);
	 void clientReceive(sf::UdpSocket& socket,int &x);

	 void clientMovement(sf::UdpSocket& socket, int x);
	 void ClientSendBulletLoc(sf::UdpSocket& socket, int x);
	 void clientSendCanReset(sf::UdpSocket& socket, int x);
	 void clientSendReceivedClientID(sf::UdpSocket& socket, int x);
	 void clientSendReceivedNrOfPlayers(sf::UdpSocket& socket, int x);

	 void clientSendStandBy(sf::UdpSocket& socket, int x);

	 
	
	






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