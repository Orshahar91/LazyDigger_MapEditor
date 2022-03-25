#include "Button.h"

const float SELECTION_THICKNESS = 2.75f;
const float PADDING = 5.0f;

Button::Button() : m_isSelected(false)
{
}

Button::~Button()
{
}

void Button::draw(RenderWindow& window)
{
	Tile::draw(window);

	if (m_isSelected)
	{
		sf::RectangleShape selection;
		selection.setSize({ (float)(TILE_SIZE - 2), (float)(TILE_SIZE - 2) });
		selection.setOrigin(selection.getSize().x / 2, selection.getSize().y / 2);
		selection.setPosition(m_position);
		selection.setFillColor(Color::Transparent);
		selection.setOutlineThickness(SELECTION_THICKNESS);
		selection.setOutlineColor(Color::Green);
		window.draw(selection);
	}
}

void Button::setTexture(const Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	// Give the button's sprite a little padding:
	m_sprite.setScale((TILE_SIZE - PADDING) / m_sprite.getGlobalBounds().width, (TILE_SIZE - PADDING) / m_sprite.getGlobalBounds().height);
}

void Button::select()
{
	m_isSelected = true;
}

void Button::deselect()
{
	m_isSelected = false;
}
