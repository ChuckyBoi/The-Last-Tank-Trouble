#include "States/StateManager.h"
#include <iostream>
#include <SFML/Network.hpp>



int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1366, 766) , "Last Man Standing");
	//sf::RenderWindow window(sf::VideoMode(1920, 1080), "Last Man Standing");
	//window.setFramerateLimit(10);
    window.setVerticalSyncEnabled(true);

	StateManager manager;
	manager.setup(window);

	std::cout << sf::IpAddress::getLocalAddress().toString();
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			manager.handleEvents(event, window);

			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
			{
				std::vector<sf::VideoMode> i = sf::VideoMode::getFullscreenModes();
				sf::RenderWindow window(i.front(), "SFML WORKS!", sf::Style::Fullscreen);
			}
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}
		window.clear(sf::Color(220,220,220));
		//window.clear(sf::Color::Black);
		//window.clear(sf::Color::White);


		manager.update(window);
		manager.Compose(window);

		window.display();
	}
	return 0;
}



/*


const unsigned short PORT = 5000;
const std::string IPADDRESS("192.168.0.5");//change to suit your needs

std::string msgSend;
sf::TcpSocket socket;
sf::Mutex globalMutex;
int xCord;
bool quit = false;

void DoStuff(void)
{
static std::string oldMsg;
	//static int old;

	while (!quit)
	{

		sf::Packet packetSend;
		globalMutex.lock();
		packetSend << msgSend;
		//packetSend << xCord;
		globalMutex.unlock();
		socket.send(packetSend);

		std::string msg;
		sf::Packet packetReceive;

		socket.receive(packetReceive);
		if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
		{
			std::cout << msg <<std::endl;
			//this prints to your own screen
			oldMsg = msg;
		}
	}
}
void Server(void)
{
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

bool Client(void)
{
	if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}

void GetInput(void)
{
	std::string s;
	std::cout << "\nEnter \"exit\" to quit or message to send: ";
	getline(std::cin, s);
	if (s == "exit")
		quit = true;
	globalMutex.lock();
	msgSend = s;

	globalMutex.unlock();
}

int main()
{
	sf::Thread* thread = 0;
	char who;
	std::cout << "Do you want to be a server (s) or a client (c) ? ";
	std::cin >> who;
	if (who == 's')
		Server();
	else
		Client();
	thread = new sf::Thread(&DoStuff);
	thread->launch();
	while (!quit)
	{
		GetInput();
	}
	if (thread)
	{
		thread->wait();
		delete thread;
	}

}
*/
//const unsigned short PORT = 5000;
/*
const std::string IPADDRESS("192.168.0.5");//change to suit your needs
sf::Vector2f cords;

int client()
{
	sf::RenderWindow window(sf::VideoMode(1366, 766), "Last Man Standing");
	window.setFramerateLimit(60);
	int cordx=0,cordy=0,Enemycordx=0,Enemycordy=0;
	bool mousePressed=false, mouseReceived=false;

	sf::TcpSocket socket;

	sf::Socket::Status status = socket.connect("localhost", 53000);

	if (status != sf::Socket::Done)
	{
		//	std::cout << "Failed to connect!\n";
		return 0;
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				cordx = sf::Mouse::getPosition(window).x;
				cordy = sf::Mouse::getPosition(window).y;
				mousePressed = true;
			}
			else 
			{
				mousePressed = false;
			}
		}
					
		sf::Packet packet2;

		if (socket.receive(packet2) != sf::Socket::Done)
		{
			//		std::cout << "Couldn't recieve data from server.\n";
		}
		else
		{
			//	std::cout << "Recieved data from server.\n";
		}


		packet2 >> Enemycordx;
		packet2 >> Enemycordy;
		packet2 >> mouseReceived;

		if (mouseReceived) {

			std::cout << "Servers cords are " << Enemycordx << " " << Enemycordy << " " << std::endl;
			std::cout << "clients cords are " << cordx << " " << cordy << std::endl;

		}
		window.clear(sf::Color::Black);
		window.display();


		//Send our clients position to the server

		sf::Packet packet1;

		packet1 << cordx;
		packet1 << cordy;
		packet1 << mousePressed;

		// TCP socket:
		if (socket.send(packet1) != sf::Socket::Done)
		{
			//std::cout << "Couldn't send data to server.\n";
		}
		else
		{
			//std::cout << "Sent data to server.\n";
		}
		window.clear();
		window.display();
	}
}
int server()
{
	sf::RenderWindow window(sf::VideoMode(1366, 766), "Last Man Standing");
	window.setFramerateLimit(60);

	sf::TcpListener listener;
	int cordx=0,cordy=0,Enemycordx=0,Enemycordy=0;
	bool mousePressed = false, mouseReceived = false;

	// bind the listener to a port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		//std::cout << "Error: No connections.\n";
		return -1;
	}
	//std::cout << "Server is listening to port 53000...\n";
	// accept a new connection
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done)
	{
		//std::cout << "error client\n";
		return -1;
	}
	//std::cout << "Client connected: " << client.getRemoteAddress()<< std::endl;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				cordx = sf::Mouse::getPosition(window).x;
				cordy = sf::Mouse::getPosition(window).y;
				mousePressed = true;
			}
			else
			{
				mousePressed = false;
			}
		}

		sf::Packet packet1;//we send

		packet1 << cordx;
		packet1 << cordy;
		packet1 << mousePressed;
		if (client.send(packet1) != sf::Socket::Done)
		{
			//std::cout << "Couldn't send data to client.\n";
		}
		else
		{
			//std::cout << "Data sent to client.\n";
		}
		sf::Packet packet2;//we receive

		if (client.receive(packet2) != sf::Socket::Done)
		{
			//std::cout << "Couldn't recieve data from client.\n";
		}
		else
		{
			//std::cout << "Recieved data from client.\n";
		}
		packet2 >> Enemycordx;
		packet2 >> Enemycordy;
		packet2 >> mouseReceived;

		if (mouseReceived)
		{
			std::cout << "client cords " << Enemycordx<< " " << Enemycordy << std::endl;
			std::cout << "servers cords are" << cordx << " " << cordy << std::endl;
			mouseReceived = false;
		}
		window.clear(sf::Color::Black);
		window.display();

		//Send our clients position to the server
	}
	// use "client" to communicate with the connected client,
	// and continue to accept new connections with the listener
}


int main()
{
	sf::Vector2f cords;
	char  type;
	std::cout << "server (s) or client (c)" << std::endl;
	std::cin >> type;

	if(type =='s')
	{
		server();
	}
	else if( type == 'c')
	{
		client();
	}

}*/