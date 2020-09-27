#pragma once
#include "SFML/Graphics.hpp"



	// centers text of any lenght and character size inside of a bounding box
	void centerTextInBounds(sf::Text& text, const sf::FloatRect& bounds);
	// centers text of any lenght and character size inside of a shape
	void centerTextInShape(sf::Text& text, const sf::RectangleShape& shape);



