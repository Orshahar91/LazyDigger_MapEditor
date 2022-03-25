#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::draw(RenderWindow& window)
{
	window.draw(m_sprite);
}

void Tile::setTexture(const Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale((TILE_SIZE) / m_sprite.getGlobalBounds().width, (TILE_SIZE) / m_sprite.getGlobalBounds().height);
}

void Tile::setPos(const Vector2f& pos)
{
	m_position = pos;
	m_sprite.setPosition(m_position);
}


bool Tile::contains(const Vector2f& pos) const
{
	return m_sprite.getGlobalBounds().contains(pos);
}

void Tile::highlight()
{
	m_sprite.setColor(Color::Green);
}

void Tile::unhighlight()
{
	m_sprite.setColor(Color::White);
}
