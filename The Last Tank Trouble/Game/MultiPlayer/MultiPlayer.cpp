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
	player1.setup(window); 
	
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
				cases = 1;
				keyIsPressed = true;
			}
		}
		else
		{
			keyIsPressed = false;

		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
				if (player1.getPlayersBulletSize(0) < 5 && player1.getShootingTimer(0) > 500)
				{

					cases = 3;
			    }
		}
	}
	
	if (isClient)
	{
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			if (player1.getPlayersBulletSize(1) < 5 && player1.getShootingTimer(1) > 500)
			{

				casesForThem = 3;
				//std::cout << casesForThem;
			}
		}
		
	}
	

}
void MultiPlayer::server()
{

	if (!isConnectedToClient)
	{
		client_.bind(55001);

		// Send a message to 192.168.1.50 on port 55002
		std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
		client_.send(message.c_str(), message.size() + 1, "192.168.1.6", 55002);

		// Receive an answer (most likely from 192.168.1.50, but could be anyone else)
	

		client_.receive(buffer, sizeof(buffer), received, sender, port);
		std::cout << sender.toString() << " said: " << buffer << std::endl;


		isConnectedToClient = true;
	
	}
	if(isConnectedToClient == true)
	{

	    sendCases(client_);
		serverReceive(client_);

	}
} 
void MultiPlayer::client()
{
	std::cout << sf::IpAddress::getLocalAddress().toString();

		if (!isConnectedToServer)
		{
			socket_.bind(55002);
			
			socket_.receive(buffer, sizeof(buffer), received, sender, port);
			std::cout << sender.toString() << " said: " << buffer << std::endl;

			std::string message = "Welcome " + sender.toString();
			socket_.send(message.c_str(), message.size() + 1, sender, port);
			isConnectedToServer = true;
	
		}
		if (isConnectedToServer == true)
		{

			clientReceive(socket_);
			clientSend(socket_);

			//ClientThreadReceive();
		    //ClientThreadSend();
		}
}
void MultiPlayer::update(sf::RenderWindow& window)
{
	
		if (isServer == true)
		{
			
			player1.setCantRestart();

			player1.movePlayer(0);
			player1.collideWithWalls(0, verticalWalls, horizontalWalls);
			player1.collideWithBox(0, box);
			player1.createBullets(0,box ,horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);
		

			player1.moveBullet(1, box, horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);




			player1.collideWithBullets(0);
			player1.collisionWithBulletsForOtherPlayer(1);
			player1.explosion(0);
			player1.restartFromPlayers(0);

			if (player1.getCanRestart())
			{
				setup(window);
				cases = 1;
			}
			



			server();
		
		
			

		}


		if (isClient == true)
		{
		
			
			player1.setCantRestart();
			player1.movePlayer(1);
			player1.collideWithWalls(1, verticalWalls, horizontalWalls);
			player1.collideWithBox(1, box);
			player1.createBullets(1,box,horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);
		
		
			player1.moveBullet(0, box, horizontalWalls, verticalWalls, hLefts, hRights, hTops, hDowns, vLefts, vRights, vTops, vDowns);
			




			player1.collideWithBullets(1);
			player1.collisionWithBulletsForOtherPlayer(0);
			player1.explosion(1);
			player1.restartFromPlayers(1);
			
			if(player1.getCanRestart())
			{
				casesForThem = 1;
			}

			client();
			
			
		
		}
	
}
void MultiPlayer::sendCases(sf::UdpSocket& client)
{
	if (cases == 2)
	{
		serverMovement(client);
	}
	if (cases == 1)
	{
		sendMapAttributes(client);
		cases = 2;
	}
	if (cases == 3)
	{
		ServerSendBulletLoc(client);
		cases = 2;
	}
}
void MultiPlayer::serverReceive(sf::UdpSocket& client)
{

	sf::Vector2f position;
	sf::Packet packetReceived;

	 client.receive(packetReceived, sender, port);
		

		packetReceived >> casesForThem;
		if (casesForThem == 1)
		{
			cases = 1;
		}
		if (casesForThem == 2)
		{
			sf::Uint32 posx, posy, rotation;
			packetReceived >> posx >> posy >> rotation;
			if ((posx > 10 || posy > 10 ) && (posx < 2000 || posy < 2000))
			{
				player1.playerSetPosition(1, sf::Vector2f(posx, posy));
				player1.setRotation(1, rotation);


			}
		
		}
		if (casesForThem == 3)
		{

			//std::cout << "NEVER HERE";
			float posx, posy;
			float dirx, diry;

			packetReceived >> posx >> posy >> dirx >> diry;
			bulletPos.x = posx;
			bulletPos.y = posy;
			bulletDir.x = dirx;
			bulletDir.y = diry;


			player1.createBulletsFor(1, bulletPos, bulletDir);


			//std::cout << "pos is " << posx << " " << posy << std::endl;
			//std::cout << "dir is " << dirx << " " << diry << std::endl;

		
		}
		
	
}
void MultiPlayer::sendMapAttributes(sf::UdpSocket& client)
{
	sf::Packet PacketboxInfos;
	PacketboxInfos << cases;

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

	
	sf::Uint32 posx, posy, rotation;
	posx = player1.playerGetPosition(1).x;
	posy = player1.playerGetPosition(1).y;
	rotation = player1.getRotation(1);
	
	PacketboxInfos << posx << posy << rotation;


	if (client.send(PacketboxInfos, sender, port) != sf::Socket::Done)
	{
		std::cout << " Didnt Sent map attributes .\n";
	}
	else
	{
		std::cout << "sent map attributes \n  ";
	}
	
}
void MultiPlayer::serverMovement(sf::UdpSocket& client)
{

	sf::Uint32 posx, posy, rotation;
	sf::Vector2f position;
	position = player1.playerGetPosition(0);
	rotation = player1.getRotation(0);

	/*
	if ((position.x != previousPos.x ||
		position.y != previousPos.y) ||
		rotation != previousRotation)
	{

		previousPos.x = player1.playerGetPosition(0).x;
		previousPos.y = player1.playerGetPosition(0).y;
		previousRotation = player1.getRotation(0);
		posx = position.x;
		posy = position.y;
	
		sf::Packet Plocation;
	Plocation << cases << posx << posy << rotation;
	client_.send(Plocation, copyAddress, copyPort);

	
	}
	*/
	posx = position.x;
	posy = position.y;
	sf::Packet Plocation;
	Plocation << cases << posx << posy << rotation;
	client_.send(Plocation, sender, port);

}
void MultiPlayer::ServerSendBulletLoc(sf::UdpSocket& client)
{
	float posx, posy;
	float Dirx, Diry;
	sf::Vector2f position;
	sf::Vector2f Dir;
	

	
	position = player1.playerGetBulletPos(0);
	posx = position.x;
	posy = position.y;
	Dir = player1.getBulletStartingDir();
	Dirx = Dir.x;
	Diry = Dir.y;

	std::cout << "pos is " << posx << " "<< posy << std::endl;
	std::cout << "Dir is " << Dirx << " " << Diry << std::endl;



	sf::Packet Plocation;
	Plocation << cases << posx << posy << Dirx << Diry;
	client.send(Plocation, sender, port);

}

