#pragma once
#include "../Window.h"
#include "SFML/Audio.hpp"
#include "../Resources/ResourceManagement.h"

class MainMenu : public Window
{


private:
	bool isActive = true;

	sf::Font font;

	Button SP{ font,"1 VS 1",sf::Vector2f(300,100) };
	Button MP{ font,"Multiplayer",sf::Vector2f(300,100) };
	Button OP{ font,"Options",sf::Vector2f(300,100) };
	Button EX{ font,"Exit",sf::Vector2f(300,100) };

	sf::Texture buttonT;
	sf::Music music;
	sf::RectangleShape MMS;


public:

	

	 void setup(sf::RenderWindow &window);
	 void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	 void update(sf::RenderWindow& window);
	 void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	 MainMenu()
	 {
		 font.loadFromFile("Fonts/crackman front.ttf");
		// buttonT.loadFromFile("Images/Button.png");
		// music.openFromFile("Audio/generals.ogg");

		 MMS.setTexture(ResourceManagement::GetInstance()->RequestedTexture("MM"));
		 MMS.setSize(sf::Vector2f(MMS.getTextureRect().width, MMS.getTextureRect().height));


		SP.setTexture(*ResourceManagement::GetInstance()->RequestedTexture("Button"));
		MP.setTexture(*ResourceManagement::GetInstance()->RequestedTexture("Button"));
		OP.setTexture(*ResourceManagement::GetInstance()->RequestedTexture("Button"));
		EX.setTexture(*ResourceManagement::GetInstance()->RequestedTexture("Button"));

		

	 }

	bool IsActive()
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

	


	void ButtonSPsetActive(const bool& active){SP.setActive(active);}
	void ButtonMPsetActive(const bool& active){MP.setActive(active);}
	void ButtonOPsetActive(const bool& active){OP.setActive(active);}
	void ButtonEXsetActive(const bool& active){EX.setActive(active);}

	const bool SPbuttonWasPressed() { return SP.getIsPressed(); }
	const bool MPbuttonWasPressed() { return MP.getIsPressed(); }
	const bool OPbuttonWasPressed() { return OP.getIsPressed(); }
	const bool EXbuttonWasPressed() { return EX.getIsPressed(); }


};