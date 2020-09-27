#include  "../Window.h"
#include "../Resources/ResourceManagement.h"

#include "../Game/MultiPlayer/MultiPlayer.h"


class MultiPlayerMenu :public Window
{
private:

	bool isActive = true;

	sf::Font font;
	Button BK{ font,"Soon...",sf::Vector2f(300,100) };
	Button Server{ font,"Server",sf::Vector2f(300,100) };
	Button Client{ font,"Client",sf::Vector2f(300,100) };

	sf::Texture buttonT;

	sf::RectangleShape MPS;

//	MultiPlayer multiPlayer;
	

public:
	void setup(sf::RenderWindow& window);
	void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	MultiPlayerMenu()
	{

		font.loadFromFile("Fonts/crackman front.ttf");
		buttonT.loadFromFile("Images/Button.png");
		MPS.setTexture(ResourceManagement::GetInstance()->RequestedTexture("MP"));
		MPS.setSize(sf::Vector2f(MPS.getTextureRect().width, MPS.getTextureRect().height));

		BK.setTexture(buttonT);
		Server.setTexture(buttonT);
		Client.setTexture(buttonT);
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

	void ButtonServersetActive(const bool& active) { Server.setActive(active); }
	const bool serverbuttonWasPressed() { return Server.getIsPressed(); }

	void ButtonClientsetActive(const bool& active) { Client.setActive(active); }
	const bool clientbuttonWasPressed() { return Client.getIsPressed(); }


};