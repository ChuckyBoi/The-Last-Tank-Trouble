#include "Center.h"


	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds) {
		// Center text's origin
		text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f,
			text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);

		// Set text position
		text.setPosition({ bounds.left + bounds.width / 2,
						   bounds.top + bounds.height / 2 });
	}
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape)
	{
		centerTextInBounds(text, shape.getGlobalBounds());
	}

