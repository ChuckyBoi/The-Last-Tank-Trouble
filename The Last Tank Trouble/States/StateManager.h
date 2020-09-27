#pragma once
#include "MainMenu.h"
#include "Options.h"
#include "MultiPlayerMenu.h"
#include "SinglePlayer.h"
#include "../Game/MultiPlayer/MultiPlayer.h"





class StateManager :public Window
{
public:
	void setup(sf::RenderWindow& window);
	void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Compose(sf::RenderWindow& window);

	

private:


	sf::Vector2f mouse;
	
	MainMenu mainmenu;
	Options options;
	MultiPlayerMenu multiPlayerMenu;
	SinglePlayer singlePlayer;
	MultiPlayer multiPlayer;

	

	//MainMenu *main = new MainMenu;

	//Window* mainmenu;
	//MainMenu d;
    //mainmenu = &d;


};

