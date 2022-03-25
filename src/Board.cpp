#include "Board.h"


using std::cout;
using std::cin;

const unsigned MAX_BOARD_SIZE = 50;

Board::Board() : m_isDiggerPlaced(false), m_isTileHighlighted(false)
{
}

Board::~Board()
{
}

bool Board::loadBoard(fstream& file, Asset_Manager& manage)
{
	file.seekg(0, std::ios::beg);	// put the reading cursor at the beggining of the file
	file >> m_rows >> m_cols >> m_stones;
	if (file.eof())	// if the existing file was empty
		return false;

	initializeBoard();

	file.get();		// workaround to throw away '\n'
	Char_t c;
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			c = (Char_t)file.get();
			switch (c)
			{
			case C_DIGGER:
				if (!m_isDiggerPlaced)	// if a digger was read from the file, save his position.
				{
					m_isDiggerPlaced = true;
					m_diggerTilePos.x = i;
					m_diggerTilePos.y = j;
					m_board[i][j].setObject(O_DIGGER, manage.GetTexture(O_DIGGER));
				}
				break;
			case C_WALL:
				m_board[i][j].setObject(O_WALL, manage.GetTexture(O_WALL));
				break;
			case C_MONSTER:
				m_board[i][j].setObject(O_MONSTER, manage.GetTexture(O_MONSTER));
				break;
			case C_DIAMOND:
					m_board[i][j].setObject(O_DIAMOND, manage.GetTexture(O_DIAMOND));
				break;
			case C_STONE:
				m_board[i][j].setObject(O_STONE, manage.GetTexture(O_STONE));
				break;
			default:
				break;
			}
		}
		file.get();		// to throw away '\n'
	}

	return true;
}

void Board::createNewBoard()
{
	cout << "Please enter number of rows \n";
	cin >> m_rows;

	cout << "Please enter number of cols \n";
	cin >> m_cols;

	while (m_rows <= 0 || m_rows > MAX_BOARD_SIZE || m_cols <= 0 || m_cols > MAX_BOARD_SIZE)
	{
		cout << "Invalid board size\n";
		cout << "Please enter new number of rows (between 1 and 50)\n";
		cin >> m_rows;
		cout << "Please enter new number of cols (between 1 and 50)\n";
		cin >> m_cols;
	}
	cout << "Please enter number of stones  \n";
	cin >> m_stones;

	

	initializeBoard();

}

void Board::setTilesTexture(const Texture& texture)
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			m_board[i][j].setTexture(texture);
		}
	}
}

unsigned Board::getRows() const
{
	
	return m_rows;
}

unsigned Board::getCols() const
{
	return m_cols;
}

void Board::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			m_board[i][j].draw(window);
		}
	}
}

void Board::highlightTile(const Vector2f& pos)
{
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
		{
			if (m_board[i][j].contains(pos))
			{
				if (!m_isTileHighlighted)	// if there isn't any tile highlighted yet
				{
					m_isTileHighlighted = true;
					m_board[i][j].highlight();
					m_highlightedTile.x = i;
					m_highlightedTile.y = j;
					return;
				}
				else if (i != m_highlightedTile.x || j != m_highlightedTile.y)	// if the tile isn't already highlighted
				{
					m_board[i][j].highlight();
					m_board[m_highlightedTile.x][m_highlightedTile.y].unhighlight();
					m_highlightedTile.x = i;
					m_highlightedTile.y = j;
					return;
				}
			}
		}
}

void Board::unhighlightTile()
{
	if (m_isTileHighlighted)
		m_board[m_highlightedTile.x][m_highlightedTile.y].unhighlight();

	m_isTileHighlighted = false;
}

void Board::setObject(const Vector2f& pos, const Object_t& obj, Asset_Manager& manage)
{
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
		{
			if (m_board[i][j].contains(pos))
			{
				if (obj == O_DIGGER)
				{
					if (!m_isDiggerPlaced)	// if there is not any digger on the board yet
					{
						m_isDiggerPlaced = true;
						m_diggerTilePos.x = i;
						m_diggerTilePos.y = j;
						m_board[i][j].setObject(obj, manage.GetTexture(obj));
					}
					else	// if a digger was placed already we transfer his position
					{
						m_board[m_diggerTilePos.x][m_diggerTilePos.y].deleteObject();	// delete old digger
						m_diggerTilePos.x = i;
						m_diggerTilePos.y = j;
						m_board[i][j].setObject(obj, manage.GetTexture(obj));				// and put it on the new tile
					}
				}
				else if (i == m_diggerTilePos.x && j == m_diggerTilePos.y)	// if the new object was placed on the digger
				{
					m_board[i][j].setObject(obj, manage.GetTexture(obj));
					m_isDiggerPlaced = false;
				}

				else
					m_board[i][j].setObject(obj, manage.GetTexture(obj));

				break;

			}
		}
}

void Board::saveBoard(fstream& file)
{
	file.seekp(0, std::ios::beg);	// put the reading cursor at the beggining of the file
	file << m_rows << " " << m_cols << " " << m_stones << "\n";

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			file << (char)m_board[i][j].getObject();
		}
		file << "\n";
	}
	file.flush();
	cout << "Board saved!\n";
	system("pause");	// pause the program to let the user know the file was saved
}

void Board::clearBoard()
{
	m_board.clear();
	m_rows = m_cols = m_stones = 0;
	m_isDiggerPlaced = false;
	unhighlightTile();
}

sf::Vector2f Board::getMenuPos() const
{
	return m_menuPos;
}

void Board::initializeBoard()
{
	m_board.resize(m_rows);
	for (size_t i = 0; i < m_board.size(); i++)
	{
		m_board[i].resize(m_cols);
	}

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			// the position of each tile will be in the middle of it (TILE_SIZE / 2), where its origin is located.
			m_board[i][j].setPos(Vector2f(float((j * TILE_SIZE) + (TILE_SIZE / 2)), float((i * TILE_SIZE) + (TILE_SIZE/2))));
		}
	}
	int MENU_HEIGHT = m_rows - 1; 
	m_menuPos = m_board[MENU_HEIGHT][(0)].getPos(); // The initial position of the menu will be at the bottom of the board.
}