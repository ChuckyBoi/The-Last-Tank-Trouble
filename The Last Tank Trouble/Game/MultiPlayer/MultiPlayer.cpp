#include "MultiPlayer.h"



//const std::string IPADDRESS("192.168.0.5");//change to suit your needs



struct attributes {

	sf::Uint16 x;
	sf::Uint16 y;
	sf::Vector2f size;
};
struct shape
{
	attributes wall;

};

sf::Packet& operator<<(sf::Packet& packet, attributes& test) {
	return packet << test.x << test.y << test.size.x << test.size.y;
}
sf::Packet& operator<<(sf::Packet& packet, shape& test) {
	
	packet << test.wall;
	return packet;
}
sf::Packet& operator>>(sf::Packet& packet, attributes& test) {
	return packet >> test.x >> test.y >> test.size.x >> test.size.y;
}
sf::Packet& operator>>(sf::Packet& packet, shape& test) {
	packet >> test.wall;
	return packet;
}







void MultiPlayer::setup(sf::RenderWindow& window)
{
	
	map.setup(window);
	set_map(map);



	player1.set_map(map);
	player1.setup(window,clients); 

	
	

	horizontalWall = map.getHorizontalWall();
	verticalWall = map.getVerticalWall();

	verticalWalls = map.getVerticalWalls();
	horizontalWalls = map.getHorizontalWalls();

	box = map.getBox();

	left = map.getLeft();
	right = map.getRight();
	down = map.getDown();
	top = map.getTop();

	hLefts = map.gethLefts();
	hRights = map.gethRights();
	hDowns = map.gethDowns();
	hTops = map.gethTops();

	vLefts = map.getvLefts();
	vRights = map.getvRights();
	vDowns = map.getvDowns();
	vTops = map.getvTops();

	

	
}


void MultiPlayer::make_foo_func_thread()
{

	t = std::thread(&MultiPlayer::listen,this);
	t.detach();
}

void MultiPlayer::make_c_func_thread()
{
	c = std::thread(&MultiPlayer::client, this);
	c.detach();
}

/*
void MultiPlayer::make_sending(sf::UdpSocket& client)
{
	Ssend = std::thread (&MultiPlayer::sendCases,this,std::ref(client));
	std::cout << "make_SENDING" << std::endl;
	Ssend.detach();
}
void MultiPlayer::make_receiving(sf::UdpSocket& client)
{
	Sreceive = std::thread(&MultiPlayer::serverReceive,this,std::ref(client));
	std::cout << "make_receiving" << std::endl;
	Sreceive.detach();
}


void MultiPlayer::Make_clientSend(sf::UdpSocket& socket)
{
	Csend = std::thread(&MultiPlayer::clientSend, this, std::ref(socket));
	std::cout << "make_sending" << std::endl;
	Csend.detach();
}

void MultiPlayer::Make_clientReceive(sf::UdpSocket& socket)
{
	Creceive = std::thread(&MultiPlayer::clientReceive, this, std::ref(socket));
	std::cout << "make_receiving" << std::endl;
	Creceive.detach();
}
*/