void MultiPlayer::clientSend(sf::UdpSocket& socket)
{
	if (casesForThem == 1)
	{
		clientSendCanReset(socket);
		casesForThem = 2;
	}
	if (casesForThem == 2)
	{
		clientMovement(socket);
	}
	if (casesForThem == 3)
	{
		//std::cout << "IT casesForThem WORK " << casesForThem << std::endl;
		ClientSendBulletLoc(socket);
		casesForThem = 2;
	}
	
}
void MultiPlayer::clientReceive(sf::UdpSocket& socket)
{

	sf::Packet packetReceived;
	if (socket.receive(packetReceived, sender, port) != sf::Socket::Done)
	{
		//std::cout << "Couldn't receive data from server.\n";
	}
	else
	{
		//std::cout << "received data from server.\n";
	}
	packetReceived >> cases;
	if (cases == 1) 
	{

		attributes atrb;
		shape wholeThing;

		packetReceived >> wholeThing.wall;

		box.setSize(sf::Vector2f(wholeThing.wall.size));
		box.setPosition(sf::Vector2f(wholeThing.wall.x, wholeThing.wall.y));

	//	std::cout << "client:" << wholeThing.wall.size.x << std::endl;

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

		sf::Uint32 posx, posy, rotation;
		sf::Vector2f position;
		float rotation_;
		packetReceived >> posx >> posy >> rotation;
		position.x = posx;
		position.y = posy;
		rotation_ = rotation;
		player1.playerSetPosition(1, position);
		player1.setRotation(1, rotation_);

		///casesForThem = 2;

	}
	if (cases == 2) {
		sf::Uint32 posx, posy, rotation;
		packetReceived >> posx >> posy >> rotation;

		//std::cout << "posx is " << posx << " posy is " << posy << std::endl;

	//	if (posx > 10 || posy < 10)
		//{
			player1.playerSetPosition(0, sf::Vector2f(posx, posy));
			player1.setRotation(0, rotation);
	//	}

	
		//casesForThem = 2;
	}
	if (cases == 3) 
	{
		float posx, posy;
		float dirx, diry;


		packetReceived >> posx >> posy >> dirx >> diry;
		bulletPos.x = posx;
		bulletPos.y = posy;
		bulletDir.x = dirx;
		bulletDir.y = diry;
		

	   player1.createBulletsFor(0, bulletPos, bulletDir);
		

		//std::cout << "pos is " << posx << " " << posy << std::endl;
		//std::cout << "dir is " << dirx << " " << diry << std::endl;

		  
	}
}
void MultiPlayer::clientMovement(sf::UdpSocket& socket)
{

	sf::Uint32 posx, posy, rotation;
	sf::Vector2f position;
	position = player1.playerGetPosition(1);
	rotation = player1.getRotation(1);
	
	posx = position.x;
	posy = position.y;
	sf::Packet Plocation;
	Plocation << casesForThem << posx << posy << rotation;

	socket.send(Plocation, sender, port);


}
void MultiPlayer::ClientSendBulletLoc(sf::UdpSocket& socket)
{
	float posx, posy;
	float Dirx, Diry;
	sf::Vector2f position;
	sf::Vector2f Dir;



	position = player1.playerGetBulletPos(1);
	posx = position.x;
	posy = position.y;
	Dir = player1.getBulletStartingDir();
	Dirx = Dir.x;
	Diry = Dir.y;

	std::cout << "pos is " << posx << " " << posy << std::endl;
	std::cout << "Dir is " << Dirx << " " << Diry << std::endl;


	sf::Packet Plocation;
	Plocation << casesForThem << posx << posy << Dirx << Diry;
	
	socket.send(Plocation, sender, port);

}

void MultiPlayer::clientSendCanReset(sf::UdpSocket& socket)
{
	sf::Packet Plocation;
	Plocation << casesForThem;

	socket.send(Plocation, sender, port);

}


void MultiPlayer::ServerThreadReceive()
{

	std::thread t(&MultiPlayer::serverReceive, &MultiPlayer(), std::ref(client_));
	t.join();
}
void MultiPlayer::ClientThreadSend()
{
	std::thread t1(&MultiPlayer::clientSend, &MultiPlayer(), std::ref(socket_));
	t1.join();
}
void MultiPlayer::ClientThreadReceive()
{
	std::thread t2(&MultiPlayer::clientReceive, &MultiPlayer(), std::ref(socket_));
	t2.join();
}
void MultiPlayer::ServerThreadSend()
{
	std::thread t3(&MultiPlayer::sendCases, &MultiPlayer(), std::ref(client_));
	t3.join();

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

	target.draw(player1);


	
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
