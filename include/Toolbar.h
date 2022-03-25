#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Consts.h"
#include "Asset_Manager.h"

using sf::Texture;
using std::vector;

class Toolbar
{
public:
	Toolbar();	
	~Toolbar();

	// Sets the texture of the buttons.
	void setBtnTextures(Asset_Manager& manage); // textures - Vector of loaded textures.

	// Draws the toolbar on a window.
	void draw(sf::RenderWindow& window);	// window - The window to draw on.

	// Highlights the button in the given position.
	void highlightButton(const Vector2f& pos);	// pos - The position of the button to highlight.

	// Unhighlights the last button that was highlighted.
	void unhighlightButton();

	// Sets a selected button in the given position.
	void setSelection(const Vector2f& pos		// pos - The position of the button.
		, Object_t& button);	// button - Variable to return the selected button.


	// Sets the toolbar (vector of buttons) with size and position.
	void initializeToolbar(sf::Vector2f);

// Returns the button that is currently selected.
	Object_t getSelectedBtn() const;


private:

	Button m_buttons[NUM_OF_BUTTONS];	// Vector to hold buttons.
	Object_t m_currSelection;	// The currently selected button.
	Object_t m_prevSelection;	// The previous selected button.
	bool m_isHighlighted;		// True if any button is highlighted.
	unsigned m_highlightedBtn;	// The highlighted button number.
};

