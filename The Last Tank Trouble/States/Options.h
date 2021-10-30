#pragma once
#include  "../Window.h"
#include "../Resources/ResourceManagement.h"
class Options:public Window
{


private:

	bool isActive = false;

	sf::Font font;
	Button BK{ font,"Back",sf::Vector2f(300,100) };

	
	sf::Texture buttonT;

	sf::RectangleShape OPS;



public:
	void setup(sf::RenderWindow& window);
	void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	Options()
	{
	
		font.loadFromFile("Fonts/crackman front.ttf");
		buttonT.loadFromFile("Images/Button.png");

		OPS.setTexture(ResourceManagement::GetInstance()->RequestedTexture("OP"));
		OPS.setSize(sf::Vector2f(OPS.getTextureRect().width, OPS.getTextureRect().height));


		BK.setTexture(*ResourceManagement::GetInstance()->RequestedTexture("Button"));

		
		
	
	
	
	
	}

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

	void ButtonBKsetActive(const bool& active) { BK.setActive(active); }
	const bool BKbuttonWasPressed() { return BK.getIsPressed(); }


};

