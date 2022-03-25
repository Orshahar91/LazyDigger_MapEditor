#pragma once
#include "Tile.h"

class Container : public Tile
{
public:
	Container();
	~Container();

	// Draws the tile and the added object on a window.
	void draw(RenderWindow& window);	// window - The window to draw on.

	// Sets the tile and the added object's position.
	void setPos(const Vector2f& pos);	// pos - The position to set for the tile and the object.

	sf::Vector2f getPos() const ; // return positon of the container

	// Sets the added object.
	void setObject(const Object_t& obj,		// obj - The object to set.
		const Texture& texture);	// texture - The texture of the new object.

// Deletes the object from the container.
	void deleteObject();

	// Returns the object that the container is holding.
	Char_t getObject() const;

private:
	Object_t m_object;		// The object that the container is holding.
	Sprite m_objectSprite;	// The sprite of the object.
	bool m_isObjectAdded;	// True if the container is holding an object.
};