void MultiPlayer::listen()
{


	int casesS;
	//client_.bind(55002);
	if(client_.bind(55002) == sf::Socket::Done)
	{
		//std::cout << "Server IS BIND  " << port << ", waiting for a connection... " << std::endl;
	}

	selector.add(client_);
	
	while (true)
	{
		Packet_Clock.getElapsedTime().asSeconds();
		
		if (selector.wait(sf::microseconds(100.f)))
		{
			if (selector.isReady(client_))
			{
				if (client_.receive(buffer, sizeof(buffer), received, sender, port) == sf::Socket::Done) {

					std::cout << "Message received from client " << sender << ": \"" << buffer << "\"" << std::endl;
				}

				if (client_.send("9", sizeof(buffer), sender, port) != sf::Socket::Done)
				{
					std::cout << "clinet cant send";
				}

				sf::UdpSocket* client = new sf::UdpSocket;

				if (client_.bind(55002) == sf::Socket::Done)
				{


				//make_sending(*client);
				//make_receiving(*client);

					sentMapsToAll = false;
					sentNrOfPlayers = false;
					sentClientID = false;

				casesS = 1;
				sendCases(*client, casesS); //send map attributes
			//	serverReceive(*client,casesS);

					
				casesS = 4;
				sendCases(*client, casesS);
				//serverReceive(*client,casesS);
				clientID++;
				//casesS = 1;
						
					
						clients.push_back(client);
					std::cout << "clients size :" << clients.size() << std::endl;

				
					currentNrPlayers = clients.size();
					selector.add(*client);
				}
				else
				{
					std::cout << "delete client" << std::endl;
					// Error, we won't get a new connection, delete the socket
					delete client;
				}
			}

			else
			{
				if (Packet_Clock.getElapsedTime().asSeconds() >= 1)
				{
					//std::cout << "packets sent " << packetsSent << std::endl;
					packet_counter = 0;
					packet_storage = 0;
					packetsSent = 0;
					Packet_Clock.restart();
				}
		
				packet_counter = (Packet_Clock.getElapsedTime().asMilliseconds() / 15);

				if (packet_counter > packet_storage)
				{
					packetsSent++;
					packet_storage = packet_counter;

						for (std::list<sf::UdpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
						{
							sf::UdpSocket& client = **it;

							if (selector.isReady(client))
							{
								if (!sentMapsToAll)
								{
									casesS = 1;
								}
								if (!sentNrOfPlayers && sentMapsToAll)
								{
									casesS = 5;
								}
								if (sentMapsToAll && sentNrOfPlayers)
								{
									casesS = 2;
								}
								if (bulletShot) 
								{
									casesS = 3;
									//bulletShot = false;
								
								}
							
								if(bulletShot)
									std::cout << "sent to client" << std::endl;

								sendCases(client, casesS);
								serverReceive(client,casesS);
							}
						}
						if (!sentNrOfPlayers && sentMapsToAll)
						{
							sentNrOfPlayers = true;
						}
						if (!sentMapsToAll)
						{
							sentMapsToAll = true;
						}
						if (bulletShot)
						{
							bulletShot = false;
						}
						
					
					
				}
			}
		}
	}
}

void MultiPlayer::client()
{
	int casesC;

	if (!isConnectedToServer)
	{
	    std::cout << "Your port:?" << std::endl;
		std::cin >> ClientsPort;

		// Send a message to 192.168.1.50 on port 55002
		//socket_.bind(55001);
		socket_.send("9", sizeof(buffer), "192.168.0.120", 55002);

		// Receive an answer (most likely from 192.168.1.50, but could be anyone else)

		socket_.receive(buffer, sizeof(buffer), received, sender, port);
		std::cout << "server " << " said: " << buffer << std::endl;




		isConnectedToServer = true;

		//clientReceive(socket_, casesC);
		//clientSend(socket_, casesC);


	}
	if (isConnectedToServer == true)
	{
	

		while (true)
		{

			Packet_Clock.getElapsedTime().asSeconds();
		

					if (Packet_Clock.getElapsedTime().asSeconds() >= 1)
					{
						//std::cout << "packets sent " << packetsSent << std::endl;
						packet_counter = 0;
						packet_storage = 0;
						packetsSent = 0;

						Packet_Clock.restart();
					}
					packet_counter = (Packet_Clock.getElapsedTime().asMilliseconds() / 15);

					if (packet_counter > packet_storage)
					{
						packetsSent++;

						packet_storage = packet_counter;

						clientReceive(socket_, casesC);
						clientSend(socket_, casesC);
					}
				}

	}
}

void MultiPlayer::set_map(Map map)
{
	this->map = map;
}
void MultiPlayer::handleEvents(const sf::Event& event, sf::RenderWindow& window)
{

	if (isServer)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (!keyIsPressed)
			{
				setup(window);
				BetaClock.restart();

				sentMapsToAll = false;
				sentNrOfPlayers = false;

				keyIsPressed = true;
			}
		}
		else
		{
			keyIsPressed = false;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
				if (player1.getPlayersBulletSize(clientID) < 5 && player1.getShootingTimer(clientID) > 500)
				{
					// caseS = 3;
					
			    }
		}
	}
	
	if (isClient)
	{
		//int  casesC;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			if (player1.getPlayersBulletSize(clientID) < 5 && player1.getShootingTimer(clientID) > 500)
			{


				bulletShot = true;

			}
		}
		
	}
	

}
void MultiPlayer::server()
{

}
void MultiPlayer::update(sf::RenderWindow& window)
{
	
		if (isServer == true)
		{
			for (int i = 1; i <= clients.size(); i++) {

					player1.moveBullet(i, box, horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);

			}
			//player1.setCantRestart();

			//player1.movePlayer(0);
			//player1.collideWithWalls(0, verticalWalls, horizontalWalls);
			//player1.collideWithBox(0, box);
			//player1.createBullets(0,box ,horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);
		

		//	player1.moveBullet(1, box, horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);


		//	player1.collideWithBullets(0);
			//player1.collisionWithBulletsForOtherPlayer(1);
		//	player1.explosion(0);
		//	player1.restartFromPlayers(0);

			//if (player1.getCanRestart())
			//{
			//	setup(window);
			//	cases = 1;
			//}
		
			server();
		}


		if (isClient == true)
		{
	
			
			player1.setCantRestart();
			player1.movePlayer(clientID);
			
			player1.collideWithWalls(clientID, verticalWalls, horizontalWalls);
			 player1.collideWithBox(clientID, box);
			player1.createBullets(clientID,box,horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);
			player1.moveBullet(clientID, box, horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);

			// player1.createBulletsFor(clientID)
		

		//	player1.moveBullet(0, box, horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);
			



		
			///player1.collideWithBullets(1);
			//player1.collisionWithBulletsForOtherPlayer(0);
			//player1.explosion(1);
			//player1.restartFromPlayers(1);


		//	std::cout << "current pos of second player" << player1.playerGetPositionX(currentNrPlayers) << std::endl;

			player1.CalculateDeltaTime();

			//client();
			
			
		
		}
	
}



