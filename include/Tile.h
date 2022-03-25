#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.h"

using sf::Sprite;
using sf::Texture;
using sf::RectangleShape;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Color;

class Tile
{
public:
	Tile();	
	~Tile();

	// Draws the tile on a window
	void draw(RenderWindow& window);	// window - The window to draw on.

	// Sets the tile's texture.
	void setTexture(const Texture& texture);	// texture - The texture that will be set for the tile.

	// Sets the tile's position.
	void setPos(const Vector2f& pos);	// pos - The position to set for the tile.

	// Returns true if the tile contains the given position.
	bool contains(const Vector2f& pos) const;	// pos - The position to check.

	// Highlights the tile.
	void highlight();

	// Unhighlights the tile.
	void unhighlight();

protected:
	Sprite m_sprite;	// The sprite of the tile.
	Vector2f m_position;// The position of the tile.
};

