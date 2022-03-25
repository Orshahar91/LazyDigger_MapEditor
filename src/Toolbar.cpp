#include "Toolbar.h"


Toolbar::Toolbar()
	:m_currSelection(O_ERASE), m_prevSelection(O_ERASE), m_isHighlighted(false)
{
	m_buttons[m_currSelection].select();
}


Toolbar::~Toolbar()
{
}

void Toolbar::setBtnTextures(Asset_Manager & manage)
{
	for (unsigned i = 0; i < NUM_OF_BUTTONS; i++)
	{
		m_buttons[i].setTexture(manage.GetTexture(i));
	}

}

void Toolbar::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < NUM_OF_BUTTONS; i++)
	{
		m_buttons[i].draw(window);
	}
}

void Toolbar::highlightButton(const Vector2f& pos)
{
	for (unsigned i = 0; i < NUM_OF_BUTTONS; i++)
	{
		if (m_buttons[i].contains(pos))
		{
			if (!m_isHighlighted)	// if there isn't any button highlighted yet
			{
				m_buttons[i].highlight();
				m_isHighlighted = true;
				m_highlightedBtn = i;
				return;
			}
			else if (i != m_highlightedBtn) // if the button isn't already highlighted
			{
				m_buttons[i].highlight();
				m_buttons[m_highlightedBtn].unhighlight();
				m_highlightedBtn = i;
				return;
			}
		}
	}
}

void Toolbar::unhighlightButton()
{
	if (m_isHighlighted)
		m_buttons[m_highlightedBtn].unhighlight();

	m_isHighlighted = false;
}

void Toolbar::setSelection(const Vector2f& pos, Object_t& button)
{
	for (size_t i = 0; i < NUM_OF_BUTTONS; i++)
	{
		if (m_buttons[i].contains(pos))
		{
			m_currSelection = (Object_t)i;
			button = m_currSelection;
			break;
		}
	}

	if (m_currSelection == O_CLEAR || m_currSelection == O_SAVE)	// no need to select Clear and Save buttons
	{
		m_currSelection = m_prevSelection;
		return;
	}
	else if (m_currSelection != m_prevSelection)	// if the button isn't already selected
	{
		m_buttons[m_currSelection].select();
		m_buttons[m_prevSelection].deselect();
		m_prevSelection = m_currSelection;
	}
}

Object_t Toolbar::getSelectedBtn() const
{
	return m_currSelection;
}

void Toolbar::initializeToolbar(sf::Vector2f MenuPos)
{
	
	for (unsigned i = 0; i < NUM_OF_BUTTONS; i++)
	{
		// the position of each button will be in the middle of his tile (TILE_SIZE / 2), where his origin is located.
		m_buttons[i].setPos({ (float)(MenuPos.x + (i * TILE_SIZE)), (float)(MenuPos.y + TILE_SIZE) });
	}
}