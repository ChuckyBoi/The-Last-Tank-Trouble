#include  "../Window.h"
#include "../Game/Player.h"
#include "../Resources/ResourceManagement.h"


class SinglePlayer :public Window
{

private:

	bool isActive = false;
	bool pressed = false;

	sf::Font font;
	Button BK{ font,"Back",sf::Vector2f(300,100) };

	sf::Texture buttonT;

	Map map;
	Score score;
	Player players;

public:
	void setup(sf::RenderWindow& window);
	void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	SinglePlayer()
	{
		font.loadFromFile("Fonts/crackman front.ttf");
		buttonT.loadFromFile("Images/Button.png");
	//	buttonT.setTexture(ResourceManagement::GetInstance()->RequestedTexture("GreenTank"));
		//BK.setTexture(ResourceManagement::GetInstance()->RequestedTexture("Button"));
		BK.setTexture(buttonT);
	
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