void MultiPlayer::sendCases(sf::UdpSocket& client,int &casesS)
{
	ServerMutexSend.lock();
	//std::cout <<"cases send " << casesS << std::endl;

	switch (casesS) 
	{
	case 0:
		ServerSendStandBy(client, casesS);
		break;
	case 1:
		sendMapAttributes(client, casesS);
		break;
	case 2:
		serverMovement(client, casesS);
		break;
	case 3:
		ServerSendBulletLoc(client, casesS);
		break;
	case 4:
		ServerSendClientID(client, casesS);
		break;
	case 5:
		serverSendNrOfClients(client, casesS);
	

		std::cout << "hey this is 5 and I sent you " << clients.size() << std::endl;
		break;
	}

	ServerMutexSend.unlock();
}
void MultiPlayer::serverReceive(sf::UdpSocket& client, int &casesS)
{
	ServerMutexReceive.lock();

	
	sf::Packet packetReceived;
	int clientID_;
	int casesC;
	sf::Uint16 posx=0, posy=0, rotation=0;
	float dirx=0, diry=0;

	client.receive(packetReceived, sender, port);

	
	packetReceived >> casesC >> clientID_;
	
//	std::cout << "cases receive "<< casesC << std::endl;


	switch (casesC) {
	case 0:
		
		break;
	case 1:
		//casesS = 1;
		break;
	case 2:
		packetReceived >> posx >> posy >> rotation;
		if ((posx > 10 || posy > 10) && (posx < 2000 || posy < 2000))
		{
			player1.playerSetPosition(clientID_, sf::Vector2f(posx, posy));
			player1.setRotation(clientID_, rotation);
		}
		break;
	case 3:
	
		packetReceived >> posx >> posy >> dirx >> diry;

		bulletPos.x = posx;
		bulletPos.y = posy;
		bulletDir.x = dirx;
		bulletDir.y = diry;

		std::cout << "Bullet position received from client number" << clientID_ << " " << posx << " " << posy << " " << dirx << " " << diry << " " << std::endl;

		player1.createBulletsFor(clientID_, bulletPos, bulletDir);



		clientWhoShotTheBullet = clientID_;
		bulletShot = true;

		break;
	case 4:
		
		break;
	case 5:
		
	default:
		break;
	
	}

	packetReceived.clear();
	ServerMutexReceive.unlock();

}

