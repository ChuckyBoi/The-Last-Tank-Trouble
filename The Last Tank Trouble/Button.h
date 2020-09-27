#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Utils/Center.h"





	class Button : public sf::Drawable
	{
	public:
		Button(const sf::Vector2f& size) {
			shape.setSize(size);
			outlineThickness = 3;
		}
		Button(const sf::Vector2f& size, const sf::Texture& texture) : Button(size) {
			this->setTexture(texture);
		}
		Button(const sf::Font& font, const sf::String& txt, const sf::Vector2f& size) : Button(size)
		{
			text.setFont(font);
			text.setString(txt);
			text.setCharacterSize(30);

			//centerTextInShape(text, shape);
			centerTextInShape(text, shape);

			textPos = text.getPosition();
		}
		Button() : Button(sf::Vector2f{ 400, 50 }) {} // default empty selectable rectangle

		//  Selects by mouse (BUT Needs handleEvents() to take action!)
		void selectByMouse(const sf::Vector2f& mouse);
		// handles enter and mouseclick events and plays given sounds and animations whenever needed
		void handleEvents(const sf::Event& event);

		// draws given shape to a render target
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// sound the button makes when pressed
		void setSoundFX(const sf::SoundBuffer& buffer);
		// font of the text on the button
		void setFont(const sf::Font& font);
		// sets the color of the text on the button
		void setTextColor(const sf::Color& color);
		// string the button uses
		void setString(const sf::String& txt);
		// texture of the button
		void setTexture(const sf::Texture& texture);
		// sets the location inside the texture at which buttons should load (default: 0, 0)
		void setTexturePos(const sf::Vector2i position);
		// changes the default color of the button (default: white)
		void setFillColor(const sf::Color& color);
		// position of the button
		void setPosition(const sf::Vector2f& position);
		// outline's color when selected
		void setSelectColor(const sf::Color& color);
		// sets the thickness of the outline when selected
		void setSelectThickness(const float thickness);
		// scale of the button
		void setScale(const sf::Vector2f& scale);
		// sets the character size of the text
		void setCharacterSize(const int size);
		// if true makes button unselectable, and unactivatable (activates third texture)
		void setInactivity(const bool in_isInactive);
		// sets size of the button (affects texture clipping)
		void setSize(const sf::Vector2f size);
		// returns true whenever action needs to be taken(isActive == true)
		// sets isActive back to false automatically
		bool activated();

		void setActive(const bool& active) { isActive = active; }
		bool getIsPressed() const { return isPressed; }
		
		sf::RectangleShape getShape() { return shape; }
		sf::Vector2f getScale() const { return shape.getScale(); }
		sf::Vector2f getPosition() const { return shape.getPosition(); }
		sf::Vector2f getSize() const { return shape.getSize(); }
		sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }
	

	private:
		sf::RectangleShape shape; // creates a shape for the button
		sf::Text text; // a text to be on the button
		sf::Sound sound; // sound to play when button activated

		float outlineThickness; // the thickness of the outline when selected
		sf::Vector2f textPos; // saves the position at which the text should stay (to avoid moving indefinetly)
		sf::Vector2i texturePos = {0, 0}; // the position at which textures should be loaded from

		sf::Color shapeColor; // the color the shape has when not inactive
		bool isInactive = false; // if true make it grey and set it to unselectable
		bool isPressed = false; // intermediarily active boolean in between isSelected and isActive
		bool isSelected = false; // if the button is selected by either mouse or keyboard this is true
		bool isActive = false; // this is true when the button is pressed upon

		bool useMouse = false; // true whenever mouse selection is used

		bool warningMessage = true; // used to display warning message only once in an endless loop
	};

