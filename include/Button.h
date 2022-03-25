#pragma once
#include "Tile.h"

class Button : public Tile
{
public:
	Button();
	~Button();

	// Draws the button on a window. If the button is selected, it also draws an outline around it.
	void draw(RenderWindow& window);	// window - The window to draw on.

	// Sets the button's texture.
	void setTexture(const Texture& texture);	// texture - The texture that will be set for the button.

	// Selects the button.
	void select();

	// Deselects the button.
	void deselect();

private:
	bool m_isSelected;	// True if the button is selected.
};

