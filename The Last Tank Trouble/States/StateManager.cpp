#include "StateManager.h"
#include <iostream>

void StateManager::setup(sf::RenderWindow& window)
{
	mainmenu.setup(window);
	options.setup(window);
	multiPlayerMenu.setup(window);
	singlePlayer.setup(window);
	multiPlayer.setup(window);
}

void StateManager::handleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (mainmenu.IsActive())
	{
		mainmenu.handleEvents(event, window);

		if(mainmenu.OPbuttonWasPressed())//If options was pressed
		{
			mainmenu.setInactive();//mainemenu is inactive
			options.setActive();//options menu is active
		}
		if(mainmenu.EXbuttonWasPressed())
		{
			window.close();
		}
		if(mainmenu.SPbuttonWasPressed())
		{
			mainmenu.setInactive();
			singlePlayer.setActive();
		}
		if(mainmenu.MPbuttonWasPressed())
		{
			mainmenu.setInactive();
			multiPlayerMenu.setActive();	
		}
	}

	if (options.getActive())
	{
		options.handleEvents(event, window);
		if(options.BKbuttonWasPressed())
		{
			mainmenu.setActive();
			options.setInactive();
		}
	}

	if(multiPlayerMenu.getActive())
	{
		multiPlayerMenu.handleEvents(event, window);
		
		if(multiPlayerMenu.BKbuttonWasPressed())
		{
			mainmenu.setActive();
			multiPlayerMenu.setInactive();
		}




		if (multiPlayerMenu.serverbuttonWasPressed())
		{
			multiPlayer.setServerActive(true);


			multiPlayer.make_foo_func_thread();
		
			

			multiPlayerMenu.setInactive();
			multiPlayer.setActive();

		}
		if (multiPlayerMenu.clientbuttonWasPressed())
		{
			multiPlayer.setClientActive(true);

			multiPlayer.make_c_func_thread();

		
			multiPlayerMenu.setInactive();
			multiPlayer.setActive();
		
		}
	
	}
	if(singlePlayer.getActive())
	{
		singlePlayer.handleEvents(event, window);

		if(singlePlayer.BKbuttonWasPressed())
		{
			singlePlayer.setInactive();
			mainmenu.setActive();
		}
	}
	if(multiPlayer.getActive())
	{
		multiPlayer.handleEvents(event, window);


	}
}
void StateManager::update(sf::RenderWindow& window)
{
	if (singlePlayer.getActive())
	{
		singlePlayer.update(window);
	}

	if (multiPlayer.getActive())
	{

		multiPlayer.update(window);
		//multiPlayer.threadReceive();
	
	}
}

void StateManager::Compose(sf::RenderWindow& window)
{
	if (mainmenu.IsActive())
	{
		window.draw(mainmenu);
	}
	if (options.getActive()) 
	{
		window.draw(options);
	}
	if(multiPlayerMenu.getActive())
	{
		window.draw(multiPlayerMenu);
	}
	if(singlePlayer.getActive())
	{
		window.draw(singlePlayer);
	}
	if(multiPlayer.getActive())
	{
		window.draw(multiPlayer);

	}
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	//target.draw(mainmenu);
}