void MultiPlayer::serverSendNrOfClients(sf::UdpSocket& client, int &casesS)
{
	sf::Packet PNrOfClients;
	PNrOfClients << casesS << clients.size();
	client.send(PNrOfClients, sender, port);
}
void MultiPlayer::sendMapAttributes(sf::UdpSocket& client, int &casesS)
{
	sf::Packet PacketboxInfos;
	PacketboxInfos << casesS;

	attributes atrb;
	shape wholeThing;

	atrb.x = box.getPosition().x;
	atrb.y = box.getPosition().y;
	atrb.size.x = box.getSize().x;
	atrb.size.y = box.getSize().y;

	wholeThing.wall = atrb;

	PacketboxInfos << wholeThing.wall;

	PacketboxInfos << static_cast<sf::Uint32>(horizontalWalls.size());

	for (size_t i = 0; i < horizontalWalls.size(); i++)
	{
		atrb.x = horizontalWalls[i].getPosition().x;
		atrb.y = horizontalWalls[i].getPosition().y;
		atrb.size.x = horizontalWalls[i].getSize().x;
		atrb.size.y = horizontalWalls[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(verticalWalls.size());
	for (size_t i = 0; i < verticalWalls.size(); i++)
	{
		atrb.x = verticalWalls[i].getPosition().x;
		atrb.y = verticalWalls[i].getPosition().y;
		atrb.size.x = verticalWalls[i].getSize().x;
		atrb.size.y = verticalWalls[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(hLefts.size());
	for (size_t i = 0; i < hLefts.size(); i++)
	{
		atrb.x = hLefts[i].getPosition().x;
		atrb.y = hLefts[i].getPosition().y;
		atrb.size.x = hLefts[i].getSize().x;
		atrb.size.y = hLefts[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(hRights.size());
	for (size_t i = 0; i < hRights.size(); i++)
	{
		atrb.x = hRights[i].getPosition().x;
		atrb.y = hRights[i].getPosition().y;
		atrb.size.x = hRights[i].getSize().x;
		atrb.size.y = hRights[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(hTops.size());
	for (size_t i = 0; i < hTops.size(); i++)
	{
		atrb.x = hTops[i].getPosition().x;
		atrb.y = hTops[i].getPosition().y;
		atrb.size.x = hTops[i].getSize().x;
		atrb.size.y = hTops[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(hDowns.size());
	for (size_t i = 0; i < hDowns.size(); i++)
	{
		atrb.x = hDowns[i].getPosition().x;
		atrb.y = hDowns[i].getPosition().y;
		atrb.size.x = hDowns[i].getSize().x;
		atrb.size.y = hDowns[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(vLefts.size());
	for (size_t i = 0; i < vLefts.size(); i++)
	{
		atrb.x = vLefts[i].getPosition().x;
		atrb.y = vLefts[i].getPosition().y;
		atrb.size.x = vLefts[i].getSize().x;
		atrb.size.y = vLefts[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(vRights.size());
	for (size_t i = 0; i < vRights.size(); i++)
	{
		atrb.x = vRights[i].getPosition().x;
		atrb.y = vRights[i].getPosition().y;
		atrb.size.x = vRights[i].getSize().x;
		atrb.size.y = vRights[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(vTops.size());
	for (size_t i = 0; i < vTops.size(); i++)
	{
		atrb.x = vTops[i].getPosition().x;
		atrb.y = vTops[i].getPosition().y;
		atrb.size.x = vTops[i].getSize().x;
		atrb.size.y = vTops[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}
	PacketboxInfos << static_cast<sf::Uint32>(vDowns.size());
	for (size_t i = 0; i < vDowns.size(); i++)
	{
		atrb.x = vDowns[i].getPosition().x;
		atrb.y = vDowns[i].getPosition().y;
		atrb.size.x = vDowns[i].getSize().x;
		atrb.size.y = vDowns[i].getSize().y;

		wholeThing.wall = atrb;
		PacketboxInfos << wholeThing.wall;
	}

	//WHAT
	if (client.send(PacketboxInfos, sender, port) != sf::Socket::Done)
	{
		std::cout << " Didnt Sent map attributes .\n";
	}
	else
	{
		std::cout << "sent map attributes \n  ";
	}
	
}
void MultiPlayer::serverMovement(sf::UdpSocket& client, int &casesS)
{

   // sf::Uint16 posx, posy, rotation;
	//sf::Uint16 position;

	sf::Packet Plocation;

	for (int i = 1; i <= clients.size(); i++)
	{
		posx[i] = player1.playerGetPositionX(i);
		posy[i] = player1.playerGetPositionY(i);
		rotation[i] = player1.getRotation(i);
	}


	//std::cout << "Putting in packet to send to client "<< std::endl;

	for (int i = 1; i <= clients.size(); i++)
	{
		if (SavedPositionSX[i] == posx[i] &&
			SavedPositionSY[i] == posy[i] &&
			SavedRotationS[i] == rotation[i]) 
		{
			
			
			casesS = 2;
			Plocation << casesS << i << posx[i] << posy[i] << rotation[i];

		//	std::cout << casesS << " " << i << " " << posx[i] << " " << posy[i] << std::endl;

		
		}
		else 
		{
			casesS = 2;

			SavedPositionSX[i] = posx[i];
			SavedPositionSY[i] = posy[i];
			SavedRotationS[i] = rotation[i];

		//	std::cout << "Players " << i << "pos is " << posx[i] << " " << posy[i] << std::endl;
		
			Plocation << casesS << i << posx[i] << posy[i] << rotation[i];


			//std::cout << casesS << " " << i << " " << posx[i] << " " << posy[i] << std::endl;
	
		}
		
	}

		client.send(Plocation, sender, port);
}
void MultiPlayer::ServerSendBulletLoc(sf::UdpSocket& client, int &casesS)
{
	sf::Packet Plocation;

	sf::Vector2f position;
	sf::Vector2f Dir;
	sf::Uint16 posx=0, posy=0;
	float Dirx=0, Diry=0;


	for (int i = 1; i <= clients.size(); i++) 
	{
		
		position = player1.playerGetBulletPos(clientWhoShotTheBullet);
		Dir = player1.playerGetDir(clientWhoShotTheBullet);

		posx = position.x;
		posy = position.y;
		Dirx = Dir.x;
		Diry = Dir.y;


		Plocation << casesS << i << posx << posy << Dirx << Diry;
		std::cout << "Server is sending for client " << i <<" " << posx << " " << posy <<" " << Dirx << " " << Diry << std::endl;


		
	}

	client.send(Plocation, sender, port);

}
void MultiPlayer::ServerSendClientID(sf::UdpSocket& client, int &casesS)
{
	sf::Packet PclientID;
	PclientID << casesS << clientID;
	client.send(PclientID, sender, port);

}
void MultiPlayer::ServerSendStandBy(sf::UdpSocket& client, int& casesS)
{
	sf::Packet Pcase0;
	Pcase0 << casesS << clientID;
	client.send(Pcase0, sender, port);
}


void MultiPlayer::clientReceive(sf::UdpSocket& socket,int &casesC)
{
	float dirx, diry;
	sf::Uint16 posx=0, posy=0, rotation=0;
	int clientID_= 0;
	
	ClienterverMutexReceive.lock();


	sf::Packet packetReceived;
	if (socket.receive(packetReceived, sender, port) != sf::Socket::Done)
	{
		std::cout << "CLIENT RECEIVE: Couldn't receive data from server.\n";
	}

	for (int i = 1; i <= currentNrPlayers; i++) 
	{
		
		packetReceived >> casesC;
		//std::cout << "cases received for client is " << casesC << std::endl;
		//std::cout << "cases C is" << casesC << std::endl;

		switch (casesC)
		{
		case 0:
		
			packetReceived >> clientID_>> posx>>posy;
			//std::cout << casesC << " player " << clientID_ << "pos " << posx << " " << posy << std::endl;
			casesC = 2;
			break;
		case 1:
		{


			attributes atrb;
			shape wholeThing;

			packetReceived >> wholeThing.wall;

			box.setSize(sf::Vector2f(wholeThing.wall.size));
			box.setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));

			horizontalWalls.clear();
			verticalWalls.clear();

			hLefts.clear();
			hRights.clear();
			hTops.clear();
			hDowns.clear();

			vLefts.clear();
			vRights.clear();
			vTops.clear();
			vDowns.clear();



			int size = 0;
			packetReceived >> size;

			for (sf::Uint32 i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				horizontalWalls.push_back(sf::RectangleShape(horizontalWall));

				horizontalWalls[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				horizontalWalls[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
				//std::cout << "horizontal walls " << horizontalWalls[i].getPosition().x << "\n";
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				verticalWalls.push_back(sf::RectangleShape(horizontalWall));

				verticalWalls[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				verticalWalls[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}

			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				hLefts.push_back(sf::RectangleShape(left));

				hLefts[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				hLefts[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				hRights.push_back(sf::RectangleShape(right));

				hRights[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				hRights[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				hTops.push_back(sf::RectangleShape(top));

				hTops[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				hTops[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				hDowns.push_back(sf::RectangleShape(down));

				hDowns[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				hDowns[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				vLefts.push_back(sf::RectangleShape(left));

				vLefts[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				vLefts[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				vRights.push_back(sf::RectangleShape(right));

				vRights[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				vRights[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				vTops.push_back(sf::RectangleShape(top));

				vTops[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				vTops[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}
			size = 0;
			packetReceived >> size;

			for (size_t i = 0; i < size; i++)
			{
				packetReceived >> wholeThing.wall;

				vDowns.push_back(sf::RectangleShape(down));

				vDowns[i].setSize(sf::Vector2f(wholeThing.wall.size.x, wholeThing.wall.size.y));
				vDowns[i].setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));
			}


			///casesForThem = 2;

			setupOnce = false;
			if (!setupOnce) {

				//player1.setupForClient(clientID);
				player1.setClientFirstPosition(box, clientID);
				setupOnce = true;
			}
			i = currentNrPlayers + 1;
		}
		break;
		case 2:
			packetReceived >> clientID_ >> posx >> posy >> rotation;

			if (clientID_ != clientID)
			{
				player1.playerSetPosition(clientID_, sf::Vector2f(posx, posy));
				player1.setRotation(clientID_, rotation);
			}
			break;
		case 3:
			
			packetReceived >> clientID_ >> posx >> posy >> dirx >> diry;
			std::cout << "client received from server from client number "  << clientID_ << " " << posx << " " << posy << " " << dirx << " " << diry << std::endl;

			if (clientID_ != clientID)
			{

				bulletPos.x = posx;
				bulletPos.y = posy;
				bulletDir.x = dirx;
				bulletDir.y = diry;

				player1.createBulletsFor(clientID_, bulletPos, bulletDir);
				std::cout << "should create " << std::endl;
			}

			break;
		case 4:
			packetReceived >> clientID;
			break;
		case 5:
			packetReceived >> currentNrPlayers;
			std::cout << "cases = 5 and I received " << currentNrPlayers << std::endl;
			break;
		default:
			break;
		}
	}
		
	ClienterverMutexReceive.unlock();

}
void MultiPlayer::clientSend(sf::UdpSocket& socket, int& casesC)
{
	//std::cout <<"client Send"<< casesC << std::endl;
	ClienterverMutexSend.lock();
	if (bulletShot) {

		bulletShot = false;
		casesC = 3;

	}

	switch (casesC)
	{
	case 0:
		clientSendStandBy(socket, casesC);
		break;
	case 1:
		clientSendCanReset(socket, casesC);
		break;
	case 2:
		clientMovement(socket, casesC);
		break;
	case 3:
		ClientSendBulletLoc(socket, casesC);	
		break;
	case 4:
		clientSendReceivedClientID(socket, casesC);
		break;
	case 5:
		clientSendReceivedNrOfPlayers(socket, casesC);
		break;
	default:
		break;
	}

	ClienterverMutexSend.unlock();
}
void MultiPlayer::clientMovement(sf::UdpSocket& socket,int casesC)
{
	sf::Uint16 posx=0, posy=0, rotation=0;
	sf::Packet Plocation;

	posx = player1.playerGetPositionX(clientID);
	posy = player1.playerGetPositionY(clientID);
	rotation = player1.getRotation(clientID);

	
	if (SavedPositionXC == posx &&
		SavedPositionYC == posy &&
		rotationCC == rotation) {

		casesC = 0;
		Plocation << casesC << clientID;
		//socket.send(Plocation, sender, port);
	}
	
	else {
		casesC = 2;
		SavedPositionXC = posx;
		SavedPositionYC = posy;
		rotationCC = rotation;

	
		Plocation << casesC << clientID << posx << posy << rotation;

	//	socket.send(Plocation, sender, port);

	}

	//std::cout << "sent " << casesC << std::endl;
	socket.send(Plocation, sender, port);
}
void MultiPlayer::ClientSendBulletLoc(sf::UdpSocket& socket, int casesC)
{
	
	sf::Uint16 posx, posy;
	float Dirx=0, Diry=0;
	sf::Vector2f position;
	sf::Vector2f Dir;


	position = player1.playerGetBulletPos(clientID);
	Dir = player1.playerGetDir(clientID);

	posx = position.x;
	posy = position.y;
	Dirx = Dir.x;
	Diry = Dir.y;


	std::cout << "Client number " <<clientID << " is sending" << " " << posx << " " << posy << " " << Dirx << " " << Diry << std::endl;

	sf::Packet Plocation;
	Plocation << casesC << clientID << posx << posy << Dirx << Diry;
	
	socket.send(Plocation, sender, port);

}
void MultiPlayer::clientSendCanReset(sf::UdpSocket& socket, int casesC)
{
	sf::Packet Plocation;
	Plocation << casesC << clientID;

	socket.send(Plocation, sender, port);

}
void MultiPlayer::clientSendReceivedClientID(sf::UdpSocket& socket, int casesC)
{
	sf::Packet PreceivedID;
	PreceivedID << casesC << clientID;
	socket.send(PreceivedID, sender, port);
}
void MultiPlayer::clientSendReceivedNrOfPlayers(sf::UdpSocket& socket, int casesC)
{
	sf::Packet PnrOfPlayers;
	PnrOfPlayers << casesC << clientID << currentNrPlayers;
		socket.send(PnrOfPlayers, sender, port);

}


void MultiPlayer::clientSendStandBy(sf::UdpSocket& socket, int casesC)
{
	sf::Packet Pcase0;
	//sf::Uint16 posx, posy, rotation;
	/*
	posx = player1.playerGetPositionX(clientID);
	posy = player1.playerGetPositionY(clientID);
	rotation = player1.getRotation(clientID);


	if (SavedPositionXC == posx &&
		SavedPositionYC == posy &&
		rotationCC == rotation) {

		casesC = 0;
		Pcase0 << casesC << clientID;
		//socket.send(Plocation, sender, port);
	}
	else {
		casesC = 2;
		Pcase0 << casesC << clientID;
	}
	*/
	Pcase0 << casesC << clientID;
	socket.send(Pcase0, sender, port);

}

void MultiPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(box, states);
	for(auto &i :verticalWalls)
	{
		target.draw(i);
	}
	for (auto& i : horizontalWalls)
	{
		target.draw(i);
	}



	if (isServer) {
		player1.drawEverything(target, states, clients.size());
	}
		//player1.drawAll(target, states, clients.size());

	if (isClient) {
		//player1.drawEverything(target, states, currentNrPlayers);
		player1.drawEverything(target, states, currentNrPlayers);
		//std::cout << "current nr of players "<<currentNrPlayers << std::endl;
	}
	target.draw(player1);
	//target.draw(player1.Players[clientID].Tank);

	/*
	if (isClient) {
	
		target.draw(player1);
	}
	if (isServer)
	{
		target.draw(player1);
	}
	*/
	
	
}
