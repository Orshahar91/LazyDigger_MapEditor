#include "Game.h"
#include "Consts.h"

using sf::Event;
using sf::Vector2f;

Game::Game() 
{ 

	//Load game assets
	LoadTextures();
	m_toolbar.setBtnTextures(m_manage);
	m_message.setTexture(m_manage.GetTexture(O_MESSAGE));

	if (!openFile())	// if file doesn't exist
	{
		createNewFile();
		ClearWindow();	
	}

	else if (!m_board.loadBoard(m_file, m_manage))	// if reading the existing file failed
	{
		createNewFile();
		ClearWindow();
		
	}

	
	m_toolbar.initializeToolbar(m_board.getMenuPos()); 
	m_board.setTilesTexture(m_manage.GetTexture(O_TILE));
	createWindow();
}

Game::~Game()
{
}

void Game::Run()
{
	while (m_window.isOpen())
	{
		draw();
		HandleEvents();
	}
}

void Game::createWindow()
{
	if (m_board.getCols() < NUM_OF_BUTTONS)	// Workaround so that all buttons will be displayed
		m_window.create(sf::VideoMode(TILE_SIZE * NUM_OF_BUTTONS, TILE_SIZE + TILE_SIZE * m_board.getRows()), APP_NAME, sf::Style::Close);
	else
		m_window.create(sf::VideoMode(TILE_SIZE * m_board.getCols(), TILE_SIZE + TILE_SIZE * m_board.getRows()), APP_NAME, sf::Style::Close);

}


void Game::draw()
{

	m_window.clear();
	m_toolbar.draw(m_window);
	m_board.draw(m_window);
	m_window.display();
}

void Game::HandleEvents()
{
	Event event;
	if (m_window.waitEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_window.close();
			break;
		case Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				// Save the position of the mouse click:
				const Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				
				if (mousePos.y >= m_board.getMenuPos().y && mousePos.y <= m_board.getMenuPos().y +(TILE_SIZE*NUM_OF_BUTTONS))	// Toolbar area
				{
					Object_t button;	// variable to save the button that was pressed
					m_toolbar.setSelection(mousePos, button);

					if (button == O_CLEAR)
					{
						m_window.close();
						m_board.clearBoard();
						createNewFile();
						ClearWindow();
						m_toolbar.initializeToolbar(m_board.getMenuPos());
						m_board.setTilesTexture(m_manage.GetTexture(O_TILE));
						createWindow();
					}
					else if (button == O_SAVE)
					{
						m_board.saveBoard(m_file);
					}
				}
				else	// Board area
				{
					m_board.setObject(mousePos, m_toolbar.getSelectedBtn(), m_manage);
				}
			}
			break;
		case Event::MouseMoved:
			// Save the position of the mouse:
			const Vector2f mousePos = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

			if (event.mouseMove.y >= m_board.getMenuPos().y && event.mouseMove.y < m_board.getMenuPos().y + (TILE_SIZE * NUM_OF_BUTTONS))	// Toolbar area
			{
				m_board.unhighlightTile();
				m_toolbar.highlightButton(mousePos);
			}
			else															// Board area
			{
				m_toolbar.unhighlightButton();
				m_board.highlightTile(mousePos);
			}
			break;
		}
	}

}


bool Game::openFile()
{
	m_file.open(FILE_NAME, fstream::out | fstream::in);
	if (!m_file.is_open())	// if file doesn't exist
		return false;
	return true;
}

void Game::createNewFile()
{
	if (m_file.is_open())
		m_file.close();
	m_file.open(FILE_NAME, fstream::out);
}

void Game::ClearWindow()
{
	m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), APP_NAME); // Temporary window


	m_window.clear();
	m_window.draw(m_message); // Display message to the user
	m_window.display();
	m_board.createNewBoard(); 
}

void Game::LoadTextures()
{
	m_manage.LoadTexture(O_ERASE, ERASE_PNG_FILEPATH);
	m_manage.LoadTexture(O_DIGGER, DIGGER_PNG_FILEPATH);
	m_manage.LoadTexture(O_MONSTER, MONSTER_PNG_FILEPATH);
	m_manage.LoadTexture(O_WALL, WALL_PNG_FILEPATH);
	m_manage.LoadTexture(O_STONE, STONE_PNG_FILEPATH);
	m_manage.LoadTexture(O_DIAMOND, DIAMOND_PNG_FILEPATH);
	m_manage.LoadTexture(O_CLEAR, CLEAR_PNG_FILEPATH);
	m_manage.LoadTexture(O_SAVE, SAVE_PNG_FILEPATH);
	m_manage.LoadTexture(O_TILE, TILE_PNG_FILEPATH);
	m_manage.LoadTexture(O_MESSAGE, MESSAGE_PNG_FILEPATH);

}
