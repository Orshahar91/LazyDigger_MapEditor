#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Board.h"
#include "Toolbar.h"
#include "Asset_Manager.h"

using std::fstream;
using sf::Texture;
using sf::RenderWindow;
using sf::Event;
using sf::Vector2f;



class Game
{

public:
	Game();
	~Game();
	
	// Opens a file for read and write. Returns false if the file doesn't exist.
	bool openFile();

	void Run();

	// Creates a new file for write.
	void createNewFile();

	// Clear the window with the message to enter dimentions
	void ClearWindow();

	// Load all the textures of the game through object 
	void LoadTextures();

	// Creates the window, with size based on the board size.
	void createWindow();

	// Draws the toolbar and the board on the window, and than displays it.
	void draw();

	// Handles the events: window's closed, left mouse button pressed and mouse moved.
	void HandleEvents();
	
private:

	RenderWindow m_window;		// Window instance.
	fstream m_file;				// File instance for read and write.
	Toolbar m_toolbar;			// Toolbar instance.
	Board m_board;				// Board instance.
	sf::Sprite m_message;	    // Sprite to hold the message for user
	Asset_Manager m_manage;     // Instance to handle textures
};