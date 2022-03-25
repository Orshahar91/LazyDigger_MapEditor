#pragma once
#include <vector>
#include "Container.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Asset_Manager.h"
#include "Consts.h"
#include <iostream>

using std::vector;
using std::fstream;
using sf::Vector2f;
using sf::Texture;

// A struct to hold indexes of a matrix.
struct MatrixIndex
{
	unsigned x;	// Row index.
	unsigned y;	// Column index.
};

class Board
{
public:
	Board();	
	~Board();	

	// Loads a board from a file.
	bool loadBoard(fstream& file,Asset_Manager& manage);	

	// Gets an input for the board dimensions, and creates a new board based on it.
	void createNewBoard();

	// Sets the textures of the tiles background.
	void setTilesTexture(const Texture& texture);	// texture - The texture that will be set for the tiles background.

	// Returns the number of rows existing in the board.
	unsigned getRows() const;

	// Returns the number of columns existing in the board.
	unsigned getCols() const;

	// Draws the board on a window.
	void draw(sf::RenderWindow& window);

	// Highlights the tile in the given position.
	void highlightTile(const Vector2f& pos);	// pos - The position of the tile to highlight.

	// Unhighlights the last tile that was highlighted.
	void unhighlightTile();

	// Sets an object on a tile in the given position.
	void setObject(const Vector2f& pos,				// pos - The position of the tile.
		const Object_t& obj,				// obj - The object to put on the tile.
		Asset_Manager& manage);	// textures - The textures that will be set for the objects.

	// Saves the board into a file.
	void saveBoard(fstream& file);	// file - The file to save into.

	// Clears the board.
	void clearBoard();

	// returns the position of the menu according to the board
	sf::Vector2f getMenuPos() const;

private:
	// Sets the board (matrix of containers) with size and position.
	void initializeBoard();

	// Members:
	vector<vector<Container>> m_board;	// The board - matrix of containers
	int m_rows;							// Board's number of rows
	int m_cols;							// Board's number of columns
	int m_stones;                       // Number of stones allowed to eat
	bool m_isTileHighlighted;			// True if any tile is highlighted.
	MatrixIndex m_highlightedTile;		// The highlighted tile indexes in the matrix.
	bool m_isDiggerPlaced;				// True if any digger is placed on the board already.
	MatrixIndex m_diggerTilePos;		// The digger tile indexes in the matrix.
	sf::Vector2f m_menuPos;				// Starting position of the Menu
};

