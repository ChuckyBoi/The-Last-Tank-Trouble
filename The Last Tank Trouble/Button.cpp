#include "Button.h"


	void Button::selectByMouse(const sf::Vector2f & mouse)
	{
		if (!isInactive) {
			// checks if the mouse and the button intersect
			// considers mouse to be 1x1 pixels
			isSelected = shape.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));
		}
	}
	void Button::handleEvents(const sf::Event & event)
	{
		if (!isInactive)
		{
			// if the button is selected outline appears
			if (isSelected)
				shape.setOutlineThickness(outlineThickness);
			else // if not the outline disappears
				shape.setOutlineThickness(0);

			// if its selected and the right events are triggered
			if ( isSelected && event.mouseButton.button == sf::Mouse::Left )
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sound.getStatus() != sf::Music::Status::Playing) // play button sound
						sound.play();

					// create the "pressed in" visual effect
					shape.setTextureRect(sf::IntRect(texturePos.x + (int)shape.getSize().x, texturePos.y,
													 (int)shape.getSize().x, (int)shape.getSize().y));

					// the button has been pressed / take action when released
					isPressed = true;
				}
				else if (isPressed && event.type == sf::Event::MouseButtonReleased)
				{
					// take action
					isActive = true;
				}
			}

			// make the button non-active whenever needed
			if ((event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) || !isSelected)
			{
				shape.setTextureRect(sf::IntRect(texturePos.x, texturePos.y, (int)shape.getSize().x, (int)shape.getSize().y));
				isPressed = false;
			}

			// if the button is pressed and selected the text moves down and right a bit to create the pressed-in feeling
			if (isPressed && isSelected)
				text.setPosition(sf::Vector2f(textPos.x + (3 * shape.getScale().x), textPos.y + (3 * shape.getScale().y))); // move 3px to shape's scale
			else // else the text gets back its position
				text.setPosition(textPos);
		}
	}
	void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(shape, states);
		target.draw(text, states);
	}
	void Button::setSoundFX(const sf::SoundBuffer &buffer)
	{
		this->sound.setBuffer(buffer);
	}
	void Button::setFont(const sf::Font & font)
	{
		// sets font
		text.setFont(font);

		// centers text with the new font in mind
		centerTextInShape(text, shape);
		textPos = text.getPosition();
	}
	void Button::setTextColor(const sf::Color & color)
	{
		text.setFillColor(color);
	}

	void Button::setTexture(const sf::Texture & texture)
	{
		// sets sprite texture
		shape.setTexture(&texture);

		// uses the first part of the buttontexture
		shape.setTextureRect(sf::IntRect(texturePos.x, texturePos.y, int(shape.getSize().x), int(shape.getSize().y)));
	}
	void Button::setTexturePos(const sf::Vector2i position)
	{
		texturePos = position;

		// resets shape's texture to apply the new position immediately
		shape.setTextureRect(sf::IntRect(texturePos.x, texturePos.y, int(shape.getSize().x), int(shape.getSize().y)));
	}
	void Button::setFillColor(const sf::Color & color)
	{
		shape.setFillColor(color);
		shapeColor = color;
	}
	void Button::setPosition(const sf::Vector2f & position)
	{
		//sets position of the sprite
		shape.setPosition(position);

		// update the position of the text based on shape's position
		centerTextInShape(text, shape);
		textPos = text.getPosition();
	}
	void Button::setSelectColor(const sf::Color & color)
	{
		//in case selected this color will be the outline
		shape.setOutlineColor(color);
	}
	void Button::setSelectThickness(const float thickness)
	{
		outlineThickness = thickness;
	}
	void Button::setScale(const sf::Vector2f & scale)
	{
		//changes sprite scale
		shape.setScale(scale);

		//changes text size
		text.setCharacterSize(int(38 * scale.y));

		//centers the newly sized text
		centerTextInShape(text, shape);
		textPos = text.getPosition();
	}
	void Button::setCharacterSize(const int size)
	{
		//sets the new string to the text
		this->text.setCharacterSize(size);

		//centers the string with its new height
		centerTextInShape(text, shape);
		textPos = text.getPosition();
	}
	void Button::setInactivity(const bool in_isInactive)
	{
		if (isInactive && !in_isInactive) {
			// set original shape color back
			shape.setFillColor(shapeColor);
		}
		else if (!isInactive && in_isInactive) {
			// gets rid of selected outline if there is any
			isSelected = false;
			shape.setOutlineThickness(0);

			// set greyish color to shape
			shape.setFillColor ({150, 150, 150});
		}

		isInactive = in_isInactive;
	}
	void Button::setSize(const sf::Vector2f size)
	{
		shape.setSize(size);
	}
	bool Button::activated()
	{
		if (isActive) {
			isActive = false;
			return true;
		}
		else return false;
	}
	void Button::setString(const sf::String & txt)
	{
		//sets the new string to the text
		this->text.setString(txt);

		//centers the new string of text
		centerTextInShape(text, shape);
		textPos = text.getPosition();
	}

